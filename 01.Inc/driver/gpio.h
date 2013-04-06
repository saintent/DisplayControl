//================ File Despciption =========================================//
//=== File name : gpio.h
//=== 
//===========================================================================//

#ifndef GPIO_H
#define GPIO_H

//================ Include Header ===========================================//
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "system.h"
#include "stm32f0xx_gpio.h"

//================ PULBIC DEFINE ============================================//
//----- Parameter define
//================ PUBLIC MACRO =============================================//
//
//================ TYPEDEF DATA TYPE DEFINITION =============================//

//================ ENUMERATOR DEFINITION ====================================//
typedef enum GpioPort_tag {
	GPIO_A = 0,
	GPIO_B,
	GPIO_C,
	GPIO_MAX
}GpioPort_t;
//================ TYPEDEF STRUCT/UNION DATA TYPE DEFFINITION ===============//

//================ EXTERN FUNCTION ==========================================//

//================ EXTERN FUNCTION POINTER ==================================//
//
//================ EXTERN VARIABLE ==========================================//
//
//================ EXTERN QUEUE =============================================//
//
//================ END OF FILE ==============================================//
#endif
//#ifndef GPIO_H
