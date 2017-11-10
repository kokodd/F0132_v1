#include <REG_MPC89L51-515.h>
#include "CPLD.h"
#include "delay.h"
#include "Music.h"

/** output port **/
unsigned char xdata	CS1_6295  _at_ 0x2000;  //CS1_6295
unsigned char xdata CS2_6295  _at_ 0x3000;	//CS2_6295

/**====		音樂IC控制 函式使用說明  ====**/
/** bank_ch		 ：	選擇 音樂IC儲存空間 ( Bank1 or Bank2 )											 							**/
/** channel_ch ：	選擇 播放頻道 ( Channel_01 ~ Channel_04 )  一個Bank有4個頻道	 						**/
/** music_ch	 ：	選擇 歌曲 ( 1 ~ 127 )，燒錄音樂.bin檔時已分配歌曲順序											**/
/** volume_ch  ：	選擇 播放音樂大小 ( 通常直接給MAX，由喇叭的旋鈕來調整聲音大小 ) 					**/

void Music_IC1_Play(unsigned char bank_ch, unsigned char channel_ch, unsigned char music_ch, unsigned char volume_ch) {

		unsigned char idata play;
	
	//選擇IC儲存空間(Bank1、Bank2)
		switch(bank_ch) {
    	case	Bank_1:	cpld_out(0xA1,0);   break;	//IC1 -> K1_6295 = 0 -> bank1
    	case	Bank_2:	cpld_out(0xA1,1);		break;	//IC1 -> K1_6295 = 1 -> bank2 
    }
		 				 
	/*--- VOICE_6294 = 音樂IC1控制腳位 ---*/
		
		/**  VOICE_6294 _8bits資料使用方式  																																			**/
		/**  功能1：輸出切換 + 切換頻道  																																					**/
		/** 			說明： bit7			bit6				bit5				bit4				bit3				bit2				bit1				bit0  	**/
		/** 						ON/OFF	Channel_4 	Channel_3		Channel_2		Channel_1			 -					 -					 -			**/	
		/**	 腳位名稱已宣告於 Music.h 請直接使用  																																**/
		
		CS1_6295 = channel_ch;	//bit7 = 0 ->先關閉指定頻道 (如果頻道有再使用的話)
		delay1us(7);
		
		/**  VOICE_6294 _8bits資料使用方式  																																			**/
		/**  功能2：輸出切換 + 選擇歌曲輸出																																				**/ 
		/** 			說明： bit7			bit6				bit5				bit4				bit3				bit2				bit1				bit0  	**/
		/** 						ON/OFF	 Music_6		 Music_5		 Music_4		 Music_3		 Music_2		 Music_1		 Music_0  **/
		/** bit7 ~ bit0 : 0111,1111 總共可儲存127首歌																															**/
		
		play = 0x80 | music_ch;	 // OR 0x80 可開啟音樂IC
		CS1_6295 = play;
		delay1us(7);
		
		/**  VOICE_6294 _8bits資料使用方式  																																			**/
		/**  功能3：頻道輸出 + 音量輸出																																						**/ 
		/** 			說明： bit7				bit6				bit5				bit4				bit3				bit2				bit1				bit0  **/
		/** 					Channel_4 	Channel_3		Channel_2		Channel_1		 volume3 		volume2			volume1			volume0	**/
		
		channel_ch = channel_ch << 1; 					// "chnnel_ch" 向左移 1bit + OR	"volume_ch" 才能符合功能3.的資料格式
		channel_ch |= volume_ch;		
		CS1_6295 = channel_ch;		//輸出

}

void Music_IC2_Play(unsigned char bank_ch, unsigned char channel_ch, unsigned char music_ch, unsigned char volume_ch) {

		unsigned char idata play;
	
	//選擇IC儲存空間(Bank1、Bank2)
		switch(bank_ch) {
    	case	Bank_1:	cpld_out(0xA4,0);   break;	//IC1 -> K2_6295 = 0 -> bank1
    	case	Bank_2:	cpld_out(0xA4,1);		break;	//IC1 -> K2_6295 = 1 -> bank2 
    }
		
		CS2_6295 = channel_ch;	//bit7 = 0 ->先關閉指定頻道 (如果頻道有再使用的話)
		delay1us(7);
		
		play = 0x80 | music_ch;	 // OR 0x80 可開啟音樂IC
		CS2_6295 = play;
		delay1us(7);
		
		channel_ch = channel_ch << 1; 					// "chnnel_ch" 向左移 1bit + OR	"volume_ch" 才能符合功能3.的資料格式
		channel_ch |= volume_ch;		
		CS2_6295 = channel_ch;		//輸出

}

/**====		確認音樂IC頻道使用狀態   ====**/
/** IC_ch		   ：	選擇 音樂IC ( "IC1 = CS1_6295" or "IC2 = CS2_6295" )			**/
/** channel_ch ：	選擇 要確認的頻道 ( Channel_01 ~ Channel_04 )  			 			**/
unsigned char Check_Music_Play(unsigned char IC_ch, unsigned char channel_ch) {
  
	unsigned char idata music_mode;
	
	switch(IC_ch) {
		
		case	IC1:
				music_mode = CS1_6295;	//無音樂播放 music_mode=0、4個頻道都再播放 music_mode=0x78 (0111,1000)
				music_mode = music_mode & channel_ch;	//"music_mode" AND "channel_ch" = 頻道是否使用中。(ch1=0x01,ch2=0x02,ch3=0x04,ch4=0x08)
		break;
		
		case	IC2:
				music_mode = CS2_6295;	
				music_mode = music_mode & channel_ch;	
		break;
	}
	
	return(music_mode);	
}

/**====		停止播放音樂   ====**/
/**channel_ch : 選擇要停止的頻道，無指定就是全部停止 **/
void Music_STOP(unsigned char channel_ch)	{

	switch(channel_ch) {

		case Channel_01: 
				CS1_6295 = channel_ch; //0xxx,x000 : channel x = 1 off
				CS2_6295 = channel_ch;
				delay1ms(1);
		break;
		
		case Channel_02: 
				CS1_6295 = channel_ch; //0xxx,x000 : channel x = 1 off
				CS2_6295 = channel_ch;
				delay1ms(1);
		break;
		
		case Channel_03: 
				CS1_6295 = channel_ch; //0xxx,x000 : channel x = 1 off
				CS2_6295 = channel_ch;
				delay1ms(1);
		break;
		
		case Channel_04: 
				CS1_6295 = channel_ch; //0xxx,x000 : channel x = 1 off
				CS2_6295 = channel_ch;
				delay1ms(1);
		break;
		
		default:
				CS1_6295 = 0x78;			//全頻道停止。0111,1000 : channel 1~4 off		
				CS2_6295 = 0x78;
				delay1ms(1);
		break;
	
	}

} 