#include <stdint.h>	//路徑：C:\Keil_v5\C51\INC\SiLABS\shared\si8051Base
#include <stdio.h>
#include <stdlib.h>	//function：動態記憶體配置
#include <string.h> //function：strlen


#include "CPLD.h"
#include "LCM.h"
#include "other.h"
#include "delay.h"



/**	LCM_Basic_setting 說明：R/W(SID) 控制函式
	*
	*	Select：命令LCM執行-->控制指令、顯示指令
	*	Address：8位元數據(高4位與低4位)，指令輸入(1Bytes) 
	*	 #Address 可直接丟"字串"、'字元'(英文&符號)，LCM會自行判斷
	*
***/
void LCM_Basic_Setting(signed char  Select, signed char  Address) {

			signed char  decide_8bits = 0; //輸入訊號是否為 8bits
	
			unsigned char LCM_command; //LCM_Basic_Setting 專用暫存變數(儲存SID控制位址)
			unsigned char LCM_address; //LCM_Basic_Setting 專用暫存變數(儲存SID高4,低4位址)
	
			/**===== R/W、E 腳位控制 =====
				* R/W = SID : 	配合SCLK的輸入訊號，一次輸入一個位元訊號
				*   cpld_out(LCM_SID,OR);   --> SID = '1'	
				*		cpld_out(LCM_SID,AND);  --> SID = '0'
				*
				*	E = SCLK  ：	脈波訊號，配合R/W的位元資料輸入
				*  	cpld_out(LCM_SCLK,OR);   --> E = '1'	
				*	 	cpld_out(LCM_SCLK,AND);  --> E = '0'
			**/
	
			cpld_out(LCM_SID,AND);	//SID->'0'
				//cpld_action(); //立刻執行(立即將暫存於變數的值，輸出到該腳位址)
	
			// LCM_1：ON
			cpld_out(LCM_CS,OR); //CS = '1'
				//cpld_action();
			
			/*==== 開始輸入訊號進入LCM ====*/
			
			switch( Select ) {
				case LCM_Select_Control:	LCM_command = 0xF8;	break;	//LCM為[控制狀態]
				case LCM_Select_Dispaly:	LCM_command	= 0xFA;	break;	//LCM為[顯示狀態]	
				
				default :	LCM_command = Select;	break;
			}
			
			/*----第1字節： LCM串口控制格式 (8 bits)----*/
			for(decide_8bits = 7; decide_8bits >= 0; decide_8bits--) {
			
					if( (LCM_command & (0x01 << decide_8bits) ) >> decide_8bits == 1 )	cpld_out(LCM_SID,OR);  //SID = '1'
						else cpld_out(LCM_SID,AND);	//SID = '0'
									//cpld_action();
				
						//打E(SCLK)脈波訊號
							cpld_out(LCM_SCLK,OR);	//SCLK = '1'
								//cpld_action();
							cpld_out(LCM_SCLK,AND);	//SCLK = '0'
								//cpld_action();
			}
			
			/*----第2字節： 8位數據的 高4位元 (DDDD,0000)----*/
			LCM_address = (0xF0 & Address);
			for(decide_8bits = 7; decide_8bits >= 0; decide_8bits--) {
					
					if( (LCM_address & (0x01 << decide_8bits)) >> decide_8bits == 1 )	cpld_out(LCM_SID,OR);	//SID = '1'
						else cpld_out(LCM_SID,AND);	//SID = '0'
									//cpld_action();
				
						//打E(SCLK)脈波訊號
							cpld_out(LCM_SCLK,OR); 	//SCLK = '1'
								//cpld_action();
							cpld_out(LCM_SCLK,AND); //SCLK = '0'
								//cpld_action();
			}
			
			/*----第3字節： 8位數據的 低4位元 (0000,DDDD)----*/
			LCM_address = (0x0F & Address) << 4;
			for(decide_8bits = 7; decide_8bits >= 0; decide_8bits--) {
					
					if( (LCM_address & (0x01 << decide_8bits)) >> decide_8bits == 1 )	cpld_out(LCM_SID,OR);	//SID = '1'
						else cpld_out(LCM_SID,AND);	//SID = '0'
									//cpld_action();
				
						//打E(SCLK)脈波訊號
							cpld_out(LCM_SCLK,OR);	//SCLK = '1'
								//cpld_action();
							cpld_out(LCM_SCLK,AND); //SCLK = '0'
								//cpld_action();
			}
			
			
			// LCM_1：OFF
			cpld_out(LCM_CS,AND); //CS = '0'
				//cpld_action();
	
}

/**	
	*		LCM 功能選擇函式
**/

//	LCM_Display_Function 說明：LCM_顯示效果選擇
//-------文字顯示------
//	1.顯示功能 ON 一次就可以持續使用了，等到結束在OFF。
//-------文字左右移動------
//	1. 整體左、右移需先使用：LCM_Print_Char_Function 再使用 LCM_Display_Function 左右移功能。
//	2. 整體左移、右移：一次會移動整個字串，如果要做到smooth要將字串拆成字元來位移???
//
//
void LCM_Display_Function(unsigned char  FUN_) {

		switch(FUN_) {
			case 0 : 	LCM_Basic_Setting (LCM_Select_Control, 0x08);	break;	//顯示功能OFF
			case 1 :	LCM_Basic_Setting (LCM_Select_Control, 0x0C);	break;	//顯示功能ON
			case 2 :	LCM_Basic_Setting (LCM_Select_Control, 0x0E);	break;	//顯示+開啟游標 (游標 '___')
			case 3 :	LCM_Basic_Setting (LCM_Select_Control, 0x0D);	break;	//顯示+開啟游標位置反白
			case 4 :	LCM_Basic_Setting (LCM_Select_Control, 0x0F);	break;	//開啟顯示+游標+游標反白
		}
}



