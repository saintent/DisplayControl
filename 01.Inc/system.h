//================ File Despciption =========================================//
//=== File name : usart_api.h
//=== 
//===========================================================================//

#ifndef UART_H
#define SUART_H

//================ Include Header ===========================================//
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "stm32f0xx.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"

//================ PULBIC DEFINE ============================================//
#define UART_CLK			RCC_APB2Periph_USART1
#define GPIOA_CLK			RCC_AHBPeriph_GPIOA
#define GPIOB_CLK			RCC_AHBPeriph_GPIOB
#define GPIOC_CLK			RCC_AHBPeriph_GPIOC


//--------------- Uart attribute ----------------
#define UART_PORT			USART1
#define UART_TX_PIN			GPIO_Pin_9
#define UART_RX_PIN			GPIO_Pin_10
#define UART_TX_PIN_SRC		GPIO_PinSource9
#define UART_RX_PIN_SRC		GPIO_PinSource10
#define UART_GPIO_PORT		GPIOA
#define UART_GPIO_AF		GPIO_AF_1
#define UART_IRQn			USART1_IRQn

//-------------- Push button attribute ----------
#define REM_MAN_SW_PORT		GPIOC
#define REM_MAN_SW_PIN		GPIO_Pin_0

#define LEFT_SW_PORT		GPIOC
#define LEFT_SW_PIN			GPIO_Pin_1

#define DW_SW_PORT			GPIOC
#define DW_SW_PIN			GPIO_Pin_2

#define UP_SW_PORT			GPIOC
#define UP_SW_PIN			GPIO_Pin_3

#define RIGHT_SW_PORT		GPIOA
#define RIGHT_SW_PIN		GPIO_Pin_0

#define EN_SW_PORT			GPIOA
#define EN_SW_PIN			GPIO_Pin_1

#define MODE_SW_PORT		GPIOA
#define MODE_SW_PIN			GPIO_Pin_2

#define HOME_SW_PORT		GPIOA
#define HOME_SW_PIN			GPIO_Pin_3

//---------------- DP Status ------------------
#define DP_STA_PORT			GPIOC
#define DP_STA_PIN			GPIO_Pin_13

//---------------- 7 Segment ------------------
#define C_PORT				GPIOB
#define C_PIN				GPIO_Pin_12

#define DP_PORT				GPIOB
#define DP_PIN				GPIO_Pin_13

#define E_PORT				GPIOB
#define E_PIN				GPIO_Pin_14

#define D_PORT				GPIOB
#define D_PIN				GPIO_Pin_15

#define F_PORT				GPIOC
#define F_PIN				GPIO_Pin_6

#define G_PORT				GPIOC
#define G_PIN				GPIO_Pin_7

#define B_PORT				GPIOC
#define B_PIN				GPIO_Pin_8

#define A_PORT				GPIOC
#define A_PIN				GPIO_Pin_9

#define COM1_PORT			GPIOC
#define COM1_PIN			GPIO_Pin_4

#define COM2_PORT			GPIOC
#define COM2_PIN			GPIO_Pin_5

//--------------- LED Status -----------------
#define ROW_PORT			GPIOB
#define ROW1_PIN			GPIO_Pin_7
#define ROW2_PIN			GPIO_Pin_6
#define ROW3_PIN			GPIO_Pin_5
#define ROW4_PIN			GPIO_Pin_4
#define ROW5_PIN			GPIO_Pin_3
#define ROW6_PIN			GPIO_Pin_2
#define ROW7_PIN			GPIO_Pin_1
#define ROW8_PIN			GPIO_Pin_0

#define COLUMN_PORT			GPIOB
#define COLUMN1_PIN			GPIO_Pin_10
#define COLUMN2_PIN			GPIO_Pin_9
#define COLUMN3_PIN			GPIO_Pin_8



//================ PUBLIC MACRO =============================================//
//
//================ TYPEDEF DATA TYPE DEFINITION =============================//
//
//================ ENUMERATOR DEFINITION ====================================//
//
//================ TYPEDEF STRUCT/UNION DATA TYPE DEFFINITION ===============//
//
//================ EXTERN FUNCTION ==========================================//
//
//================ EXTERN FUNCTION POINTER ==================================//
//
//================ EXTERN VARIABLE ==========================================//
//
//================ EXTERN QUEUE =============================================//
//
//================ END OF FILE ==============================================//
#endif
//#ifndef UART_H
