#include	<REG_MPC89L51-515.h>
#include	"CPLD.h"
#include	"Input.h"
#include	"delay.h"
#include	"LCM.h"
#include	"error.h"


/**	input pin **/
unsigned char xdata INS000     _at_ 0xc000; //input的資料暫存器


/**	input 資料暫存變數 **/
typedef idata struct	{
	unsigned char kss3;
	unsigned char kss4;
	unsigned char kss5;
	unsigned char kss6;	
}INPUT;
INPUT my_input;


/**	input 暫存變數初始化	**/
void Input_Variable_Init(void)	{

			my_input.kss3 = 0;
			my_input.kss4 = 0;
			my_input.kss5 = 0;
			my_input.kss6 = 0;
}


/**  IO 致能  **/
void Enable_Pin(unsigned char Enable_name)	{
		
	switch(Enable_name) {
		
		case COIN_1:		cpld_out(0x86,1);		break;
		case METER_CS:		cpld_out(0x87,1);		break;
		case METER_A:		cpld_out(0x70,1);		break; 
		case METER_B:		cpld_out(0x71,1);		break; 
		case METER_C:		cpld_out(0x72,1);		break; 
		
	}
}//Enable END

/**  IO 禁能  **/
void Disable_Pin(unsigned char Disable_name) {

	switch(Disable_name) {
	
		case COIN_1:		cpld_out(0x86,0);		break;
		case METER_CS:		cpld_out(0x87,0);		break;
		case METER_A:		cpld_out(0x70,0);		break; 
		case METER_B:		cpld_out(0x71,0);		break; 
		case METER_C:		cpld_out(0x72,0);		break; 
	}

}//Disable END
/**	input 腳位重新命名(方便辨識) **/
bit Read_Data_from(unsigned char Pin_name)	{
	
	switch(Pin_name)	{
		case	COIN_1:		return P32;		break;		//JP2 第2腳
	}

}

/**		按鈕開關	 **/
/*-	Pin_name：輸入腳位名稱	-*/
bit Input_Pin_Data(unsigned char Pin_name)	{

	switch(Pin_name) {
		
		case HIT1: //由Input.h內宣告代號
			
				cpld_out(0x63,1);	//Input致能腳位選擇，0x63為KSS3	
				
				my_input.kss3 = INS000;	//將資料暫存器INS資料放到暫存變數 my_cpld.kss3 內儲存
				
				//如果開關按下後執行的動作超過彈跳時間，則不需要防彈跳
				if(	(my_input.kss3 & 0x20) == 0	)		delay1ms(20);	//防彈跳(debouncer)，需延遲20ms
					
				return (my_input.kss3 & 0x20);	/***	只需要HIT1腳位資料	(當開關ON時return 0，開關OFF時return 1)	***/
				/*		INS腳位會一次讀取kss3所有輸入的狀態，AND 0X20即可針對HIT1腳位是否有訊號輸入		*/
		break;
				
		case GOOD2: //由Input.h內宣告代號
			
				cpld_out(0x64,1);
		
				my_input.kss4 = INS000;	
		
				if(	(my_input.kss4 & 0x08) == 0	)		delay1ms(20);
		
				return (my_input.kss4 & 0x08); /***	只需要取得 GOOD2 腳位資料	***/
		break;
		
		case METER_A:  //電子碼錶，斷線檢知
		
				//需使用"Enable_Pin(METER_CS)"函式致能電子碼錶
		
				cpld_out(0x66,1);	//Input致能腳位選擇，0x66為KSS6
					
				//delay1ms(20);
				my_input.kss6 = INS000;	
		
				return (my_input.kss6 & 0x20); /***取得  RD5 腳位資料	***/
		break;
		
		case METER_B: 
				
				cpld_out(0x66,1);	//Input致能腳位選擇，0x66為KSS6
				
				my_input.kss6 = INS000;	
		
				return (my_input.kss6 & 0x40);/***取得	RD6 腳位資料	***/
		break;
				
		case METER_C:
				
				cpld_out(0x66,1);	//Input致能腳位選擇，0x66為KSS6
				
				my_input.kss6 = INS000;	
		
				return (my_input.kss6 & 0x80);/***取得	RD7 腳位資料	***/
		break;
		
		case JP5_PT1: //test:電眼腳位
			
				cpld_out(0x63,1);	//Input致能腳位選擇，0x63為KSS3	
				
				my_input.kss3 = INS000;	
				
				//如果開關按下後執行的動作超過彈跳時間，則不需要防彈跳
				if(	(my_input.kss3 & 0x01) == 0	)		delay1ms(20);	//防彈跳(debouncer)，需延遲20ms
					
				return (my_input.kss3 & 0x01);
		break;
		
		case JP5_GOOD1: //test:近接開關腳位 (NPN型 0:ON(吸磁) 1:OFF )
			
				cpld_out(0x64,1);	//Input致能腳位選擇，0x63為KSS4	
				
				my_input.kss4 = INS000;	
				
				//如果開關按下後執行的動作超過彈跳時間，則不需要防彈跳
				if(	(my_input.kss4 & 0x01) == 0	)		delay1ms(20);	//防彈跳(debouncer)，需延遲20ms
					
				return (my_input.kss4 & 0x04);/***取得 GOOD1_RD2 腳位資料	***/
		break;

	}
	
	return -1;
}


