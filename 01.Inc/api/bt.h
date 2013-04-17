//================ File Description =========================================//
//=== File name :
//=== 
//===========================================================================//

#ifndef BT_H
#define BT_H

//================ Include Header ===========================================//
#include "stdint.h"
#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
//================ PULBIC DEFINE ============================================//
//-------------- Push button attribute ----------
#define REM_MAN_SW_PORT		GPIOC
#define REM_MAN_SW_PIN		GPIO_Pin_0

#define LEFT_SW_PORT		GPIOC
#define LEFT_SW_PIN			GPIO_Pin_1

#define DW_SW_PORT			GPIOC
#define DW_SW_PIN			GPIO_Pin_3

#define UP_SW_PORT			GPIOC
#define UP_SW_PIN			GPIO_Pin_2

#define RIGHT_SW_PORT		GPIOA
#define RIGHT_SW_PIN		GPIO_Pin_0

#define EN_SW_PORT			GPIOA
#define EN_SW_PIN			GPIO_Pin_1

#define MODE_SW_PORT		GPIOA
#define MODE_SW_PIN			GPIO_Pin_2

#define HOME_SW_PORT		GPIOA
#define HOME_SW_PIN			GPIO_Pin_3

#define RST_SW_PORT			GPIOF
#define RST_SW_PIN			GPIO_Pin_4
//================ PUBLIC MACRO =============================================//
//
//================ TYPEDEF DATA TYPE DEFINITION =============================//
//
//================ ENUMERATOR DEFINITION ====================================//
typedef enum BTName_tag {
	RM_BT = 0,
	L_BT,
	U_BT,
	D_BT,
	R_BT,
	MODE_BT,
	EN_BT,
	HOME_BT,
	RST_BT
}BTName_t;

typedef enum BTPress_tag {
	BT_RELEAS = 0,
	BT_PRESS
}BTPress_t;
//================ TYPEDEF FUNCTION TYPE DEFFINITION ========================//
typedef void BTCallBack_t(BTName_t, BTPress_t);
//================ TYPEDEF STRUCT/UNION =====================================//
typedef struct ButtonStatus_tag {
	uint8_t 	Press;
	uint8_t 	HadProcess;
	uint8_t		Count;
	uint8_t 	rsv;
}ButtonStatus_t;
//================ EXTERN FUNCTION ==========================================//
void BTInit(void);
void SetBTCallback(BTCallBack_t* cb);
void BTProcess(void);
//================ EXTERN FUNCTION POINTER ==================================//
//
//================ EXTERN VARIABLE ==========================================//
//
//================ EXTERN QUEUE =============================================//
//
//================ END OF FILE ==============================================//
#endif
//#ifndef BT_H
