//================ File Despciption =========================================//
//=== File name : sm_timer.h
//=== 
//===========================================================================//

#ifndef TIMER_H
#define TIMER_H

//================ Include Header ===========================================//
#include <stdint.h>
#include "stm32f0xx_tim.h"
//================ PULBIC DEFINE ============================================//
//----- Parameter define
//================ PUBLIC MACRO =============================================//
//
//================ TYPEDEF DATA TYPE DEFINITION =============================//
typedef void TimerCallback_t(uint8_t param);
//================ ENUMERATOR DEFINITION ====================================//
typedef enum TimeOutEvent_tag {
	CHAR_TIMEOUT = 0,
	RSP_TIMEOUT,
	SEC_TIMEOUT,
	TIMEOUT_MAX
}TimeOutEvent_t;
//================ TYPEDEF STRUCT/UNION DATA TYPE DEFFINITION ===============//

typedef struct TimeOutReg_tag{
	TimerCallback_t*	Callback;
	uint8_t			Interval;
	uint8_t			Count;
	uint8_t			Enable;
	uint8_t			CallbackParameter;
}TimeOutReg_t;

//================ EXTERN FUNCTION ==========================================//
void TimerInit(void);
void TimerResetCounter(void);
void TimerStart(void);
void TimerInterrupt(void);
void SetTimeOutCallBack(TimeOutEvent_t Event, uint8_t Interval,
		TimerCallback_t* Callback);
void EnableTimeOut(TimeOutEvent_t Event, uint8_t Cmd);
void SetTimeOut(TimeOutEvent_t Event,uint8_t Interval);
void ResetTimeCounter(TimeOutEvent_t Event);

//================ EXTERN FUNCTION POINTER ==================================//
//
//================ EXTERN VARIABLE ==========================================//
//
//================ EXTERN QUEUE =============================================//

//================ END OF FILE ==============================================//
#endif
//#ifndef SM_TIMER_H
