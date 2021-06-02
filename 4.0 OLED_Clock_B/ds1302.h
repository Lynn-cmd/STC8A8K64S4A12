

#ifndef  __DS1302_H
#define  __DS1302_H
#include "def.h"

sbit SCK=P6^5;	//时钟	
sbit SDA=P6^6;	//数据	
sbit CE=P6^7;// DS1302复位

extern u8 ds1302tmp[7];//秒分时日月周年
void Set_RTC(void); //set RTC 
void ds1302_module(void);		//DS1302测试函数
void ds1302_scan(u8 x,u16 y,u8 mode);
void number10(u8 x,u16 y,u16 dat);	//坐标 要显示的数据
#endif


