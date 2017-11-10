#include <stdint.h>		//路徑：C:\Keil_v5\C51\INC\SiLABS\shared\si8051Base
#include <stdlib.h>
#include <stdio.h>
#include <REG_MPC89L51-515.h>

/*==== 132 Function ====*/
#include "CPLD.h"
#include "LCM.h"
#include "EPROM.h"
#include "Interrupt.h"
#include "RS232.h"
#include "main.h"
#include "Input.h"
#include "error.h"
#include "Motor.h"


/*====	繁/簡體中文字標頭檔		====*/
//#include "LCM_BIG5.h"
//#include "LCM_GB2312.h"

/*====	其他標頭檔	====*/
#include "delay.h" //延遲函式
#include "other.h" //其他功能

/*====	測試UART用全域變數	====*/
int UART_flag = 0;

//unsigned char TEXT[4];
//unsigned char TEXT_CO = 0;


/*===================================*/

void main ( void ) {
		
	/*====  Keil C 變數需宣告於開頭		====*/
//		char	Text[] = "Hello UART!";
		unsigned char XXX = 0,	YYY	=	0;
		int ZZZ = 0;

	/*====  初始化函式	====*/
		/**投幣器致能**/
//		Enable_Pin(COIN_1);
	
		/**電子碼表致能**/
//		Enable_Pin(METER_CS);

		/**Interrupt**/
		INT_Interrupt_Set();
	
	/*====  LCM	測試====*/
	/**	開啟LCM顯示效果使用	**/
		LCM_Display_Function(1);  //顯示
//		LCM_Display_Function(2);  //顯示+開啟游標
	
	/**	全形字體顯示	**/
//		LCM_Print_Char_Function(1, LCM_BIG5_String);
	
	/**	半形字體顯示	**/
//		LCM_Print_Char_Function(1, );
//		LCM_Print_Char_Function(2, "Hello 2");
//		LCM_Print_Char_Function(3, "Hello 3");
	
	/**	數字顯示	**/
//		LCM_Print_Number_Function(4,3345678);

	/*====  EPROM	測試	====*/
//		EPROM_Test(); //執行時間太久12 sec

	/*====  8051中斷(Interrupt)測試====*/	
//		EA = EX1 = 1; //外部觸發 INT1
//		LCM_Print_Number_Function(2,555);
		
//		while(1) {
//			for(i=0; i<10; i++){
//					LCM_Print_Number_Function(2,i);
//					delay100ms(5);
//			}
//		}
	/*==== UART 測試 ====*/
//		RS232_Basic_Setting(); //開啟UART
		
	/**	RS232 寫入測試	**/
//		RS232_Write(Text); 
//		delay100ms(10);
		
	/**	RS232 讀取測試	**/
//		while(1) {
//			
//			//等待中斷傳輸完畢，旗標為1時，LCM再顯示
//			if( UART_flag == 1 ) {
//						LCM_Print_Char_Function(3,TEXT);
//						UART_flag = 0;
//				}
//		}

	/*====	output 測試		====*/
	/**	LED控制：直接查pdf-output，對照pdf-CPLD直接控制	**/
	/**	腳位拉High，輸出為Low，所以要接零件的負極	**/

		//cpld_out(0x75,1); //LED亮
		//cpld_out(0x75,0); //LED熄	
	
	/*====	Motor 測試		====*/
	//DC_test_Motor(DC_Motor_01, REV);


	/**  Motor：按鈕+按鈕控制( 按鈕自訂 ) **/
	/**	JP5_PT1   = 電眼	 **/
	/**	GOOD2     = 按鈕	 **/
	/**	JP5_GOOD1 = 近接	 **/
	
	while(1) {

			if( Input_Pin_Data(JP5_PT1) == 0 ) {
				DC_test_Motor(DC_Motor_01, STOP);
				DC_test_Motor(DC_Motor_02, STOP);
				DC_test_Motor(DC_Motor_03, STOP);
				DC_test_Motor(DC_Motor_04, STOP);
			}
 
			else if( Input_Pin_Data(JP5_GOOD1) == 1 ) {
				DC_test_Motor(DC_Motor_01, FWD);
				DC_test_Motor(DC_Motor_02, FWD);
				DC_test_Motor(DC_Motor_03, FWD);
				DC_test_Motor(DC_Motor_04, FWD);
			}
			else if( Input_Pin_Data(JP5_GOOD1) == 0 ) {
				DC_test_Motor(DC_Motor_01, REV);
				DC_test_Motor(DC_Motor_02, REV);
				DC_test_Motor(DC_Motor_03, REV);
				DC_test_Motor(DC_Motor_04, REV);
			}


	}
	


	
	/*====	input 測試		====*/
		//LCM_Print_Number_Function(3,XXX); 
//		while(1) {

//			YYY	=	Input_Hold_Detect(GOOD2);
				
			/**	按鈕持續ON/OFF	**/
//				LCM_Print_Number_Function(3,XXX);
//				LCM_Print_Number_Function(1,YYY);

//			if( Input_Pin_Data(JP5_GOOD1) == 1 ) {
//					//LCM_Print_Char_Function(1, "BUTTON OFF");
//					cpld_out(0x75,0); //LED OFF
//					cpld_action();
//					//XXX++;
//			}
//			else if( Input_Pin_Data(JP5_GOOD1) == 0 ) {
//					//LCM_Print_Char_Function(1, "BUTTON ON");	
//					cpld_out(0x75,1);	////LED ON
//					cpld_action();
//					//XXX = 0;
//			}
			
				/**	按鈕保持測試	**/
//			if( Input_Pin_Data(JP5_GOOD1) == 1 ) {

//					XXX	=	0;
//					YYY	=	0;
//			}
//			else if( Input_Pin_Data(JP5_GOOD1) == 0 &&	YYY	<	5	) {

//					XXX++;
//					delay100ms(8);
//					YYY++;
//			}
//			else if(	Input_Pin_Data(JP5_GOOD1) == 0	&&	YYY	>=	5	)	{
//					XXX++;
//			}

				/**	按鈕只偵測一次	**/
//			XXX = YYY;
//			YYY = Input_Pin_Data(GOOD2);
//			
//			if( XXX	== 1	&&	YYY	== 0 ) {
//					
//					Meter_ADD(METER_A);
//					Meter_ADD(METER_B);
//					Meter_ADD(METER_C);

//			}
		
//		}

		/**	 電眼測試	 **/
//		while(1) {
//			if( Input_Pin_Data(JP5_PT1) == 0 ) {
//				cpld_out(0xB3,1); //LED亮
//			}
//			else if( Input_Pin_Data(JP5_PT1) == 1 ) {
//				cpld_out(0xB3,0); //LED熄
//			}
//		}

		
		
		/*====	不離開main	====*/
		/**	8051會自己重複執行 main 的程式	**/
		while(1);
		
}//main end


	/*====  UART中斷測試		====*/
