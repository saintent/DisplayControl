//================ File Despciption =========================================//
//=== File name : sm_timer.h
//=== 
//===========================================================================//

#ifndef TIMER_H
#define TIMER_H

//================ Include Header ===========================================//
#include <stdint.h>
//================ PULBIC DEFINE ============================================//

//----- Parameter define
#define COM_TIMER			TIMER0
#define COM_TIMER_CLK		cmuClock_TIMER0
#define COM_TIMER_TOP		100U				// Interrupt at 100 ms

//================ PUBLIC MACRO =============================================//
//
//================ TYPEDEF DATA TYPE DEFINITION =============================//

//================ ENUMERATOR DEFINITION ====================================//

//================ TYPEDEF STRUCT/UNION DATA TYPE DEFFINITION ===============//
typedef struct tm_reg_cb_tag {
	tm_out_cb_t*	cb;
	uint16_t		interval;
	uint16_t		param_cb;
}tm_reg_cb_t;

typedef struct tm_reg_tag {
	tm_out_cb_t*	cb;
	uint16_t		interval;
	uint16_t		cnt;
	uint16_t		en;
	uint16_t		param;
}tm_reg_t;

//================ EXTERN FUNCTION ==========================================//

//================ EXTERN FUNCTION POINTER ==================================//
//
//================ EXTERN VARIABLE ==========================================//
//
//================ EXTERN QUEUE =============================================//

//================ END OF FILE ==============================================//
#endif
//#ifndef SM_TIMER_H
