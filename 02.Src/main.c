//================ File Despciption =========================================//
//=== File name : usart_api.c
//===========================================================================//

//================ Index ====================================================//
//
//================ Include Header ===========================================//
#include "stdint.h"
#include "app.h"
#include "at_command.h"
#include "bt.h"
#include "led.h"
#include "timer.h"
#include "uart.h"
#include "stm32f0xx_rcc.h"
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
//
//================ PRIVATE DEFINE ===========================================//
//#define TEST_SYS_TICK
#define MAX_RSP_TM		5
#define MAX_CH_TM		20
//================ PRIVATE MACRO ============================================//
//
//================ SOURCE CODE ==============================================//

void DPStaHandler(uint8_t param) {
#ifndef TEST_SYS_TICK
	if(GPIO_ReadOutputDataBit(DP_STA_PORT, DP_STA_PIN)) {
		GPIO_ResetBits(DP_STA_PORT, DP_STA_PIN);
	}
	else {
		GPIO_SetBits(DP_STA_PORT, DP_STA_PIN);
	}
#endif
	(void) param;
}

void SystickHandler(void) {
#ifndef TEST_SYS_TICK
	// Button Polling
	BTProcess();
	// Led Process
	LedProcess();
#else
	if (GPIO_ReadOutputDataBit(DP_STA_PORT, DP_STA_PIN )) {
		GPIO_ResetBits(DP_STA_PORT, DP_STA_PIN );
	} else {
		GPIO_SetBits(DP_STA_PORT, DP_STA_PIN );
	}
#endif
}

void main(void) {

	//RCC_ClockSecuritySystemCmd(ENABLE);
	// PLL at 16 Mhz
	//RCC_PLLCmd(DISABLE);
	//while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
	//RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_4);
	//RCC_PLLCmd(ENABLE);
	//while(!RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
	// Change clock to PLL
	//RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	// SysTick Config
	if (SysTick_Config(SystemCoreClock / 5000)) {
		/* Capture error */
		while (1)
			;
	}
        
	// Button Config
	BTInit();
	// Set button callback
	SetBTCallback(BTCmd);

	// Led init
	LedInit();

	// Timer Init
	TimerInit();
	// Set 1 sec toggle led
	SetTimeOutCallBack(SEC_TIMEOUT, 10, DPStaHandler);
	// Set time out for character time out
	SetTimeOutCallBack(CHAR_TIMEOUT, MAX_CH_TM, TimeOutHandler);
	// Set time our for response time out
	SetTimeOutCallBack(RSP_TIMEOUT, MAX_RSP_TM, TimeOutHandler);

	// Uart Init
	UsartInit();
	// Set call back function for usart
	UsartSetRevCallback(DataRecHandler);

	TimerStart();
	EnableTimeOut(SEC_TIMEOUT, ENABLE);

	while(1);

}

//================ END OF FILE ==============================================//
