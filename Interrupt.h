#ifndef INT_H
#define INT_H

/*=========================================================*/
/*=============   8051計時器-時間計算方式   ===============*/
/*==========  當使用12MHz石英晶體                     =====*/
/*==========  計時器的計時頻率為12MHz/12=1MHz,T=1μs   =====*/
/*==========  表示計時單位每格1μs計數值就會+1         =====*/
/*===  每當0xFFFF再加1而變成0x0000時，會令溢位旗標TF0=1  ==*/
/*=========================================================*/
/*=========================================================*/
/*==  16 bits = 0xFFFF = 65536(10進制)                   ==*/
/*==  65536-50000 = 15536 = 0x3CB0                       ==*/
/*==  15536/256= 16進制 "3C"                             ==*/
/*==  15536%256= 16進制 "B0"                             ==*/
/*==  補充：																						 ==*/
/*==	取10進制的百、千位數"除以100"、取個、十位數"%100"  ==*/
/*==  10進制取16進制的前、後兩位數則是用256來除          ==*/
/*=========================================================*/

/**======  		設定 T0 計數時間     ======**/
/**   Mdoe1：16位元 & 計數範圍 0~65535 	 **/
/**	THx : 16位元 的 高8位元 (2^8 = 256)  **/
/** TLx	:	16位元 的 低8位元							 **/	
/**======================================**/

//#define num 50000								//50ms
//#define TH_M2 (65536-num)/256		
//#define TL_M2 (65536-num)%256

#define TH_M1	0xFC;	//1ms
#define TL_M1	0x66;

void INT_Interrupt_Set(void);

#endif