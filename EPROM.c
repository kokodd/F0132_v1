#include <REG_MPC89L51-515.h>
#include <INTRINS.H>  // _nop_ 功能：暫停一個CPU的週期時間 

#include "EPROM.h"
#include "LCM.h"

/**	EPROM 型號：FM25C160ds 
/** 容量：2048 * 8 bits (000~7FFH * 一次可輸入8 bits資料量)
**/

/** -----EPROM SPI----- **/
unsigned char SPI_i;		//共用的i，絕不能平常呼叫，中斷又呼叫

void EPROM_Writ_SPI(unsigned char Op_code) {
	
	for( SPI_i = 0; SPI_i <= 7; SPI_i++ ) {
		
		SI = 0; //寫入0
		//一次輸入一個位元，利用AND保留輸入資料的其中一個位元資料
		if( ( Op_code & ( 0x80 >> SPI_i ) ) != 0 )	SI = 1; //寫入1
			
		CLK = 1; //Clock：打一個時脈，表示有一個位元資料要輸入
		CLK = 0;
	}
	
	SI = 0;
}

unsigned char EPROM_Read_SPI(void) {
	
	unsigned char Data = 0;
	
	for( SPI_i = 0; SPI_i <= 7; SPI_i++ ) {
		
		CLK = 1; //讀當前時脈的資料，與寫入資料不同，讀取時必須在時脈為高電位時讀取
		
			if( SO != 0 )	Data++; //+1，SO為EPROM輸出腳
		
		CLK = 0;
		
			if(SPI_i < 7)	Data <<= 1; //將Data資料全部左移 1bit (最後總共向左移動8 bits)
	
	}
	return Data;	
}

/** -----EPROM Writ----- **/
//**函式分為兩種功能：
//**  1. 一次寫入1個bytes(8 bits)  : char 
//**  2. 一次寫入2個bytes(16 bits) : int

void EPROM_Writ_Data8(unsigned int address,unsigned char Data) {	//unsigned char為8bits
  EA = 0; //8051定義腳位：0表示-禁止所有中斷功能、1表示-啟用中斷功能
	CS = 0;	//EPROM致能腳 (低準位智能)
	EPROM_Writ_SPI( 0x06 ); //EPROM Op-code開啟/關閉寫入功能 ("0x06" Set Write Enable、"0x04" Write Disable)
	CS = 1;
	
	_nop_();
	//_nop_();
	
	CS = 0;
	EPROM_Writ_SPI( 0x02 ); //EPROM Op-code(Write memory data)寫入資料指令
	
	//資料寫入：位址指定
	//位址有 2 Bytes (ex. 0x0234)
	EPROM_Writ_SPI( address >> 8 ); 	  //第一次寫入資料為：0x02	
	EPROM_Writ_SPI( address & 0x00ff ); //第二次寫入資料為：0x34
	
	//寫入要儲存的內容
	EPROM_Writ_SPI( Data );
	
	CS = 1;
	EA = 1;
}	

void EPROM_Writ_Data16(unsigned int address,unsigned int Data) {	//unsigned int為16bits
  EA = 0;
	CS = 0;
	EPROM_Writ_SPI( 0x06 );
	CS = 1;
	
	_nop_();
	_nop_();
	
	CS = 0;

	EPROM_Writ_SPI( 0x02 );
	EPROM_Writ_SPI( address >> 8 );
	EPROM_Writ_SPI( address & 0x00ff );
	
	//寫入第二次資料時，會自動換到下一個位址儲存(只要CS沒有為0)
	EPROM_Writ_SPI( Data >> 8 ); 		
	EPROM_Writ_SPI( Data & 0x00ff );
	
	CS = 1;
	EA = 1;
}

/** -----EPROM Read----- **/
unsigned int R_Data;

unsigned char EPROM_Read_Data8(unsigned int address) {	

	EA = 0;
	CS = 0;
	EPROM_Writ_SPI( 0x03 ); //EPROM Op-code(Read Memory Data) 讀取資料指令
	
	//寫入需讀取的位址
	EPROM_Writ_SPI( address >> 8 );		
	EPROM_Writ_SPI( address & 0x00ff );
	
	//取得寫入位址的資料
	R_Data = EPROM_Read_SPI(); 
	CS = 1; 
	EA = 1;
	return R_Data;
}

unsigned int EPROM_Read_Data16(unsigned int address)	{
  
	EA = 0;
	CS = 0;
	EPROM_Writ_SPI( 0x03 );
	EPROM_Writ_SPI( address >> 8 );
	EPROM_Writ_SPI( address & 0x00ff );
	
	R_Data = EPROM_Read_SPI();
	R_Data <<= 8;
	R_Data += EPROM_Read_SPI();
	CS = 1;
	EA = 1;
	return R_Data;
	
}

/** -----EPROM Function----- **/
void EPROM_Test(void) {
	
	unsigned short Test_address=0, Test_Record=0;//Test_address : 指定EPROM的位址、Test_Record : 紀錄EPROM位址裡的數值
	
	//EPROM總容量 2048 * 8bits (2048=0x0800)
	for(Test_address = 0x000; Test_address < 0x800; Test_address++) {
		
			//讀取EPROM位址資料，並由變數Test_Record承接此位址資料
			Test_Record = EPROM_Read_Data8(Test_address);
		
		//Step 02:
				//如果該位址的值原本就為0x55則:
			if (Test_Record == 0x55) {
				
					//將0xAA寫入FT指定之位址
					EPROM_Writ_Data8(Test_address, 0xAA);
					
					//接著讀取FT指定位址之資料，判斷是否為0xAA，如果不是，表示EPROM寫入故障，LCM顯示故障提示
					if (EPROM_Read_Data8(Test_address) != 0xAA)		LCM_Print_Char_Function(4,"ERPOM ERROR");
					
					//測試完EPROM後，回復 EPROM 原本的資料
					EPROM_Writ_Data8(Test_address, Test_Record);		 
			}
		//Step 01:
			else {
					//將0x55寫入指定位址(Test_address)
					EPROM_Writ_Data8(Test_address, 0x55);
					
					//接著讀取(Test_address)位址之資料，判斷是否為0x55，如果不是，表示EPROM寫入故障，LCM顯示故障提示
					if (EPROM_Read_Data8(Test_address) != 0x55)		LCM_Print_Char_Function(4,"ERPOM ERROR");
					
					//測試完EPROM後，回復 EPROM 原本的資料
					EPROM_Writ_Data8(Test_address, Test_Record);	
			}
	}
	
	LCM_Print_Char_Function(4,"ERPOM GOOD");
}
