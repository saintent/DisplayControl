//================ File Despciption =========================================//
//=== File name : gpio.h
//=== 
//===========================================================================//

#ifndef LED_H
#define LED_H

//================ Include Header ===========================================//
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "system.h"

//================ PULBIC DEFINE ============================================//
//----- Parameter define
//================ PUBLIC MACRO =============================================//
//
//================ TYPEDEF DATA TYPE DEFINITION =============================//

//================ ENUMERATOR DEFINITION ====================================//
typedef enum DotMatixRow_tag {
	ROW_1 = 0,
	ROW_2,
	ROW_3,
	ROW_4,
	ROW_5,
	ROW_6,
	ROW_7,
	ROW_8
}DotMatixRow_t;

typedef enum DotMatixColum_tag {
	COLUMN_1 = 0,
	COLUMN_2,
	COLUMN_3
}DotMatixColum_t;

typedef enum MLed_tag {
	M1_LED = 0,
	M2_LED,
	M3_LED,
	M4_LED,
	M5_LED,
	M6_LED,
	M7_LED,
	M8_LED
}MLed_t;

typedef enum StatusLed_tag {
	REMOTE_LED = 0,
	R_LINK_LED,
	MANUAL_LED,
	L_LINK_LED,
	DIMMER_LED,
	ALEMP_LED,
	CTEMP_LED,
	DTEMP_LED
}StatusLed_t;

typedef enum LedType_tag {
	M_ROW2 = 0,
	M_ROW1,
	STATUS_LED,
	DIGIT1,
	DIGIT2
}LedType_t;

typedef enum LedCmd_tag {
	LED_ON = 0,
	LED_OFF
}LedCmd_t;
//================ TYPEDEF STRUCT/UNION DATA TYPE DEFFINITION ===============//
typedef struct LedCtr_tag {
	LedType_t		LedState;
	LedType_t		Segment7State;
	uint16_t		rsv;
}LedCtr_t;
//================ EXTERN FUNCTION ==========================================//
void LedInit(void);
void LedCmd(LedType_t Type, uint8_t Where, LedCmd_t Cmd);
void LedProcess(void);
//================ EXTERN FUNCTION POINTER ==================================//
//
//================ EXTERN VARIABLE ==========================================//
//
//================ EXTERN QUEUE =============================================//
//
//================ END OF FILE ==============================================//
#endif
//#ifndef LED_H
