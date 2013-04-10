//================ File Despciption =========================================//
//=== File name : at_command.c
//=== 
//===========================================================================//


//================ Index ====================================================//
//
//================ Include Header ===========================================//
#include "stdint.h"
#include "string.h"
#include "led.h"
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
//
//================ PRIVATE DEFINE ===========================================//
//
//================ PRIVATE MACRO ============================================//
//
//================ SOURCE CODE ==============================================//

void LedScan(LedType_t Des, uint8_t Data) {
	for(uint8_t i = 0; i < 8; i++) {
		if(Data & (1 << i)) {
			LedCmd(Des, i, LED_ON);
		}
		else {
			LedCmd(Des, i, LED_OFF);
		}
	}
}

uint8_t DPCmd(uint8_t* data) {
	// 7-Segment
	if(data[0] == '0') {
		// Digit 1
		LedScan(DIGIT1, data[1]);
		// Digit 2
		LedScan(DIGIT2, data[3]);
	}
	// Led Status
	else if(data[0] == '1') {
		// Status Led
		LedScan(STATUS_LED, data[1]);
		// M Row 1
		LedScan(M_ROW1, data[3]);
		// M Row 2
		LedScan(M_ROW2, data[5]);
	}
	else {
		// Error
		return 0;
	}
	return 1;
}

//================ END OF FILE ==============================================//
