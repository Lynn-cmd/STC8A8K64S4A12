

#ifndef  __DS1302_H
#define  __DS1302_H
#include "def.h"

sbit SCK=P6^5;	//ʱ��	
sbit SDA=P6^6;	//����	
sbit CE=P6^7;// DS1302��λ

extern u8 ds1302tmp[7];//���ʱ��������
void Set_RTC(void); //set RTC 
void ds1302_module(void);		//DS1302���Ժ���
void ds1302_scan(u8 x,u16 y,u8 mode);
void number10(u8 x,u16 y,u16 dat);	//���� Ҫ��ʾ������
#endif


