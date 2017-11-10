#ifndef MUSIC_H
#define MUSIC_H

/*=======  使用者指令定義  ======*/

/*------------  6295 播放空間  ---------------*/
//**	音樂IC的ROM分成前、後各2M儲存空間			 **/
//**	6295一次只能使用2M(4個頻道)	的儲存空間 **/
#define Bank_1	0
#define Bank_2	1

/*------------  播放頻道定義  ---------------*/
#define Channel_01	0x08	//頻道1
#define Channel_02	0x10	//頻道2
#define Channel_03	0x20	//頻道3
#define Channel_04	0x40	//頻道4

/*------------  音量調節定義  ---------------*/
typedef enum {
	volume_15,	//0 = MAX
	volume_14,
	volume_13,
	volume_12,
	volume_11,
	volume_10,
	volume_09,
	volume_08,
	volume_07,
	volume_06,
	volume_05,
	volume_04,
	volume_03,
	volume_02,
	volume_01,
	volume_0,		//15 = MIN
}VOLUME;

/*------------  IC 選擇定義  ---------------*/
#define IC1	0
#define IC2	1
/*------------  其他定義  ---------------*/
#define ALL 3

/*=======   音樂控制函式  ======*/
//音樂播放
void Music_IC1_Play(unsigned char bank_ch, unsigned char chnnel_ch, unsigned char music_ch, unsigned char volume_ch);
void Music_IC2_Play(unsigned char bank_ch, unsigned char chnnel_ch, unsigned char music_ch, unsigned char volume_ch);

//確認頻道是否正在播放音樂
unsigned char Check_Music_Play(unsigned char IC_ch, unsigned char channel_ch);

//停止播放音樂
void Music_STOP(unsigned char channel_ch);


#endif

