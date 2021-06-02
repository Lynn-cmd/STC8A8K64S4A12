#include "stc8.h"
#include "tft.h"
#include "delay.h"
#include "def.h"

//TFT���ݼ������
// u8 VH,u8 VL  д������� ��16λ ������8λ��ʾ  ���÷���P0 P2������Ӧ
void LCD_Writ_Bus(u8 VH,u8 VL)   //��������д�뺯��
{
    LCD_DataPortH=VH;	
	LCD_DataPortL=VL;		
	LCD_WR=0;
	LCD_WR=1; 
}

//��������
void Lcd_WR_Reg(u16 Data)	 
{	
    LCD_RS=0;
	LCD_Writ_Bus(Data>>8,Data);
}

//��������
void Lcd_Write_Data(u16 Data) 
{
    LCD_RS=1;
	LCD_Writ_Bus(Data>>8,Data);
}



////д�Ĵ���
////u16 com Ҫд������� u16 valҪд�������
//void Lcd_WriteReg(u16 com,u16 val)		   
//{
//	Lcd_WR_Reg(com);
//    Lcd_Write_Data(val);
//}

//�������귶Χ		
//x1 y1  ��ʼλ��
//x2 y2  ����λ��
void Address_set(u16 x1,u16 y1,u16 x2,u16 y2)
{	     
      //  xq=0;yq=0;
		Lcd_WR_Reg(0X2A); 
		Lcd_Write_Data(x1>>8); 
		Lcd_Write_Data(x1&0XFF);
		Lcd_Write_Data(x2>>8); 
		Lcd_Write_Data(x2&0XFF);

		Lcd_WR_Reg(0X2B); 
		Lcd_Write_Data(y1>>8); 
		Lcd_Write_Data(y1&0XFF);
		Lcd_Write_Data(y2>>8); 
		Lcd_Write_Data(y2&0XFF);
	    Lcd_WR_Reg(0X2C);      //��ʼд��GRAM
 
}


//void LCD_SetCursor(u16 Xpos, u16 Ypos)
//{	 
//		    
//		Lcd_WR_Reg(0X2A); 
//		Lcd_Write_Data(Xpos>>8); 
//		Lcd_Write_Data(Xpos&0XFF);	 
//		Lcd_WR_Reg(0X2B); 
//		Lcd_Write_Data(Ypos>>8); 
//		Lcd_Write_Data(Ypos&0XFF);
//	 
//} 
//
//
//void LCD_Clear(u16 color)
//{
//	u16 i,j;      
//	LCD_SetCursor(0x0000,0x0000);	//���ù��λ�� 
//	Lcd_WR_Reg(0X2C);      //��ʼд��GRAM
////	LCD_RS=1;	 	    
//    for(i=0;i<320;i++)
//	 {
//	  for (j=0;j<240;j++)
//	   	{
////        	P2=color>>8;	
////	        P0=color;		
////	        LCD_WR=0;
////      	    LCD_WR=1;  
//			Lcd_Write_Data(color);
//	    }
//
//	  }		
//
//
//} 


////����
////x,y:����
////POINT_COLOR:�˵����ɫ
//void LCD_DrawPoint(u16 x,u16 y,u16 color)
//{
//	LCD_SetCursor(x,y);		//���ù��λ�� 
//	Lcd_WR_Reg(0X2C);      //��ʼд��GRAM
//	Lcd_Write_Data(color);
//}

////��ILI93xx����������ΪBGR��ʽ��������д���ʱ��ΪRGB��ʽ��	 ��ʵ��֤���ֲ��ﲢû��˵����
////ͨ���ú���ת��
////c:BGR��ʽ����ɫֵ
////����ֵ��RGB��ʽ����ɫֵ
//u16 LCD_bgr2rgb(u16 c)
//{
//	u16  r,g,b,rgb;   
//	b=(c>>0)&0x1f;
//	g=(c>>5)&0x3f;
//	r=(c>>11)&0x1f;	 
//	rgb=(b<<11)+(g<<5)+(r<<0);		 
//	return(rgb);
//} 


