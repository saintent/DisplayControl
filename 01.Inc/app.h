//================ File Despciption =========================================//
//=== File name : app.h
//=== 
//===========================================================================//

#ifndef APP_H
#define APP_H

//================ Include Header ===========================================//
#include "stdint.h"
#include "bt.h"
#include "uart.h"
#include "timer.h"
#include "led.h"
#include "at_command.h"
//================ PULBIC DEFINE ============================================//
//
//================ PUBLIC MACRO =============================================//
//
//================ TYPEDEF DATA TYPE DEFINITION =============================//
//
//================ ENUMERATOR DEFINITION ====================================//
//
//================ TYPEDEF FUNCTION TYPE DEFFINITION ========================//
//
//================ TYPEDEF STRUCT/UNION =====================================//
typedef struct AppControl_tag {
	uint8_t 	RxData[16];
	uint8_t 	TxData[16];
	uint8_t 	RxPtr;
	uint8_t 	TxLen;
	uint16_t	ReSend;
	struct {
		uint16_t	IsStartPackage:1;
		uint16_t	RecPackageType:1;
		uint16_t	rsv:14;
	}Status;
}AppControl_t;
//================ EXTERN FUNCTION ==========================================//
void TimeOutHandler(uint8_t Event);
void BTCmd(BTName_t Name, BTPress_t Press);
void DataRecHandler(uint8_t Incomming);
//================ EXTERN FUNCTION POINTER ==================================//
//
//================ EXTERN VARIABLE ==========================================//
//
//================ EXTERN QUEUE =============================================//
//
//================ END OF FILE ==============================================//
#endif
//#ifndef APP_H
