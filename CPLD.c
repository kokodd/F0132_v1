#include <REG_MPC89L51-515.h>
#include "CPLD.h"
#include "delay.h"


/*==============================*/
/*===     CPLD 腳位宣告      ===*/
/*==============================*/

//_at_ 	用途：位址定義						說明：定義變數放置於資料記憶體的位置 (平時用的指標為系統隨機給位址)
//xdata	用途：記憶體模組區段宣告	說明：宣告8051外部資料記憶體(沒宣告xdata系統會直接給data)

/** output port **/
unsigned char xdata  OT4000   _at_ 0x4000;
unsigned char xdata  OT5000   _at_ 0x5000;
unsigned char xdata  OT6000   _at_ 0x6000;
unsigned char xdata  OT7000   _at_ 0x7000;
unsigned char xdata  OT8000   _at_ 0x8000;
unsigned char xdata  OT9000   _at_ 0x9000;
unsigned char xdata  OTA000   _at_ 0xA000;
unsigned char xdata  OTB000   _at_ 0xB000;



/** CPLD 暫存變數用 **/
typedef idata struct {
	unsigned char out4000;
	unsigned char out5000;				
	unsigned char out6000;			
	unsigned char out7000;
	unsigned char out8000;
	unsigned char out9000;	
	unsigned char outA000;			
	unsigned char outB000;
	
}CPLD;
CPLD my_cpld;

/*==============================*/
/*===     CPLD 函式控制      ===*/
/*==============================*/

void cpld_variable_Init(void) {
		my_cpld.out4000 = 0;
		my_cpld.out5000 = 0;
		my_cpld.out6000 = 0;
		my_cpld.out7000 = 0;
		my_cpld.out8000 = 0;
		my_cpld.out9000 = 0;
		my_cpld.outA000 = 0;
		my_cpld.outB000 = 0;
}

/** (1ms)將暫存的CLPD變數(my_cpld)直接輸出到該腳位 **/
void cpld_action(void) {
		OT4000 = my_cpld.out4000;
		OT5000 = my_cpld.out5000;
		OT6000 = my_cpld.out6000;
		OT7000 = my_cpld.out7000;
		OT8000 = my_cpld.out8000;
		OT9000 = my_cpld.out9000;
		OTA000 = my_cpld.outA000;
		OTB000 = my_cpld.outB000;
}

/**CPLD 輸出函式**/
/** name : 0XAB A=觸發IC腳位 B=要控制的IC腳位(第0~7腳)
/**	bit : 判斷是否為 0:AND(OFF結果) or 1:OR(ON結果)
*/
void cpld_out( unsigned char name, bit Logic) { 	

	unsigned char idata address, Bit;
	//ET1 = 0; 										//Timer1 致能中斷(中斷時使用的CPLD也是此函式)
	
	address = name>>4;						//取十位數：決定 V74154 腳位
	Bit = 0x01 << (name&0x0F);		//取個位數：控制的腳位編號(第幾支腳)
	
	switch( address ) {
		case 4: 
						if( Logic ) //if() 沒給條件，則0為Fault，其他數值為True
							my_cpld.out4000 |= Bit;	//開啟CPLD腳位
						else
							my_cpld.out4000 &= ~Bit; //"~" 反相：關閉CPLD腳位
						break;
		case 5: 
						if( Logic )
							my_cpld.out5000 |= Bit;
						else
							my_cpld.out5000 &= ~Bit;
						break;
		case 6: 
						if( Logic )
							my_cpld.out6000 |= Bit;
						else
							my_cpld.out6000 &= ~Bit;
						break;
		case 7: 
						if( Logic )
							my_cpld.out7000 |= Bit;
						else
							my_cpld.out7000 &= ~Bit;
						break;
		case 8: 
						if( Logic )
							my_cpld.out8000 |= Bit;
						else
							my_cpld.out8000 &= ~Bit;
						break;
		case 9: 
						if( Logic )
							my_cpld.out9000 |= Bit;
						else
							my_cpld.out9000 &= ~Bit;
						break;	
		case 10: 
						if( Logic )
							my_cpld.outA000 |= Bit;
						else
							my_cpld.outA000 &= ~Bit;
						break;
		case 11: 
						if( Logic )
							my_cpld.outB000 |= Bit;
						else
							my_cpld.outB000 &= ~Bit;
						break;
							//delay1ms(1000);
		default:
			break;
	}
	//ET1 = 1;	//Timer1 致能開啟
	cpld_action(); //立即執行
}

/*--直接對指定的CPLD進行控制 (用於測試程式)--*/
//unsigned char dir_con_buf;
//void cpld_direct_control(unsigned char SW) {

//	switch(SW) {
//	
//		case AND:	
//			dir_con_buf &= 0xF7;
//			OTB000 = dir_con_buf;
//		break;

//		case OR:
//			dir_con_buf |= 0x08;
//			OTB000 = dir_con_buf;
//		break;
//		
//		default:	
//			break;
//	}

//}


