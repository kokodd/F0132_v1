#ifndef	MOTOR_H
#define	MOTOR_H

/**  宣告馬達控制，條件判斷使用  **/
#define FWD		1	//正轉
#define REV		2	//反轉
#define	STOP	3	//停

/** 馬達命名 **/
typedef enum {
	DC_Motor_01,	//0
	DC_Motor_02,
	DC_Motor_03,
	DC_Motor_04,

}MOTOR_NAME;

/**  馬達控制函式  **/
void DC_test_Motor(unsigned char Motor_NAME ,unsigned char Motor_command);



#endif