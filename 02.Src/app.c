//================ File Description =========================================//
//=== File name : app.c
//=== 
//===========================================================================//


//================ Index ====================================================//
//
//================ Include Header ===========================================//
#include "app.h"
#include "system.h"
#include "string.h"
#include "at_command.h"
#include "uart.h"
#include "bt.h"
#include "timer.h"
//================ PUBLIC METHOD ============================================//
// extern function from another file
//
//================ PRIVATE METHOD ===========================================//
// non extern function
//
//================ PUBLIC DATA ==============================================//
// extern data
//
//================ PRIVATE DATA =============================================//
// non extern data
AppControl_t 		AppControl;
//================ PRIVATE DEFINE ===========================================//
#define CMD_TYPE		0
#define RSP_TYPE		1
#define RESEND_MAX		3
//================ PRIVAE MACRO ============================================//
#define CREATE_RSP_SUCC	memcpy(AppControl.TxData, "\r\nOK\r\n", 6)
#define CREATE_RSP_FAIL	memcpy(AppControl.TxData, "\r\nERROR\r\n", 9)
//================ SOURCE CODE ==============================================//

void BTCmd(BTName_t Name, BTPress_t Press) {
	uint8_t cmdLn = 10;
	switch (Name) {
		case RM_BT :
			if(Press) {
				memcpy(AppControl.TxData, "AT*BTRM=0\r", 10);
			}
			else {
				memcpy(AppControl.TxData, "AT*BTRM=1\r", 10);
			}
			break;
		case L_BT :
			if(Press) {
				memcpy(AppControl.TxData, "AT*BTLT=0\r", 10);
			}
			else {
				memcpy(AppControl.TxData, "AT*BTLT=1\r", 10);
			}
			break;
		case U_BT :
			if(Press) {
				memcpy(AppControl.TxData, "AT*BTUP=0\r", 10);
			}
			else {
				memcpy(AppControl.TxData, "AT*BTUP=1\r", 10);
			}
			break;
		case D_BT :
			if(Press) {
				memcpy(AppControl.TxData, "AT*BTDW=0\r", 10);
			}
			else {
				memcpy(AppControl.TxData, "AT*BTDW=1\r", 10);
			}
			break;
		case R_BT :
			if(Press) {
				memcpy(AppControl.TxData, "AT*BTRT=0\r", 10);
			}
			else {
				memcpy(AppControl.TxData, "AT*BTRT=1\r", 10);
			}

			break;
		case MODE_BT :
			if(Press) {
				memcpy(AppControl.TxData, "AT*BTMF=0\r", 10);
			}
			else {
				memcpy(AppControl.TxData, "AT*BTMF=1\r", 10);
			}
			break;
		case EN_BT :
			if(Press) {
				memcpy(AppControl.TxData, "AT*BTENT=0\r", 11);
			}
			else {
				memcpy(AppControl.TxData, "AT*BTENT=1\r", 11);
			}
			cmdLn = 11;
			break;
		case HOME_BT :
			if (Press) {
				memcpy(AppControl.TxData, "AT*BTHM=0\r", 10);
			}
			else {
				memcpy(AppControl.TxData, "AT*BTHM=1\r", 10);
			}
			break;
		case RST_BT :
			if (Press) {
				memcpy(AppControl.TxData, "AT*BTRST=0\r", 11);
			}
			else {
				memcpy(AppControl.TxData, "AT*BTRST=1\r", 11);
			}
			cmdLn = 11;
			break;
	}
	AppControl.TxLen = cmdLn;
	UartSend(AppControl.TxData, cmdLn);
	AppControl.ReSend = 0;
	// Start Time out
	EnableTimeOut(RSP_TIMEOUT, ENABLE);

}

void VerifyCmd(uint8_t* Data) {
	uint8_t isSucc = 0;
	if((memcmp(Data, (const char*)"AT*DP", 5) == 0)) {
		isSucc = DPCmd(&AppControl.RxData[6]);
		if(isSucc) {
			CREATE_RSP_SUCC;
			UartSend(AppControl.TxData, 6);
                        AppControl.TxLen = 6;

		}
		else {
			CREATE_RSP_FAIL;
			UartSend(AppControl.TxData, 9);
                        AppControl.TxLen = 9;

		}
	}
	else {
		// Command Error
		CREATE_RSP_FAIL;
		UartSend(AppControl.TxData, 9);
                AppControl.TxLen = 9;
	}
}

void DataRecHandler(uint8_t Incomming) {
	if(!AppControl.Status.IsStartPackage) {
		if(Incomming == 'A') {
			AppControl.RxPtr = 0;
			AppControl.RxData[AppControl.RxPtr++] = Incomming;
			AppControl.Status.RecPackageType = CMD_TYPE;
			AppControl.Status.IsStartPackage = TRUE;
			EnableTimeOut(CHAR_TIMEOUT, ENABLE);
		}
		else if (Incomming == '\r') {
			AppControl.RxPtr = 0;
			AppControl.RxData[AppControl.RxPtr++] = Incomming;
			AppControl.Status.RecPackageType = RSP_TYPE;
			AppControl.Status.IsStartPackage = TRUE;
			EnableTimeOut(CHAR_TIMEOUT, ENABLE);
		}
	}
	else if (AppControl.Status.IsStartPackage) {
		ResetTimeCounter(CHAR_TIMEOUT);
		AppControl.RxData[AppControl.RxPtr++] = Incomming;
		if(AppControl.Status.RecPackageType == CMD_TYPE) {
			if(Incomming == '\r') {
				VerifyCmd(AppControl.RxData);
				AppControl.Status.IsStartPackage = 0;
				EnableTimeOut(CHAR_TIMEOUT, DISABLE);
			}
		}
		else {
			if(Incomming == '\n') {
				if((memcmp(AppControl.RxData, (const char*)"\r\nOK\r\n", 6) != 0)) {
					// Stop response time out
					EnableTimeOut(RSP_TIMEOUT, DISABLE);
					EnableTimeOut(CHAR_TIMEOUT, DISABLE);
					AppControl.Status.IsStartPackage = 0;
				}
				else if ((memcmp(AppControl.RxData, (const char*)"\r\nERROR\r\n", 9) != 0)){
					// Stop response time out
					EnableTimeOut(RSP_TIMEOUT, DISABLE);
					EnableTimeOut(CHAR_TIMEOUT, DISABLE);
					AppControl.Status.IsStartPackage = 0;
				}
			}
		}
	}
}

void TimeOutHandler(uint8_t Event) {
	if(Event == CHAR_TIMEOUT) {
		if( AppControl.Status.RecPackageType == CMD_TYPE) {
			VerifyCmd(AppControl.RxData);
			AppControl.Status.IsStartPackage = 0;
		}
		EnableTimeOut(CHAR_TIMEOUT, DISABLE);
	}

	if (Event == RSP_TIMEOUT) {
		// Re-send
		if(++AppControl.ReSend >= RESEND_MAX) {
			// Discard
			EnableTimeOut(RSP_TIMEOUT, DISABLE);
		}
		else {
			UartSend(AppControl.TxData, AppControl.TxLen);
			ResetTimeCounter(RSP_TIMEOUT);
		}
	}
}
//================ END OF FILE ==============================================//
