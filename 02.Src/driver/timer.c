//================ File Despciption =========================================//
//=== File name : sm_timer.c
//===========================================================================//

//================ Index ====================================================//
//
//================ Include Header ===========================================//
#include "sm_timer.h"
#include "system.h"
//================ PUBLIC METHOD ============================================//
// extern function
//
//================ PUBLIC DATA ==============================================//
// extern data
//
//================ PRIVATE METHOD ===========================================//
// non extern function
//
//================ PRIVATE DATA =============================================//
// non extern data
tm_reg_t TM_REG[TM_INDEX_MAX] = { NULL };
//================ PRIVATE DEFINE ===========================================//
//
//================ PRIVATE MACRO ============================================//
//
//================ SOURCE CODE ==============================================//
//---------------- Init routie ----------------------------------------------//
void tm_init(void) {
	uint16_t interval_100ms;
	uint64_t sys_clk;

	/* Enable clock for TIMER0 module */
	  CMU_ClockEnable(COM_TIMER_CLK, true);

	TIMER_Init_TypeDef timer_init = {
			.enable = true,
			.debugRun = true,
			.prescale = timerPrescale1024,
			.clkSel = timerClkSelHFPerClk,
			.fallAction = timerInputActionNone,
			.riseAction = timerInputActionNone,
			.mode = timerModeUp,
			.dmaClrAct = false,
			.quadModeX4 = false,
			.oneShot = false,
			.sync = false,
	};

	 /* Enable overflow interrupt */
	  TIMER_IntEnable(COM_TIMER, TIMER_IF_OF);

	  /* Enable TIMER0 interrupt vector in NVIC */
	  NVIC_EnableIRQ(TIMER0_IRQn);

	  /* Set TIMER Top value */
	  sys_clk = (uint64_t)SYSTEM_FREQ * (uint64_t)1000;
	  sys_clk = sys_clk / (uint64_t)1024;
	  sys_clk =100000000000/sys_clk;
	  sys_clk = 100000/sys_clk;
	  interval_100ms = (uint16_t)(sys_clk + 1) * 100U;
	  TIMER_TopSet(COM_TIMER, interval_100ms);

	  /* Configure TIMER */
	  TIMER_Init(COM_TIMER, &timer_init);
}



void tm_reg_timer(tm_reg_indx_t idx, tm_reg_cb_t reg) {
	TM_REG[idx].cb = reg.cb;
	TM_REG[idx].interval = reg.interval/100U;
	TM_REG[idx].param = reg.param_cb;
}

void tm_set_interval(tm_reg_indx_t idx, uint32_t itv) {
	TM_REG[idx].interval = itv/100U;
	TM_REG[idx].cnt = 0U;
}

void tm_reset_cnt(tm_reg_indx_t idx) {
	TM_REG[idx].cnt = 0U;
}

void tm_en_cnt(tm_reg_indx_t idx, uint8_t en) {
	if(en) {
		TM_REG[idx].en = en;
		TM_REG[idx].cnt = 0U;
	}
	else {
		TM_REG[idx].en = 0U;
		TM_REG[idx].cnt = 0U;
	}
}

void tm_interval_check(tm_reg_indx_t index) {
	if (TM_REG[index].en) {
		if (++TM_REG[index].cnt >= TM_REG[index].interval) {
			// If function callback had initialed
			if(TM_REG[index].cb != NULL) {
				TM_REG[index].cb(TM_REG[index].param);
			}
			TM_REG[index].cnt = 0U;
		}
	}
}
/**************************************************************************//**
 * @brief TIMER0_IRQHandler
 * Interrupt Service Routine TIMER0 Interrupt Line
 *****************************************************************************/
void TIMER0_IRQHandler(void)
{
  /* Clear flag for TIMER0 overflow interrupt */
  TIMER_IntClear(TIMER0, TIMER_IF_OF);

  for(int i = 0; i < TM_INDEX_MAX; i++) {
	  tm_interval_check(i);
  }
}
//================ END OF FILE ==============================================//
