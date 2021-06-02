
#include  "stc8.h"
#include  "gui.h"
#include  "tft.h"
#include  "delay.h" 
#include  "zifu8x16.h"			
#include  "hz16x16.h"		  //����16X16
#include "oled.h"
////��ʾ���ּ��ַ�  ������ʾ
////x1 y1 ��ʾ�ĳ�ʼλ��
////*str Ҫ��ʾ������
////dcolor ��ʾ���� �ַ�����ɫ
////bgcolor ��ʾ���� �ַ��ı�����ɫ  ��֧�ֱ�����Ļ����ɫ
void GUI_sprintf_hzstr16h(u8 x1,u16 y1,u8 *str,u16 dcolor,u16 bgcolor)	  
{  
	 u8 l=0;
	while(*str)
	{	
	  if(*str<0x80)		  //С��128   ascii ����������
	  {	  
		GUI_sprintf_char(x1,y1+l*8,*str,dcolor,bgcolor,1);
		l+=1;
		str++;
		}
	  else
	  {	  
	   //GUI_sprintf_hz1616(x1,y1+l*8,(u8*)str,dcolor, bgcolor,1);
			str+=2;l+=2;
	  }
	}	
}


//��ʾ�����ַ��� ������ʾ
//x1 y1 ��ʾ�ĳ�ʼλ��
//*str Ҫ��ʾ������
//dcolor ��ʾ�ַ�����ɫ
//bgcolor ��ʾ�ַ��ı�����ɫ  
void GUI_sprintf_hzstr16x(u8 x1,u16 y1,u8 *str,u16 dcolor,u16 bgcolor)	  
{  
	 u8 l=0;
	while(*str)
	{	
	  if(*str<0x80)		  //С��128   ascii ����������
	  {	  
		GUI_sprintf_char(x1+l*8,y1,*str,dcolor,bgcolor,0);
		l+=1;
		str++;
		}
	  else
	  {	  
	   //GUI_sprintf_hz1616(x1+l*8,y1,(u8*)str,dcolor, bgcolor,0);
			str+=2;l+=2;
	  }
	}	
}


//��ʾӢ�Ļ������ַ�
//����֧�� �ַ�������ͺ�����ʾ ��Ҫ���ɨ�跽ʽ��
//x  y  Ҫ��ʾ�ַ��ĳ�ʼ����
//value ��ʾ�ַ�����
//dcolor ��ʾ���ַ���ɫ  bgcolor��ʾ�ַ��ı�����ɫ
//mode   0 �ַ�������ʾ  1 �ַ�������ʾ
void GUI_sprintf_char(u8 x,u16 y,u8 value,u16 dcolor,u16 bgcolor,u8 mode)	
{  
	u8 i,j;
	u8 *temp=zifu816;    //temp��*temp�ĵ�ַ  ����temp����zifu���׵�ַ 
 	                    
	temp+=(value-32)*16;   //ȷ��Ҫ��ʾ��ֵ
				           //��ascii��  ǰ32��asciiû�д���zifu���� ����Ҫ��32
	                       //ÿ���ַ���16���ֽ���ʾ �����ڳ���16  ���Ƕ�Ӧ����ʾλ���׵�ַ

	  if(mode==0)Address_set(x,y,x+7,y+15);    //��������		   
	  if(mode==1)Address_set(x,y,x+7,y+15); //��������   		    
		for(j=0;j<16;j++)
		{
			for(i=0;i<8;i++)		    //�Ⱥ�ɨ
			{ 		     
			 	if((*temp&(1<<(7-i)))!=0)		   //��1 ���� Ȼ���Ӧλ�������� 				
				  Lcd_Write_Data(dcolor);		   //��ʾ�ַ���ɫ
				 
				else				
				  Lcd_Write_Data(bgcolor);		   //��ʾ������ɫ		
			}
			temp++;								   //��һ�ֽ�
		 }


}

////ֻ��ʾ10λ����
//void number10(u8 x,u16 y,u16 dat)	//���� Ҫ��ʾ������	 
//{	
//	OLED_ShowChar(x,y,dat/10%10+'0');
//	OLED_ShowChar(x+8,y,dat%10+'0');
//}

	