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
#include "system.h"
#include "stm32f0xx_usart.h"

//================ PULBIC DEFINE ============================================//
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
	uint8_t* 			Data;
	uint8_t 			Length;
	uint16_t 			Pointer;
}UartTaskAttribute_t;

typedef struct uart_task_tag {
	uint16_t 			NumberOfTask;
	uint16_t 			CurrentTask;
	UartTaskAttribute_t Task[MAX_TASK];
}UartTask_t;


typedef void UsartRevCallBack(uint8_t);
//================ EXTERN FUNCTION ==========================================//
void UsartInit(void);
void UsartSetRevCallback(UsartRevCallBack* fn);
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
