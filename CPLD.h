#ifndef CPLD_H
#define CPLD_H

//腳位定義
/***********OT4000************/
#define	LCM_SCLK 0x46		/*--SCLK = E --*/
#define	LCM_SID	 0x47		/*--SID  = R/W--*/

/***********OTA000************/
#define LCM_CS	 0xA3		/*--CS = RS --*/

//邏輯運算
#define OR	1
#define AND	0


void cpld_variable_Init(void);
void cpld_action(void);
void cpld_out(unsigned char name, bit Logic);
//void cpld_direct_control(int SW);





/*============================================================================================*/
/*=== 定義一些類型，防止由於各種平臺和編譯器的不同，而產生的類型位元組數差異，方便移植。  ====*/
/*============================================================================================*/
typedef unsigned char BOOLEAN;			// Boolean value type  					

typedef unsigned long int UINT_32;	// Unsigned 32 bit value		註記：(=long)  類型是大於或等於 int 類型大小的整數類資料類型
typedef unsigned short UINT_16; 		// Unsigned 16 bit value		註記：(=short) 類型是大於或等於 char 類型大小，但短於或等於 int 類型大小的整數類資料類型。
typedef unsigned char UINT_8; 			// Unsigned 8 bit value			

typedef signed long int INT_32; 		// Signed 32 bit value			註記：由負號開始的long
typedef signed short INT_16;				// Signed 16 bit value			註記：由負號開始的short
typedef signed char INT_8; 					// Signed 8 bit value				註記：由負號開始的char

/*------------------------------------*/

#endif