//================ File Despciption =========================================//
//=== File name : usart_api.h
//=== 
//===========================================================================//

#ifndef UART_H
#define UART_H

//================ Include Header ===========================================//
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
//#include "system.h"
#include "stm32f0xx.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_gpio.h"


//================ PULBIC DEFINE ============================================//
#define UART_CLK			RCC_APB2Periph_USART1
//--------------- Uart attribute ----------------
#define UART_PORT			USART1
#define UART_TX_PIN			GPIO_Pin_9
#define UART_RX_PIN			GPIO_Pin_10
#define UART_TX_PIN_SRC		GPIO_PinSource9
#define UART_RX_PIN_SRC		GPIO_PinSource10
#define UART_GPIO_PORT		GPIOA
#define UART_GPIO_AF		GPIO_AF_1
#define UART_IRQn			USART1_IRQn
//----- Parameter define
#define RX_BUFF_SIZE				64
#define MAX_TASK					8

//================ PUBLIC MACRO =============================================//
//
//================ TYPEDEF DATA TYPE DEFINITION =============================//
//
//================ ENUMERATOR DEFINITION ====================================//
typedef enum usart_port_tag {
	USART_1 = 0,
	//USART_2 = 1,
	USART_MAX,
}UsartPort_t;
//================ TYPEDEF STRUCT/UNION DATA TYPE DEFFINITION ===============//
typedef struct uart_task_attr_tag {
	uint8_t 			Data[30];
	uint8_t 			Length;
	uint8_t 			Pointer;
}UartTaskAttribute_t;

typedef struct uart_task_tag {
	uint16_t 			NumberOfTask;
	uint16_t 			CurrentTask;
	UartTaskAttribute_t Task[MAX_TASK];
}UartTask_t;


typedef void UsartRevCallBack_t(uint8_t);
//================ EXTERN FUNCTION ==========================================//
void UsartInit(void);
void UsartSetRevCallback(UsartRevCallBack_t* fn);
void UartSend(uint8_t* data, uint8_t len);

void UsartRxHandler(UsartPort_t port, uint8_t data);
void UsartTxHandler(UsartPort_t port);
//================ EXTERN FUNCTION POINTER ==================================//
//
//================ EXTERN VARIABLE ==========================================//
//
//================ EXTERN QUEUE =============================================//
//
//================ END OF FILE ==============================================//
#endif
//#ifndef UART_H