/**		投幣機	 **/
bit Coin_Function(void)	{
	
	static unsigned int Coin_Timer = 0;	//防釣魚計數(1ms)
	static unsigned char Coin_Flag = 0;	//是否投幣(0:無	1:有)

	if(	Read_Data_from(COIN_1)	== 0	)	{
		Coin_Timer++;	//當投幣機有訊號(0表示有硬幣投入)，則開始計數脈衝訊號持續時間
	}
	else	{
			if(	Coin_Timer	>=	5	 &&  Coin_Timer	<=	150	)	{
						Coin_Flag	=	1;	//如果脈衝訊號介於5~150ms之間則表示無釣魚，Coin_Flag為1
						Coin_Timer = 0;	//重置脈波計時變數，等待下一次投幣脈波偵測
			}
			//偵測到釣魚-禁能
			else if	(	Coin_Timer	>	150	)	{	
				Disable_Pin(COIN_1);//投幣器禁能
				Coin_Timer = 0;
				return -1;
			}
	}

	// Coin_Flag==1 : 偵測到投幣
	if(	Coin_Flag == 1	)	{
		Coin_Flag = 0;
		return 1;
	}
	
	return 0;
}

bit	Meter_ADD(char *Meter_A, char *Meter_B, char *Meter_C) {

	static char idata MeterTimer = 0;  //碼錶脈波計數
	
	 if( MeterTimer == 0 ) {
		
		 //檢查電子碼錶連接狀態
		 Meter_Online_Check();
		 
		 //如果 Meter_ 變數大於0，則將電子碼錶拉 High ，並開始計數
		 //電子碼錶只要拉 High 一次即可等待 LOW 狀態到來，狀態一次High、Low電子碼錶加1
		if( *Meter_A > 0 )	Enable_Pin(METER_A);
		if( *Meter_B > 0 ) 	Enable_Pin(METER_B);
		if( *Meter_C > 0 ) 	Enable_Pin(METER_C);
	 }
	 
	 MeterTimer++;
	 
	 //當High狀態持續30ms則狀態改LOW (Interrupt 1ms 偵測一次)
	 if( MeterTimer == 30 ) {
			 //偵測電子碼錶連接狀態，如果連結狀態沒問題，則將 Meter_ 變數減1
			 //如果 Meter_ 變數設定為2，減1之後變數為1，則脈波則會再Hight、Low一次 (此段程式為電子碼錶+2功能)
			if( Input_Pin_Data(METER_A) )	*Meter_A-=1;
			if( Input_Pin_Data(METER_B) )	*Meter_B-=1;
			if( Input_Pin_Data(METER_C) )	*Meter_C-=1;
		 
			 //狀態拉LOW
			Disable_Pin(METER_A);
			Disable_Pin(METER_B);
			Disable_Pin(METER_C);
	 }
	 
	 //脈波一次時間：60ms (High：30ms + LOW 30ms)
	 //60ms結束才會送下一次脈波(可避免電子碼錶因脈波High、Low太快偵測錯誤)
	 if( MeterTimer > 60 ) {
			 MeterTimer=0;
			 return 1;
	 }
	 
	 return -1;
}

void Meter_Online_Check(void) {
	
	//當電子碼錶，遭拔除，則會回傳該腳位"Input_Pin_Data()"的值：
	//Connect：回傳"0"、Disconnect：回傳"1"。(和按鈕開關相同)
	
		if( Input_Pin_Data(METER_A) == 1 || Input_Pin_Data(METER_B) == 1 || Input_Pin_Data(METER_C) ==1 ) {
				cpld_out(0xB3,1); //LED亮
		}
	

}
