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
#include "stm32f0xx_gpio.h"


//================ PULBIC DEFINE ============================================//
//----- Parameter define
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
	DIGIT2,
	DUM1,
	DUM2,
	DUM3
}LedType_t;

typedef enum LedCmd_tag {
	LED_OFF = 0,
	LED_ON

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
