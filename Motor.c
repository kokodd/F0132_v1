#include <REG_MPC89L51-515.h>
#include "CPLD.h"
#include "delay.h"
#include "Motor.h"


/**===================   		 	DC Motor 控制  	   ===================**/
/**  ON  ： 馬達致能腳位，1才能控制  													      **/
/**  CCW ： 馬達轉向控制，1:正轉、0:反轉        										**/
/**  STOP： 馬達立即停止(電容會釋放少許電壓，造成馬達不會立即停止)  **/
/**=================================================================**/
void DC_test_Motor(unsigned char Motor_NAME ,unsigned char Motor_command) {

	switch(Motor_NAME)	{
			
		case DC_Motor_01:
			
					switch(Motor_command) {
						/**	提醒：外接電源也會影響正反轉	**/
						case FWD: //正轉
							cpld_out(0xB2,1); //JP13 - 3 ON
							cpld_out(0xB3,0);	//JP13 - 4 CCW
							//cpld_out(0xB7,0);	//JP13 - 5 STOP
						break;
						
						case REV:	//反轉
							cpld_out(0xB2,0); //JP13 - 3 ON
							cpld_out(0xB3,1);	//JP13 - 4 CCW
							//cpld_out(0xB7,0);	//JP13 - 5 STOP			
						break;
						
						case STOP: //停止轉動
							cpld_out(0xB2,1); //JP13 - 3 ON
							cpld_out(0xB3,1);	//JP13 - 4 CCW
							//cpld_out(0xB7,1);	//JP13 - 5 STOP
						break;
					}
					
		break;
		
		case DC_Motor_02:
					switch(Motor_command) {
						
						case FWD: //正轉
							cpld_out(0xB4,1);
							cpld_out(0xB5,0);	
						break;
						
						case REV:	//反轉
							cpld_out(0xB4,0); 
							cpld_out(0xB5,1);	
						break;
						
						case STOP: //停止轉動
							cpld_out(0xB4,1);
							cpld_out(0xB5,1);	
						break;
					}
		break;
				
		case DC_Motor_03:
					switch(Motor_command) {
						
						case FWD: //正轉
							cpld_out(0xB6,1);
							cpld_out(0xB7,0);	
						break;
						
						case REV:	//反轉
							cpld_out(0xB6,0); 
							cpld_out(0xB7,1);	
						break;
						
						case STOP: //停止轉動
							cpld_out(0xB6,1);
							cpld_out(0xB7,1);	
						break;
					}
		break;
						
		case DC_Motor_04:
					switch(Motor_command) {
						
						case FWD: //正轉
							cpld_out(0x76,1);
							cpld_out(0x77,0);	
						break;
						
						case REV:	//反轉
							cpld_out(0x76,0); 
							cpld_out(0x77,1);	
						break;
						
						case STOP: //停止轉動
							cpld_out(0x76,1);
							cpld_out(0x77,1);	
						break;
					}
		break;
	}
	
}