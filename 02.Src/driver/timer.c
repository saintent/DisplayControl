//================ File Despciption =========================================//
//=== File name : sm_timer.c
//===========================================================================//

//================ Index ====================================================//
//
//================ Include Header ===========================================//
#include "timer.h"
#include "stm32f0xx_tim.h"
#include "system.h"
//================ PUBLIC METHOD ============================================//
// extern function
//
//================ PUBLIC DATA ==============================================//
// extern data
//
//================ PRIVATE METHOD ===========================================//
// non extern function
void TimeOutCheck(TimeOutEvent_t index);
//================ PRIVATE DATA =============================================//
// non extern data
TimeOutReg_t TM_REG[TIMEOUT_MAX] = { NULL };
//================ PRIVATE DEFINE ===========================================//
//
//================ PRIVATE MACRO ============================================//
//
//================ SOURCE CODE ==============================================//
//---------------- Init routie ----------------------------------------------//
void TimerInit(void) {

	/* Enable clock for Timer2 module */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

	TIM_TimeBaseInitTypeDef TimerInit = {
			.TIM_Period = 100,
			.TIM_Prescaler = 8000,
			.TIM_ClockDivision = TIM_CKD_DIV4,
			.TIM_CounterMode = TIM_CounterMode_Up
	};
	TIM_TimeBaseInit(TIM2, &TimerInit);
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	//TIM2->DIER |=
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
}

void TimerResetCounter(void) {
	TIM_SetCounter(TIM2, 0);
}

void TimerStart(void) {
	TIM_Cmd(TIM2, ENABLE);
}

void TimerInterrupt(void) {
	uint8_t i;
	for(i = 0; i < TIMEOUT_MAX; i++) {
		TimeOutCheck((TimeOutEvent_t)i);
	}
}

void SetTimeOutCallBack(TimeOutEvent_t Event, uint8_t Interval,
		TimerCallback_t* Callback) {
	TM_REG[Event].Callback = Callback;
	TM_REG[Event].Interval = Interval;
	TM_REG[Event].CallbackParameter = Event;
}

void EnableTimeOut(TimeOutEvent_t Event, uint8_t Cmd) {
	TM_REG[Event].Enable = Cmd;
}

void SetTimeOut(TimeOutEvent_t Event,uint8_t Interval) {
	TM_REG[Event].Interval = Interval;
}

void ResetTimeCounter(TimeOutEvent_t Event) {
	TM_REG[Event].Interval = 0;
}

void TimeOutCheck(TimeOutEvent_t index) {
	if (TM_REG[index].Enable) {
		if (++TM_REG[index].Count >= TM_REG[index].Interval) {
			// If function callback had initialed
			if(TM_REG[index].Count != NULL) {
				TM_REG[index].Callback(TM_REG[index].CallbackParameter);
			}
			TM_REG[index].Count = 0U;
		}
	}
}
//================ END OF FILE ==============================================//
