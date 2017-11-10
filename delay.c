/**=============延遲函式==============**/
/** 頻率：11.0592M Hz                 **/
#include "delay.h"


//void delayus(void) {
//   unsigned char i;
//   for (i = 0; i <= 10; i++);
//}

void delay1us(unsigned char k) {
   unsigned char i;
   for (i = 0; i <= 10*k; i++);
}

void delay1ms(unsigned char k) {
  unsigned char i, j;
  for (j = 0; j < k; j++)
    for (i = 0; i <= 151; i++);
		
}

void delay100ms(unsigned char r) {
	unsigned char i, j, k;
  for (k = 0; k < r; k++)
	for (j = 0; j < 100; j++)
		for (i = 0; i <= 152; i++);
} 