#ifndef LCM_H
#define LCM_H

/**LCM 串行數據控制格式	(	詳閱.LCM說明文件 )
	* 1111,1ABC
	* A ：'High'表示數據由LCD到MCU、'Low'表示數據由MCU到LCD (這裡我們使用'LOW')
	* B ：'High'表示數據為[顯示數據]、'Low'表示數據為[控制數據]
	* C ：固定為'0'
*/

#define LCM_Select_Control 0	//選擇LCM為[控制狀態]的情況
#define LCM_Select_Dispaly 1	//選擇LCM為[顯示狀態]的情況


/*---LCM 主要控制函式----*/
void	LCM_Basic_Setting(signed char	Select, signed char	 Address);	//LCM___R/W(SID) 控制函式

/*---LCM 功能控制函式----*/
void	LCM_Display_Function(unsigned char		FUN_);	//LCM_顯示效果選擇
void	LCM_Row_Function(unsigned char		ROW_);	//LCM_段落切換
void	LCM_Remove_Display(unsigned char	ROW_);	//LCM清除螢幕顯示

/*---LCM 顯示內容控制函式----*/
int	LCM_Print_Char_Function(unsigned int	ROW_, unsigned char	PRINT_[]);		//顯示字串符號，並回傳輸入字串長度
void LCM_Print_Number_Function(unsigned int ROW_, float Number); 	  				//顯示數字

/*---LCM 效果控制函式----*/
#define MOV_Right  1
#define MOV_Left  2

void	LCM_Effect_Function(unsigned char	Eff_);	//LCM 效果



#endif