//void UART_timer1(void) interrupt 4 {
//	
//		//LED ON
//		cpld_out(0xB3,1);
//		cpld_action();

//		
//		TEXT[TEXT_CO] = RS232_Read();
//		TEXT_CO++ ;
//	
//		
//		if(TEXT_CO == 5) { 
//			
//			TEXT_CO = 0;
//			//讀取時使用旗標的方式，等待中斷資料傳輸完畢，再輸出
//			UART_flag = 1;
//		
//		}
//	
//		//LED OFF
//		cpld_out(0xB3,0);
//		cpld_action();

//}

	/*====	Timer0 計時中斷測試		====*/
void MY_timer0(void) interrupt 1 {
		
		/**  計時中斷變數宣告  **/
//		static int test_flag = 0;
		TH0 = TH_M1;
		TL0 = TL_M1;
	
		/**	測試計時中斷是否作用	**/
//	if(UART_flag == 1 ) {
//		cpld_out(0xB3,1); 	//LED亮		
//	}
//	else if( UART_flag == 500 ){
//		cpld_out(0xB3,0); 	//LED熄
//	}
//	else if( UART_flag == 1000 ){
//		UART_flag = 0;
//	}
//	UART_flag++;
	
		/**	投幣器測試	**/
		//Coin_Function();
		
		
		/**	電子碼表+投幣器	**/
		/**Coin_Rate 設定指定的電子暫存投幣比率**/
//		if(	Coin_Function() == 1) { 
//			
//			test_flag = 1;	//偵測到投幣時 test_flag=1 執行電子碼錶函式
//			
//		//設定電子碼錶匯率(偵測到一次投幣 +X 次)
//			Coin_Rate.MeterA = 2; //投一個硬幣 電子碼錶A+2
//			Coin_Rate.MeterB = 1;	//投一個硬幣 電子碼錶B+1
//			Coin_Rate.MeterC = 1;
//		}
		
//		if( test_flag == 1 ) {
//			
//				Meter_ADD( &Coin_Rate.MeterA, &Coin_Rate.MeterB, &Coin_Rate.MeterC);	//執行電子碼錶累加
//			
//			//判斷電子碼錶函式是否執行完畢
//				if( Meter_ADD( &Coin_Rate.MeterA, &Coin_Rate.MeterB, &Coin_Rate.MeterC) == 1) {
//					
//				//如果執行完畢：
//					test_flag =0; //旗標拉LOW，等待下一次投幣判斷	
//				}	
//		}

}

	/*====	Timer1 計時中斷測試		====*/
void MY_timer1(void) interrupt 3 {
		
		/**  計時中斷變數宣告  **/

		/**  中斷計時設定  **/
		TH1 = TH_M1;
		TL1 = TL_M1;
	
		/**	測試計時中斷是否作用	**/
//	if(UART_flag == 1 ) {
//		cpld_out(0xB3,1); 	//LED亮		
//	}
//	else if( UART_flag == 500 ){
		//cpld_out(0xB3,0); 	//LED熄
//	}
//	else if( UART_flag == 1000 ){
//		UART_flag = 0;
//	}
//	UART_flag++;

	
		/**	 PWM 控制	 **/
	
	
}