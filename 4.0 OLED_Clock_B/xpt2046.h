 
 
#ifndef XPT2046_H
#define XPT2046_H
#include "def.h"


sbit AD7843_CS=P6^2;         //Ƭѡ	 
sbit AD7843_isClick=P6^3;    //�жϴ������Ƿ��£�����ֵ����1ʱ����



struct TFT_Pointer			  //�������������Ľṹ�庯��  ��ҪӦ���� �Բɼ���ADֵ X Y  ���Ƿ��д������������ı�־λflag
{
 u16 x;
 u16 y;
 u8 flag;
};


struct T_i
{
 short xi;          //x ��������
 short yi;          //y ��������
 short a;		  //x ƫ����
 short b;	   	  //y ƫ����
};

struct TFT_Pointer TFT_Cm();     //TFT ����������





#endif
