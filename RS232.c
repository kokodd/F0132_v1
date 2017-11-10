#include <string.h>
#include <REG_MPC89L51-515.h>
#include "RS232.h"


//#include "main.h"

void RS232_Basic_Setting(void) {

	IE 	 = 0x90;	//中斷致能暫存器。開啟中斷功能
	TMOD = 0x20;  //計時計數器模式暫存器。這裡使用T1、Mode2 : 8位元自動載入計時/計數器
	SCON = 0x50;	//串列埠控制暫存器。(SM0[SMOD0]=0、SM1=1) 8bits UART(可變)、(REN=1)串列接收致能ON
	TH1	 = 0xFD;	//Timer1。TCLK時脈設定，rate=9600 for 11.0592MHz
	TL1	 = 0xFD;
	TR1	 = 1;			//啟動Timer1
	
	TI 	 = 0;			//TI=1時，傳出完成，清除TI旗標
	RI 	 = 0;			//RI=1時，接收完成，清除RI旗標
	
}

void RS232_Write(char SEND_DATA[]) {

	signed char  xdata RS232_i = 0;
	signed short xdata SEND_DATA_length;
	SEND_DATA_length = strlen(SEND_DATA);
	
	for (RS232_i = 0; RS232_i < SEND_DATA_length; RS232_i++) {
			SBUF = SEND_DATA[RS232_i];  //將buffer內容送至SBUF傳送出去
			while (TI != 1); 						//判斷TI是否等於1(傳送完畢)，否則停在此行
			TI = 0;
	}

}

char RS232_Read(void) {
	 char Read_text;
	
	if (RI == 1) {	//RI=1時，接收完成，清除RI旗標
			Read_text = SBUF;
			RI = 0;
	}
	return Read_text;
}