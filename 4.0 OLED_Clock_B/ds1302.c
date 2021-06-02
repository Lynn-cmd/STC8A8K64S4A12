
//DS1302����
//���� ��ʾ ʱ�� ���� ���� ���� 
//�ɲ�ͣ������ʱ��
//�ɽ��д�������
#include "stc8.h" //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#include "ds1302.h"
#include "intrins.h"
#include "delay.h"
#include "oled.h"

code u8 write_rtc_address[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c}; //���ʱ�������� ���λ��дλ
code u8 read_rtc_address[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};  

u8 ds1302tmp[7]={30,26,14,2,6,3,20};//���ʱ��������


//дһ���ֽ� 
//temp Ҫд����ֽ�	 ����ַ�����ݣ�
void Write_Ds1302_Byte(u8 temp) 
{
 u8 i;
 for (i=0;i<8;i++)     	//ѭ��8�� д������
  { 
     SCK=0;
     SDA=temp&0x01;     //ÿ�δ�����ֽ� 
     temp>>=1;  		//����һλ
	 delay_us(40);
     SCK=1;
   }
}   

//д��DS1302����
//address д��ĵ�ַ
//dat     д�������
void Write_Ds1302( u8 address,u8 dat )     
{
 	CE=0;
	_nop_();
	delay_us(50);
 	SCK=0;
	_nop_();
	delay_us(50);
 	CE=1;						//����
   	_nop_();        
	delay_us(50);           
 	Write_Ds1302_Byte(address);	//���͵�ַ
 	Write_Ds1302_Byte(dat);		//��������
 	CE=0;  		            //�ָ�
}

//����DS1302����
//address ��ȡ���ݵĵ�ַ
//���� ��ȡ������ֵ
u8 Read_Ds1302 ( u8 address )
{
 	u8 i,temp=0x00;
 	CE=0;
	_nop_();
	_nop_();
	delay_us(50);
 	SCK=0;
	_nop_();
	_nop_();
	delay_us(50);
 	CE=1;
	_nop_();
	_nop_();
	delay_us(50);

 	Write_Ds1302_Byte(address);

 	for (i=0;i<8;i++) 		//ѭ��8�� ��ȡ����
 	{		
 		if(SDA)
 		temp|=0x80;			//ÿ�δ�����ֽ�
		SCK=0;
		temp>>=1;			//����һλ
		_nop_();
		delay_us(50);
	   _nop_();
	   _nop_();
 		SCK=1;
	} 

 	CE=0;
	_nop_();	          	//����ΪDS1302��λ���ȶ�ʱ��
 	_nop_();
	delay_us(50);
	CE=0;
	SCK=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	delay_us(50);
	SCK=1;
	_nop_();
	_nop_();
	delay_us(50);
	SDA=0;
	_nop_();
	_nop_();
delay_us(50);
	SDA=1;
	_nop_();
	_nop_();	delay_us(50);
	return (temp);			//����
}


//д��ʱ DCBת��	
//DS1302 ֻ���� DCB�� ����4λ��10λֵ ��4λ�Ÿ�λֵ
//add Ҫת���ĵ�ַ
//���� ת���������
u8 dcb_read(u8 add)
{
  u8 fla,fla2;
  fla=Read_Ds1302(add);
  fla2=((fla/16)*10)+(fla&0x0f);
  return fla2;	
}


//�趨ʱ������
//��Ҫ����ʱ��оƬ��� ���ʱ��������
void Set_RTC(void)		       //�趨 ����
{
	u8 i;

	for(i=0;i<7;i++)         //BCD����
	 ds1302tmp[i]=ds1302tmp[i]/10*16+ds1302tmp[i]%10;
	 
 	Write_Ds1302(0x8E,0X00);   //дʹ��
			
 	for(i=0;i<7;i++)		   //7��д�� ���ʱ��������
 	Write_Ds1302(write_rtc_address[i],ds1302tmp[i]);
	
    Write_Ds1302(0x8E,0x80);   //д��ֹ

}


//DS1302  ʱ�� ������ ���� ������ʾ����
//֧��ֻ��ʾʱ�� ����
//�˺�����Ҫѭ�� ���и��� �����Զ�����
//x y  ��ʾ��ʱ��ĳ�ʼ����  ��������������ʾ  ������ ������������ʾ
//��
//2013-12-12
//Friday
//20:25:32
//dcolor ������ɫ	  bgcolor  ������ɫ
//mode  Ϊ1ʱ ֧�� ������ ������ʾ  ���� ֻ��ʾʱ��
void ds1302_scan(u8 x,u16 y,u8 mode)
{
    u8 i;	
		OLED_ShowString(x+16,y,":");//��ʾ�� �� ʱ ֮��� ������	
		OLED_ShowString(x+40,y,":");
		for(i=0;i<3;i++)						  //��ʾDisplay ��  ��  ʱ
		 number10(x+24*i,y,dcb_read(0x85-i*2));
	
						 
	if(mode==1)		 //�ж� �Ƿ��� ���� ������ʾ modeΪ1��ʾ����
	 {				 
		switch(dcb_read(0x8b))					  //����
		{
		 case 7:
				OLED_ShowString(x,y+2,"Sunday");
				break;
		 case 1:
				OLED_ShowString(x,y+2,"Monday");
				break;
		 case 2:
					OLED_ShowString(x,y+2,"Tuesday");
				break;
		 case 3:
					OLED_ShowString(x,y+2,"Wednesday");
				break;
		 case 4:
					OLED_ShowString(x,y+2,"Thursday");
				break;
		 case 5:
					OLED_ShowString(x,y+2,"Friday");
				break;
		 case 6:
					OLED_ShowString(x,y+2,"Saturday");
				break;
		}
		
				OLED_ShowString(x,y+4,"20"); //��ʾ�� �� �� ֮��� ��-��
				OLED_ShowString(x+32,y+4,"-");
				OLED_ShowString(x+56,y+4,"-");

		 number10(x+16,y+4,dcb_read(0x8d));		 //��
		 number10(x+16+24,y+4,dcb_read(0x89));	 //��
		 number10(x+16+48,y+4,dcb_read(0x87));	 //��	                            
	 }
}


//ֻ��ʾ10λ����
void number10(u8 x,u16 y,u16 dat)	//���� Ҫ��ʾ������	 
{	
	OLED_ShowChar(x,y,dat/10%10+'0');
	OLED_ShowChar(x+8,y,dat%10+'0');
}