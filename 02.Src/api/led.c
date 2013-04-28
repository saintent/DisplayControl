//================ File Despciption =========================================//
//=== File name : gpio.c
//===========================================================================//

//================ Index ====================================================//
//
//================ Include Header ===========================================//
#include "led.h"
#include "stm32f0xx_gpio.h"
//================ PUBLIC METHOD ============================================//
// extern function
//
//================ PUBLIC DATA ==============================================//
// extern data
//
//================ PRIVATE METHOD ===========================================//
// non extern function

//================ PRIVATE DATA =============================================//
// non extern data
uint8_t displayData[5][8] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1 },		// M Row 2
		{ 1, 1, 1, 1, 1, 1, 1, 1 },		// M ROw 1
		{ 1, 1, 1, 1, 1, 1, 1, 1 },		// Status
        //A  B  C  D  E  F  G DP
		{ 1, 1, 1, 1, 1, 1, 1, 1 },		// Digit 1
		{ 1, 1, 1, 1, 1, 1, 1, 1 }		// Digit 2
};

uint16_t DispDataRowPin[8] = { ROW1_PIN, ROW2_PIN, ROW3_PIN, ROW4_PIN,
		ROW5_PIN, ROW6_PIN, ROW7_PIN, ROW8_PIN
};

GPIO_TypeDef * DispDataRowPort[8] = { ROW_PORT, ROW_PORT, ROW_PORT, ROW_PORT,
		ROW_PORT, ROW_PORT, ROW_PORT, ROW_PORT };

uint16_t DispDataColumnPin[3] = { COLUMN1_PIN, COLUMN2_PIN, COLUMN3_PIN };

uint16_t Segment7Pin[8] = { A_PIN, B_PIN, C_PIN, D_PIN,
		E_PIN, F_PIN, G_PIN, DP_PIN };

uint16_t Segment7ComPin[2] = { COM1_PIN, COM2_PIN };

GPIO_TypeDef * Segment7Port[8] = { A_PORT, B_PORT, C_PORT , D_PORT,
		E_PORT, F_PORT, G_PORT, DP_PORT };
GPIO_TypeDef * Segment7ComPort[2] = { COM1_PORT, COM2_PORT };

LedCtr_t LedControl;
//================ PRIVATE DEFINE ===========================================//
#define DISPLAY_PORT		GPIOB

//================ PRIVATE MACRO ============================================//
//
//================ SOURCE CODE ==============================================//
void LedInit(void) {
	GPIO_InitTypeDef GpioInit;

	// Dp status init
	GpioInit.GPIO_Mode = GPIO_Mode_OUT;
	GpioInit.GPIO_OType = GPIO_OType_PP;
	GpioInit.GPIO_PuPd = GPIO_PuPd_UP;
	GpioInit.GPIO_Speed= GPIO_Speed_Level_1;
	GpioInit.GPIO_Pin = DP_STA_PIN;
	GPIO_Init(DP_STA_PORT, & GpioInit);

	// 7 Segment
	GpioInit.GPIO_Pin = C_PIN | DP_PIN | E_PIN | D_PIN;
	GPIO_Init(GPIOB, & GpioInit);
	GpioInit.GPIO_Pin = F_PIN | G_PIN | B_PIN | A_PIN;
	GPIO_Init(GPIOC, & GpioInit);

	// LED status
	GpioInit.GPIO_Pin = ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN
			| ROW5_PIN | ROW6_PIN | ROW7_PIN | ROW8_PIN
			| COLUMN1_PIN | COLUMN2_PIN | COLUMN3_PIN;
	GPIO_Init(GPIOB, & GpioInit);

	GpioInit.GPIO_OType = GPIO_OType_OD;
	GpioInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GpioInit.GPIO_Pin = COM1_PIN | COM2_PIN;
	GPIO_Init(GPIOC, & GpioInit);

	// Init state
	LedControl.LedState = M_ROW2;
	LedControl.Segment7State = DIGIT1;
}

void LedCmd(LedType_t Type, uint8_t Where, LedCmd_t Cmd) {
	displayData[Type][Where] = Cmd;
}

void WriteValue(GPIO_TypeDef** Port, uint16_t* Pin, uint8_t* Src) {
	for(uint8_t i = 0; i < 8; i++) {
		if(Src[i] == 0) {
			GPIO_ResetBits(Port[i], Pin[i]);
		}
		else {
			GPIO_SetBits(Port[i], Pin[i]);
		}
	}
}

void LedProcess(void) {
	uint8_t dump[8] = { 0 };

	WriteValue(DispDataRowPort, DispDataRowPin, &dump[0]);
	// Led status Process
	switch (LedControl.LedState) {
		case M_ROW2 :
			// Open Column
			GPIO_ResetBits(COLUMN_PORT, DispDataColumnPin[COLUMN_3]);
			GPIO_SetBits(COLUMN_PORT, DispDataColumnPin[COLUMN_1]);

			// Open Row
			WriteValue(DispDataRowPort, DispDataRowPin, &displayData[M_ROW2][0]);

			// Go to M_ROW1
			LedControl.LedState = M_ROW1;
			break;
		case M_ROW1 :
			// Open Column
			GPIO_ResetBits(COLUMN_PORT, DispDataColumnPin[COLUMN_1]);
			GPIO_SetBits(COLUMN_PORT, DispDataColumnPin[COLUMN_2]);

			// Open Row
			WriteValue(DispDataRowPort, DispDataRowPin, &displayData[M_ROW1][0]);

			// Go to Status led
			LedControl.LedState = STATUS_LED;
			break;
		case STATUS_LED :
			// Open Column
			GPIO_ResetBits(COLUMN_PORT, DispDataColumnPin[COLUMN_2]);
			GPIO_SetBits(COLUMN_PORT, DispDataColumnPin[COLUMN_3]);

			// Open Row
			WriteValue(DispDataRowPort, DispDataRowPin, &displayData[STATUS_LED][0]);

			// Go to M_ROW2
			LedControl.LedState = M_ROW2;
			break;
		case DUM1 :
			GPIO_ResetBits(COLUMN_PORT, DispDataColumnPin[COLUMN_3]);
			LedControl.LedState = M_ROW2;
			break;
		default:
			LedControl.LedState = M_ROW2;
			break;
	}

	// 7 Segment Process
	WriteValue(Segment7Port, Segment7Pin, &dump[0]);
	switch (LedControl.Segment7State) {
		case DIGIT1 :
			// Open Column
			GPIO_ResetBits(Segment7ComPort[0], Segment7ComPin[0]);
			GPIO_SetBits(Segment7ComPort[1], Segment7ComPin[1]);

			// Open Row
			WriteValue(Segment7Port, Segment7Pin, &displayData[DIGIT1][0]);

			// Go to DIGIT2
			LedControl.Segment7State = DIGIT2;
			break;
		case DIGIT2 :
			// Open Column
			GPIO_ResetBits(Segment7ComPort[1], Segment7ComPin[1]);
			GPIO_SetBits(Segment7ComPort[0], Segment7ComPin[0]);

			// Open Row
			WriteValue(Segment7Port, Segment7Pin, &displayData[DIGIT2][0]);

			// Go to DIGIT1
			LedControl.Segment7State = DIGIT1;
			break;
/*		case DUM1:
			GPIO_ResetBits(Segment7ComPort[0], Segment7ComPin[0]);
			LedControl.Segment7State = DIGIT1;
			break;
		case DUM2 :
			LedControl.Segment7State = DIGIT1;
			break;*/
		default:
			LedControl.Segment7State = DIGIT1;
			break;
	}

}
//================ END OF FILE ==============================================//
