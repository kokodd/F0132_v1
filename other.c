/**=============其他功能==============
	* 撰寫日期：2017/08/18
*/

#include "other.h" 
//==========功能："數字"轉"字串"=========
/** Number on countu**/
int other_n_tu(int number, int count) {
    int result=1;
    while(count-- > 0)
    result *= number;   

    return result;
}

/***Convert float to string***/
void other_loat_to_string(float f, char r[]) {
	
    long int xdata length, length2, i, number, position, sign;
    float xdata number2;

    sign = -1;   // -1 == positive number
    if (f < 0) {
				sign = '-';
        f *= -1;    
    }   


    number2 = f;  
    number = f;
    length = 0;  // size of decimal part
    length2 = 0; //  size of tenth

    /* calculate length2 tenth part*/
    while( (number2 - (float)number) != 0.0 && !((number2 - (float)number) < 0.0) )
    {
         number2 = f * (other_n_tu(10.0, length2 + 1));
         number = number2;  

         length2++;
    }

    /* calculate length decimal part*/
    for(length = (f > 1) ? 0 : 1; f > 1; length++) 
        f /= 10;

    position = length;
    length = length + 1 + length2;
    number = number2;
		
    if(sign == '-') {
        length++;
        position++;
    }

    for(i = length; i >= 0 ; i--) {
        if(i == (length))
            r[i] = '\0';
        else if(i == (position))
            r[i] = '.';
        else if(sign == '-' && i == 0)
            r[i] = '-';
        else  
        {
            r[i] = (number % 10) + '0';
            number /=10;
        }
    }
}