//	LCM_RowCH_Function 說明：LCM_段落切換 (說明書P9.為漢字顯示座標)
//===	
//===	絕對位置：LCM_Basic_Setting( LCM_Select_Control , 1 AC6~AC0) 
//===	AC6~AC0 為每一行的指定位置
//===
void LCM_Row_Function(unsigned char  ROW_) {

		switch(ROW_) {
			case 1 : 	LCM_Basic_Setting (LCM_Select_Control, 0x80);	break;	//Row 1
			case 2 :	LCM_Basic_Setting (LCM_Select_Control, 0x90);	break;	//Row 2
			case 3 :	LCM_Basic_Setting (LCM_Select_Control, 0x88);	break;	//Row 3
			case 4 :	LCM_Basic_Setting (LCM_Select_Control, 0x98);	break;	//Row 4
		}
}




//===LCM_Print_Char_Function 說明：顯示字串符號，並回傳輸入字串長度
//===	
//===	ROW_ : 顯示段落選擇
//===	PRINT_[] : array 輸入顯示資料 (LCM可顯示：中字--> 4行*8個；	英文--> 4行x16個 ) 
//===		輸入內容註記：
//===					1.	TAB會顯示 "o"

int LCM_Print_Char_Function(unsigned int ROW_, unsigned char	PRINT_[]) {	
	
		int  PRINT_length = 0,	count_length = 0; //紀錄顯示內容長度、計算文字長度
	
		PRINT_length  =  strlen(PRINT_); //判斷 PRINT_ 資料長度
	
		LCM_Row_Function(ROW_); //選擇顯示於第幾行
	
	
		//送入文字，並判斷是否需要'換行'
		while (count_length < PRINT_length) {
		
				LCM_Basic_Setting (LCM_Select_Dispaly, PRINT_[ count_length++ ]); //將文字個別送入LCM
				
					//判斷這行文字是否滿16位元
					if ( count_length %16 == 0 ) {
							//如果滿了則 ROW_ +1(跳下一行)，等到在一次滿再+1，直到第4行後，跳回第一行
							if ( ++ROW_ > 4)	ROW_ = 1;	
									LCM_Row_Function(ROW_);
					}
		}

		//雖然LCM字串輸入時，未滿16位元LCM會自動用空格補滿16位元，
		//但是為了 LCM_Remove_Display 清除單行字串時使用，不需單行清除時，此while迴圈可不使用
		//當count_length除於16之餘數不等於0時
		//(最後使用16個空格代替了此函式)
		
		/*
		while (count_length %16 != 0) {
			
			LCM_Basic_Setting (LCM_Select_Dispaly,  ' ');  //LCM_Basic_Setting 可直接判斷符號，'空格'表示輸入空格符號。
			count_length++; //直到此行填滿16位元為止
		}
		*/
		
		return  PRINT_length; //回傳輸入字串長度
}


//===LCM_Print_Number_Function 說明：顯示數字 (輸入Number無法使用：bit型態)
void LCM_Print_Number_Function(unsigned int ROW_, float Number) {

		char xdata *Number_length;  //動態記憶體指標
		int  xdata  arrLen = 30; 		//動態記憶體：配置空間大小
		
	/** 動態記憶體主程式 **/
		init_mempool( &Number_length, arrLen *sizeof(char) );	//初始化記憶體位置
	
		Number_length = malloc ( arrLen *sizeof(char) ); 			//取得記憶體空間
		
		other_loat_to_string(Number, Number_length); 					//任意數字轉字串

		LCM_Print_Char_Function( ROW_, Number_length); 				//LCM輸出
	
	/**	釋放記憶體空間	**/
		free(Number_length);

}

//===LCM_Remove_Display 清除顯示內容
//===	
void LCM_Remove_Display(unsigned char	ROW_) {
		
		switch(ROW_) {
				case 0 : 	LCM_Basic_Setting(LCM_Select_Control, 0x01);	 break; 	//清除全部內容...
				case 1 : 	LCM_Print_Char_Function(1, "                ");	 break; //只清除第一行
				case 2 :	LCM_Print_Char_Function(2, "                ");	 break; //只清除第二行
				case 3 :	LCM_Print_Char_Function(3, "                ");	 break; //只清除第三行
				case 4 :	LCM_Print_Char_Function(4, "                ");	 break; //只清除第四行
		}
}




//===LCM_Effect_Function  LCM 效果指令
//
void LCM_Effect_Function( unsigned char	Eff_ )	{

		//LCM_Basic_Setting(LCM_Select_Control, 0x30); //LCM功能設定：開啟8bit控制介面 & RE=0 只使用基本指令 (RE=1 使用擴充指令)
		//LCM_Basic_Setting(LCM_Select_Control, 0x06); //游標右移
	
			switch(Eff_) {
				case MOV_Right:	LCM_Basic_Setting (LCM_Select_Control, 0x1C);	break;	// 字串向右移動
				case MOV_Left	:	LCM_Basic_Setting (LCM_Select_Control, 0x18);	break;	// 字串向左移動
				
				case 3 :	// 字串開頭反白(反白範圍：2 bits)
									LCM_Basic_Setting (LCM_Select_Control, 0x80);	//反白位置( 初始設定 80H 位置 )
									LCM_Basic_Setting (LCM_Select_Control, 0x0D);	//開啟反白
																																			break;
				
				//ing....
		}

		
		
}