//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
u16 LCD_readpoint(u16 x,u16 y)
{
	u16 color;
	u8 r=0,g=0,b=0;

//  	Lcd_WR_Reg(0x0020);		  //���ö���ɫ����
//	Lcd_Write_Data(x);	  
//    Lcd_WR_Reg(0x0021);
//	Lcd_Write_Data(y); 

	Lcd_WR_Reg(0X2A); 
	Lcd_Write_Data(x>>8); 
	Lcd_Write_Data(x&0XFF);	 
	Lcd_Write_Data(x>>8); 
	Lcd_Write_Data(x&0XFF);	

	Lcd_WR_Reg(0X2B); 
	Lcd_Write_Data(y>>8); 
    Lcd_Write_Data(y&0XFF);
	Lcd_Write_Data(y>>8); 
    Lcd_Write_Data(y&0XFF);


	Lcd_WR_Reg(0x2e);		           //���Ͷ���ɫ����

	P7M1=0XFF;						  //P7 P0������Ϊ������״̬ �ȴ�������ɫ����
	P7M0=0X00;
	P0M1=0XFF;
	P0M0=0X00;

	LCD_RS=1;						  //1Ϊ������
	//��ȡ����(��GRAMʱ,��Ҫ��2��)
	LCD_RD=0;					   	  //���ж�����
 	LCD_RD=1;
 	//dummy READ					  //��һ�ν���Ϊ��������  �ֲ�69ҳ �����
	delay_us(6);
	LCD_RD=0;					   
 	LCD_RD=1;
	r=P0;
	g=P7;
	delay_us(6);
	LCD_RD=0;					   
 	LCD_RD=1;
	b=P0;
		
//	color=P2;
//	color=(color<<8)|P0;	          //�ڶ��ζ�ȡ������ɫ����

    P7M1=0X00;						  //P7 P0����Ϊ˫��IO��  ���ָ�״̬��
	P7M0=0X00;
	P0M1=0X00;
	P0M0=0X00;

	color=(((u16)r>>3)<<11)|(((u16)g>>2)<<5)|((u16)b>>3);
	return color;
//	return LCD_bgr2rgb(color);		  //�Զ�ȡ����ɫ���� BGRתRGB	  
}



/*
9341ɨ���ص� ���ɨ�跽��ı�� ��ֱ�Ӹı�x y��ʼԭ��
�����ں�����ʾ��ʱ�� �Ͳ��ÿ��� x y�ı仯��Ľ�� ��Ϊԭ��Ҳ�����ı�
���ǿ���һ�ִ���ͨ��

*/

//tft������ɨ�跽ʽ����
//mode 1 -8  һ��8��ɨ�跽ʽ
//     1   ��>��  ��>�� 
//     2   ��>��  ��>��
//     3   ��>��  ��>��
//     4   ��>��  ��>�� 
//     5   ��>��  ��>��  
//     6   ��>��  ��>�� 
//     7   ��>��  ��>�� 
//     8   ��>��  ��>�� 
void LCD_scan(u8 mode)
{
 switch(mode)
 {
   case 1:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	Lcd_Write_Data(0x08); 	
    Lcd_WR_Reg(0X2C);      //��ʼд��GRAM			 
	break;
   case 2:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	Lcd_Write_Data(0x88); 
	Lcd_WR_Reg(0X2C);      //��ʼд��GRAM					 
	break;
   case 3:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	Lcd_Write_Data(0x48); 	
	Lcd_WR_Reg(0X2C);      //��ʼд��GRAM				
	break;
   case 4:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	Lcd_Write_Data(0xc8); 	
	Lcd_WR_Reg(0X2C);      //��ʼд��GRAM				 
	break;
   case 5:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	Lcd_Write_Data(0x28); 
	Lcd_WR_Reg(0X2C);      //��ʼд��GRAM					 
	break;
   case 6:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	Lcd_Write_Data(0x68); 	
	Lcd_WR_Reg(0X2C);      //��ʼд��GRAM				 
	break;
   case 7:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	Lcd_Write_Data(0xa8); 	
	Lcd_WR_Reg(0X2C);      //��ʼд��GRAM				 
	break;
   case 8:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	Lcd_Write_Data(0xe8); 
	Lcd_WR_Reg(0X2C);      //��ʼд��GRAM					 
	break;
 }
}




