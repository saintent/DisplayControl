//================ File Description =========================================//
//=== File name : bt.c
//=== 
//===========================================================================//


//================ Index ====================================================//
//
//================ Include Header ===========================================//
#include "bt.h"
#include "system.h"
//================ PUBLIC METHOD ============================================//
// extern function from another file
//
//================ PRIVATE METHOD ===========================================//
// non extern function
void DumCallback(BTName_t bt);
//================ PUBLIC DATA ==============================================//
// extern data
//
//================ PRIVATE DATA =============================================//
// non extern data
uint8_t Count[9] = { 0 };
BTCallBack_t*	BTCallBack = DumCallback;
//================ PRIVATE DEFINE ===========================================//
#define DECISION_TIME		200
//================ PRIVATE MACRO ============================================//
//
//================ SOURCE CODE ==============================================//
void BTInit(void) {
	GPIO_InitTypeDef GpioInit;

	// Config as in put
	GpioInit.GPIO_Mode = GPIO_Mode_IN;
	GpioInit.GPIO_OType = GPIO_OType_PP;
	GpioInit.GPIO_PuPd = GPIO_PuPd_DOWN;
	GpioInit.GPIO_Speed= GPIO_Speed_Level_1;
	GpioInit.GPIO_Pin = REM_MAN_SW_PIN | LEFT_SW_PIN | DW_SW_PIN | UP_SW_PIN;
	GPIO_Init(GPIOC, & GpioInit);

	GpioInit.GPIO_Pin = RIGHT_SW_PIN | EN_SW_PIN | MODE_SW_PIN | HOME_SW_PIN;
	GPIO_Init(GPIOA, & GpioInit);
}

void DumCallback(BTName_t bt) {
	(void) bt;
}

void SetBTCallback(BTCallBack_t* cb) {
	BTCallBack = cb;
}

void BTProcess(void) {

	if(GPIO_ReadInputDataBit(REM_MAN_SW_PORT, REM_MAN_SW_PIN)) {
		if(++Count[RM_BT] >= DECISION_TIME) {
			BTCallBack(RM_BT);
			Count[RM_BT] = 0;
		}
	}
	else {
		Count[RM_BT] = 0;
	}

	if(GPIO_ReadInputDataBit(LEFT_SW_PORT, LEFT_SW_PIN)) {
		if(++Count[L_BT] >= DECISION_TIME) {
			BTCallBack(L_BT);
			Count[L_BT] = 0;
		}
	}
	else {
		Count[L_BT] = 0;
	}

	if(GPIO_ReadInputDataBit(DW_SW_PORT, DW_SW_PIN)) {
		if(++Count[U_BT] >= DECISION_TIME) {
			BTCallBack(U_BT);
			Count[U_BT] = 0;
		}
	}
	else {
		Count[U_BT] = 0;
	}

	if(GPIO_ReadInputDataBit(UP_SW_PORT, UP_SW_PIN)) {
		if(++Count[D_BT] >= DECISION_TIME) {
			BTCallBack(D_BT);
			Count[D_BT] = 0;
		}
	}
	else {
		Count[D_BT] = 0;
	}

	if(GPIO_ReadInputDataBit(RIGHT_SW_PORT, RIGHT_SW_PIN)) {
		if(++Count[R_BT] >= DECISION_TIME) {
			BTCallBack(R_BT);
			Count[R_BT] = 0;
		}
	}
	else {
		Count[R_BT] = 0;
	}

	if(GPIO_ReadInputDataBit(EN_SW_PORT, EN_SW_PIN)) {
		if(++Count[EN_BT] >= DECISION_TIME) {
			BTCallBack(EN_BT);
			Count[EN_BT] = 0;
		}
	}
	else {
		Count[EN_BT] = 0;
	}

	if(GPIO_ReadInputDataBit(MODE_SW_PORT, MODE_SW_PIN)) {
		if(++Count[MODE_BT] >= DECISION_TIME) {
			BTCallBack(MODE_BT);
			Count[MODE_BT] = 0;
		}
	}
	else {
		Count[MODE_BT] = 0;
	}

	if(GPIO_ReadInputDataBit(HOME_SW_PORT, HOME_SW_PIN)) {
		if(++Count[HOME_BT] >= DECISION_TIME) {
			BTCallBack(HOME_BT);
			Count[HOME_BT] = 0;
		}
	}
	else {
		Count[HOME_BT] = 0;
	}

	/*if(GPIO_ReadInputDataBit(RST_SW_PORT, RSP_SW_PIN)) {

	}
	else {

	}*/

}


//================ END OF FILE ==============================================//
