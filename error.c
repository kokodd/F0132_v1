#include	"error.h"
#include	"LCM.h"


void error_WARNING(unsigned char error_situation) {
	
	LCM_Remove_Display(0);
	
	switch( error_situation ) {
	
		case Meter_disconnect:					LCM_Print_Char_Function(2," Meter_disconnect ");				break;
		
	}
}