//Һ����ʼ�� ili9341
void Lcd_Init(void)
{
	LCD_RST=1;
    delay_ms(5);	
    LCD_RST=0;
    delay_ms(5) ;
    LCD_RST=1;

	LCD_CS=1;
	LCD_RD=1;
	LCD_WR=1;
	delay_ms(5);

	LCD_CS =0;  //��Ƭѡʹ��		����һ����ʼ ʼ�տ�����Ƭѡʹ��	
	
		Lcd_WR_Reg(0xCF);  
		Lcd_Write_Data(0x00); 
		Lcd_Write_Data(0xC1); 
		Lcd_Write_Data(0X30); 
		Lcd_WR_Reg(0xED);  
		Lcd_Write_Data(0x64); 
		Lcd_Write_Data(0x03); 
		Lcd_Write_Data(0X12); 
		Lcd_Write_Data(0X81); 
		Lcd_WR_Reg(0xE8);  
		Lcd_Write_Data(0x85); 
		Lcd_Write_Data(0x10); 
		Lcd_Write_Data(0x7A); 
		Lcd_WR_Reg(0xCB);  
		Lcd_Write_Data(0x39); 
		Lcd_Write_Data(0x2C); 
		Lcd_Write_Data(0x00); 
		Lcd_Write_Data(0x34); 
		Lcd_Write_Data(0x02); 
		Lcd_WR_Reg(0xF7);  
		Lcd_Write_Data(0x20); 
		Lcd_WR_Reg(0xEA);  
		Lcd_Write_Data(0x00); 
		Lcd_Write_Data(0x00); 
		Lcd_WR_Reg(0xC0);    //Power control 
		Lcd_Write_Data(0x1B);   //VRH[5:0] 
		Lcd_WR_Reg(0xC1);    //Power control 
		Lcd_Write_Data(0x01);   //SAP[2:0];BT[3:0] 
		Lcd_WR_Reg(0xC5);    //VCM control 
		Lcd_Write_Data(0x30); 	 //3F
		Lcd_Write_Data(0x30); 	 //3C
		Lcd_WR_Reg(0xC7);    //VCM control2 
		Lcd_Write_Data(0XB7); 
		Lcd_WR_Reg(0x36);    // Memory Access Control 
		Lcd_Write_Data(0x08); 
		Lcd_WR_Reg(0x3A);   
		Lcd_Write_Data(0x55); 
		Lcd_WR_Reg(0xB1);   
		Lcd_Write_Data(0x00);   
		Lcd_Write_Data(0x1A); 
		Lcd_WR_Reg(0xB6);    // Display Function Control 
		Lcd_Write_Data(0x0A); 
		Lcd_Write_Data(0xA2); 
		Lcd_WR_Reg(0xF2);    // 3Gamma Function Disable 
		Lcd_Write_Data(0x00); 
		Lcd_WR_Reg(0x26);    //Gamma curve selected 
		Lcd_Write_Data(0x01); 
		Lcd_WR_Reg(0xE0);    //Set Gamma 
		Lcd_Write_Data(0x0F); 
		Lcd_Write_Data(0x2A); 
		Lcd_Write_Data(0x28); 
		Lcd_Write_Data(0x08); 
		Lcd_Write_Data(0x0E); 
		Lcd_Write_Data(0x08); 
		Lcd_Write_Data(0x54); 
		Lcd_Write_Data(0XA9); 
		Lcd_Write_Data(0x43); 
		Lcd_Write_Data(0x0A); 
		Lcd_Write_Data(0x0F); 
		Lcd_Write_Data(0x00); 
		Lcd_Write_Data(0x00); 
		Lcd_Write_Data(0x00); 
		Lcd_Write_Data(0x00); 		 
		Lcd_WR_Reg(0XE1);    //Set Gamma 
		Lcd_Write_Data(0x00); 
		Lcd_Write_Data(0x15); 
		Lcd_Write_Data(0x17); 
		Lcd_Write_Data(0x07); 
		Lcd_Write_Data(0x11); 
		Lcd_Write_Data(0x06); 
		Lcd_Write_Data(0x2B); 
		Lcd_Write_Data(0x56); 
		Lcd_Write_Data(0x3C); 
		Lcd_Write_Data(0x05); 
		Lcd_Write_Data(0x10); 
		Lcd_Write_Data(0x0F); 
		Lcd_Write_Data(0x3F); 
		Lcd_Write_Data(0x3F); 
		Lcd_Write_Data(0x0F); 
		Lcd_WR_Reg(0x2B); 
		Lcd_Write_Data(0x00);
		Lcd_Write_Data(0x00);
		Lcd_Write_Data(0x01);
		Lcd_Write_Data(0x3f);
		Lcd_WR_Reg(0x2A); 
		Lcd_Write_Data(0x00);
		Lcd_Write_Data(0x00);
		Lcd_Write_Data(0x00);
		Lcd_Write_Data(0xef);	 
		Lcd_WR_Reg(0x11); //Exit Sleep
		delay_ms(120);
		Lcd_WR_Reg(0x29); //display on	

}	   



