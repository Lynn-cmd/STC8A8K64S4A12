#ifndef TFT_H
#define TFT_H
#include "def.h"


#define  LCD_DataPortH P0     //��8λ���ݿ�
#define  LCD_DataPortL P7     //��8λ���ݿ�
sbit LCD_RS = P3^5;  	  //����/�����л�  ��0����д���� 1����д���ݣ�
sbit LCD_WR = P3^6;		  //д������
sbit LCD_RD =P3^7;		  //��ȡ����
sbit LCD_CS=P4^4;		  //Ƭѡ	
sbit LCD_RST=P4^3;	          //Ӳ����λ  

void Lcd_Init(void);   //��ʼ��

void Lcd_WR_Reg(u16 Data);   //��������
void Lcd_Write_Data(u16 Data); //��������
//void Lcd_WriteReg(u16 com,u16 val); //д�Ĵ���
void Address_set(u16 x1,u16 y1,u16 x2,u16 y2);//�������귶Χ
u16 LCD_readpoint(u16 x,u16 y);     //��ȡ����ɫ

void LCD_scan(u8 mode);

#endif
