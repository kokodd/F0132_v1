#ifndef EPROM_H
#define EPROM_H

#define SO  P34
#define CS  P35
#define CLK P11
#define SI  P12

/** -----EPROM Basic----- **/
void EPROM_Writ_SPI(unsigned char Op_code);
unsigned char EPROM_Read_SPI(void);
void EPROM_Writ_Data8(unsigned int address,unsigned char Data);
void EPROM_Writ_Data16(unsigned int address,unsigned int Data);
unsigned char EPROM_Read_Data8(unsigned int address);
unsigned int EPROM_Read_Data16(unsigned int address);

/** -----EPROM Function----- **/
void EPROM_Test(void); //執行時間13 sec 太久

#endif

