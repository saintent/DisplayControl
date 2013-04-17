//================ File Despciption =========================================//
//=== File name : usart_api.c
//===========================================================================//

//================ Index ====================================================//
//
//================ Include Header ===========================================//
#include "uart.h"
//================ PUBLIC METHOD ============================================//
// extern function
//
//================ PUBLIC DATA ==============================================//
// extern data
//
//================ PRIVATE METHOD ===========================================//
// non extern function
void RevCb(uint8_t data);
//================ PRIVATE DATA =============================================//
// non extern data
UartTask_t 			uartTask[USART_MAX] = { 0 };
UsartRevCallBack_t*	revCb = RevCb;
//================ PRIVATE DEFINE ===========================================//
#define CURRENT_TASK	uartTask[USART_1].CurrentTask
#define TASK			uartTask[USART_1].Task[CURRENT_TASK]
//================ PRIVATE MACRO ============================================//
//
//================ SOURCE CODE ==============================================//
//---------------- Init routie ----------------------------------------------//
void RevCb(uint8_t data) {
	(void) data;
}

void UsartInit(void) {

	//memset(uartTask, 0, sizeof(UartTask_t));

	USART_InitTypeDef UartInit;
	GPIO_InitTypeDef GpioInit;
	NVIC_InitTypeDef NVICInit;

	// Enable USART clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// Connect PXx to USART Tx
	GPIO_PinAFConfig(UART_GPIO_PORT, UART_TX_PIN_SRC, UART_GPIO_AF);
	// Connect Pxx to USART Rx
	GPIO_PinAFConfig(UART_GPIO_PORT, UART_RX_PIN_SRC, UART_GPIO_AF);

	// Config uart pin as AF
	GpioInit.GPIO_Pin = UART_TX_PIN | UART_RX_PIN;
	GpioInit.GPIO_Mode = GPIO_Mode_AF;
	GpioInit.GPIO_Speed = GPIO_Speed_10MHz;
	GpioInit.GPIO_OType = GPIO_OType_PP;
	GpioInit.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(UART_GPIO_PORT, &GpioInit);

	UartInit.USART_BaudRate = 115200;
	UartInit.USART_WordLength = USART_WordLength_8b;
	UartInit.USART_StopBits = USART_StopBits_1;
	UartInit.USART_Parity = USART_Parity_No;
	UartInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UartInit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// UART Initial
	USART_Init(UART_PORT, &UartInit);

	// NVIC init
	NVICInit.NVIC_IRQChannel = UART_IRQn;
	NVICInit.NVIC_IRQChannelPriority = 0;
	NVICInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVICInit);

	// Interrupt Set up
	USART_ITConfig(UART_PORT, USART_IT_RXNE, ENABLE);

	USART_OverrunDetectionConfig(UART_PORT, USART_OVRDetection_Disable);

	// Enable UART
	USART_Cmd(UART_PORT, ENABLE);


}

void UsartSetRevCallback(UsartRevCallBack_t* fn) {
	revCb = fn;
}

void UartSend(uint8_t* data, uint8_t len) {
	if(uartTask[USART_1].NumberOfTask <= (MAX_TASK - 1)) {
		//TASK.Data = malloc(len);
		TASK.Length = len;
		TASK.Pointer = 0;
		// Copy data to buffer
		memcpy(TASK.Data, data, len);

		if(uartTask[USART_1].NumberOfTask == 0) {
			// Interrupt Set up
			USART_ITConfig(UART_PORT, USART_IT_TXE, ENABLE);
			uartTask[USART_1].NumberOfTask++;
		}
		else {
			uartTask[USART_1].NumberOfTask++;
		}

	}
	else {
		// Busy
	}
}

//---------------- Interupt routie ------------------------------------------//
/**************************************************************************//**
 * @brief USART RX IRQ Handler
 *
 * Set up the interrupt prior to use
 *
 * Note that this function handles overflows in a very simple way.
 *
 *****************************************************************************/
void UsartRxHandler(UsartPort_t port, uint8_t data) {
	revCb(data);
}

/**************************************************************************//**
 * @brief USART TX IRQ Handler
 *
 * Set up the interrupt prior to use
 *
 *****************************************************************************/
void UsartTxHandler(UsartPort_t port) {
	// Send data
	USART_SendData(UART_PORT, TASK.Data[TASK.Pointer]);

	if (++TASK.Pointer >= TASK.Length) {
		// End of task
		//free(TASK.Data);

		if (++uartTask[USART_1].CurrentTask >= MAX_TASK) {
			uartTask[USART_1].CurrentTask = 0;
		}
		// If this last task
		if (--uartTask[USART_1].NumberOfTask == 0) {
			// Disable
			USART_ITConfig(UART_PORT, USART_IT_TXE, DISABLE);
		}

	}
}

//================ END OF FILE ==============================================//
