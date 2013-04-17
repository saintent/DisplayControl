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
void DumCallback(BTName_t bt, BTPress_t press);
//================ PUBLIC DATA ==============================================//
// extern data
//
//================ PRIVATE DATA =============================================//
// non extern data
ButtonStatus_t ButtonSta[9];
BTCallBack_t*	BTCallBack = DumCallback;
//================ PRIVATE DEFINE ===========================================//
#define DECISION_TIME		100
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

	GpioInit.GPIO_Pin = RST_SW_PIN;
	GPIO_Init(GPIOF, & GpioInit);

}

void DumCallback(BTName_t bt, BTPress_t press) {
	(void) bt;
	(void) press;
}

void SetBTCallback(BTCallBack_t* cb) {
	BTCallBack = cb;
}

void BTCheckSta(BTName_t Bt, uint8_t Sta) {
	if (!ButtonSta[Bt].Press) {
		// Detect when active high
		if(Sta) {
			if (++ButtonSta[Bt].Count >= DECISION_TIME) {
				ButtonSta[Bt].Press = TRUE;
				if (!ButtonSta[Bt].HadProcess) {
					BTCallBack(Bt, BT_PRESS);
					ButtonSta[Bt].HadProcess = TRUE;
				}
			}
		}
		else {
			ButtonSta[Bt].HadProcess = FALSE;
			ButtonSta[Bt].Count = 0;
		}
	}
	else {
		// Detect when active low
		if(!Sta) {
			if (++ButtonSta[Bt].Count >= DECISION_TIME) {
				ButtonSta[Bt].Press = FALSE;
				if (!ButtonSta[Bt].HadProcess) {
					BTCallBack(Bt, BT_RELEAS);
					ButtonSta[Bt].HadProcess = TRUE;
				}
			}
		}
		else {
			ButtonSta[Bt].HadProcess = FALSE;
			ButtonSta[Bt].Count = 0;
		}
	}
}

void BTProcess(void) {
	uint8_t IsPress;

	IsPress = GPIO_ReadInputDataBit(REM_MAN_SW_PORT, REM_MAN_SW_PIN);
	BTCheckSta(RM_BT, IsPress);

	IsPress = GPIO_ReadInputDataBit(LEFT_SW_PORT, LEFT_SW_PIN);
	BTCheckSta(L_BT, IsPress);

	IsPress = GPIO_ReadInputDataBit(DW_SW_PORT, DW_SW_PIN);
	BTCheckSta(D_BT, IsPress);

	IsPress = GPIO_ReadInputDataBit(UP_SW_PORT, UP_SW_PIN);
	BTCheckSta(U_BT, IsPress);

	IsPress = GPIO_ReadInputDataBit(RIGHT_SW_PORT, RIGHT_SW_PIN);
	BTCheckSta(R_BT, IsPress);

	IsPress = GPIO_ReadInputDataBit(EN_SW_PORT, EN_SW_PIN);
	BTCheckSta(EN_BT, IsPress);

	IsPress = GPIO_ReadInputDataBit(MODE_SW_PORT, MODE_SW_PIN);
	BTCheckSta(MODE_BT, IsPress);

	IsPress = GPIO_ReadInputDataBit(HOME_SW_PORT, HOME_SW_PIN);
	BTCheckSta(HOME_BT, IsPress);

	IsPress = GPIO_ReadInputDataBit(RST_SW_PORT, RST_SW_PIN);
	BTCheckSta(RST_BT, IsPress);

}


//================ END OF FILE ==============================================//
