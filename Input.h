#ifndef	INPUT_H
#define	INPUT_H
/*============================================================================*/
/*===================				MCU-132 輸入腳位讀取方式	 		====================*/
/*========	1. KSS：為輸入的致能腳，經由OT6000進行控制						 		========*/	
/*========				OT6000下指令給IC:V74273(pdf-CPLD)，V74273輸出KS腳位	========*/
/*========				由KS腳位控制IC:74LS245(pdf-Output)輸出到KSS腳位			========*/
/*========	2. INS：為輸入的狀態暫存器，由OTC000進行控制			 		 		========*/
/*========				INS會將選取的KSS腳位資料一次讀取，儲存到OTC000		  ========*/
/*========				但因為INS讀取的為全部的腳位資料，										========*/
/*========				如果要得到其中一支的腳位資料，需AND該腳位的數值			========*/
/*============================================================================*/

/*======  腳位代號宣告  ======*/

/**  輸入腳位  **/
typedef enum {
		HIT1,		//0		
		GOOD2,
		METER_A,
		METER_B,
		METER_C,
		JP5_PT1, //PT1已宣告使用(REG_MPC89L51-515.h)
		JP5_GOOD1, //近接開關 :Proximity Switch
	
}PIN_NAME;

/**  致能腳位  **/
typedef enum {
		COIN_1,
		METER_CS,
	
}ENABLE_NAME;

/**	 腳位命名(方便辨認)  **/
bit Read_Data_from(unsigned char Pin_name);
/**	暫存變數初始化	**/
void Input_Variable_Init(void);

/*============ 輸入函式 =============*/
/**	 按鈕開關(KSS)	 **/
bit Input_Pin_Data(unsigned char Pin_name);
/**  致能  **/
void Enable_Pin(unsigned char Enable_name);
/**  禁能  **/
void Disable_Pin(unsigned char Disable_name);
/**	 比較式-投幣機	**/
bit Coin_Function(void);
/**  電子碼表  **/
bit	Meter_ADD(char *Meter_A, char *Meter_B, char *Meter_C); //累加
void	Meter_Online_Check(void); //確認連接狀態

#endif