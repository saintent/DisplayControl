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

#define RST_SW_PORT
#define RSP_SW_PIN
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
//================ TYPEDEF FUNCTION TYPE DEFFINITION ========================//
typedef void BTCallBack_t(BTName_t);
//================ TYPEDEF STRUCT/UNION =====================================//
//
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
