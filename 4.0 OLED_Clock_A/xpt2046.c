
 
#include "stc8.h"
#include "math.h"
#include "xpt2046.h"
#include "delay.h"
#include "spi.h"
#include "gui.h"
#include "tft.h"


u8 i2t[8];			   //��24c02�� ����У׼���� ��ʱת����������


//������У׼����
//���û��У׼��24C��  ʹ��Ĭ��ֵ
struct T_i T_i2c=
{
 678,	 //�������� ��ֵҪ����10000������ʵֵ  ��ΪΪ�˷��㺯������ ����ʱ����10000 		 
 920,	 //�������� ��ֵҪ����10000������ʵֵ  ��ΪΪ�˷��㺯������ ����ʱ����10000 
 -19,
 -20,
};





//SPI���߷� ��ȡXPT2046����
//�ɼ�����ʱxpt������������� x y  
//�˺���û��ת����LCD��ʵ������ 
//ΪУ׼��������ȡ
//���� xpt2046ad.x  ����x����
//     xpt2046ad.y  ����y����
//     xpt2046ad.flag �ɼ��ɹ���־
struct TFT_Pointer xpt2046ad()		                                 
{
 struct TFT_Pointer result;
 u8   ax[8];
 u16 x1,y1;
 u16 x2,y2;

 result.x=0;
 result.y=0;
 result.flag=0;
 
#define ERR_RANGE 5 //��Χ 
  
 if(AD7843_isClick==0)
 {	 
  delay_ms(1);
  if(AD7843_isClick==0)
  {
	LCD_CS=1;			//xpt��Ƭѡ����tft�� ��ֹ��������ʱӰ��tft	����ص�TFTʹ��
    AD7843_CS=0; 		//��Ƭѡ
	SPI_Speed(2);		//���� SPIͨѶ�ٶ� ʹ����оƬ�Ż����ݸ��ȶ�
   
   /*�������16ʱ�����ڲɼ�  ��Ϊ �˴������ܲ��õ���SPI����
     ��SPI������ֻ��8λ����  XPT2046��AD�ֱ���Ϊ12λ  
	 ����8λ��SPI�����ǲ��е�
	 ���� ����XPT2046�ֲ��� 16ʱ������ ʱ��ͼ ���Կ���
	 ���Ͳɼ�����  ����һ��SPI���ݺ� �ڷ��Ϳչ��ܵ�SPI����  �ͻ��ʣ�µĲ��ֽ��յ�
	 �����Ƚ��յ� �ǵ��ֽ�����  �ڶ��ν��յ��Ǹ��ֽ�����  ��λ�� ����12λ��ADֵ   
   */
   ax[0]=SPI_SendByte(0x90);  //�Ϳ�����10010000���ò�ַ�ʽ��X���꣬������ȡ������
   ax[0]=SPI_SendByte(0x00);  //�����������ݣ����λ����Ϊ1����2046�����ͻ��������X���ֽ�
   ax[1]=SPI_SendByte(0xD0);  //�Ϳ�����11010000���ò�ַ�ʽ��Y���꣬����X���ֽ�
   ax[2]=SPI_SendByte(0x00);  //�����������ݣ�ͬ�ϣ�������Y���ֽ�
   ax[3]=SPI_SendByte(0x90);  //�Ϳ�����10010000 ���ڶ��Σ���X���꣬����Y���ֽ�
   ax[4]=SPI_SendByte(0x00);  //�����������ݣ�ͬ�ϣ�������X���ֽ�
   ax[5]=SPI_SendByte(0xD0);  //�Ϳ�����11010000  ���ڶ��Σ���Y���꣬����X���ֽ�
   ax[6]=SPI_SendByte(0x00);  //�����������ݣ�ͬ��)������Y���ֽ�
   ax[7]=SPI_SendByte(0x90);  //�Ϳ�����10010000  �������Σ���X���꣬����Y���ֽ�

								//��ȡ���βɼ�ֵ
   y1=(ax[0]<<5)|(ax[1]>>3);
   y2=(ax[4]<<5)|(ax[5]>>3);
   x1=(ax[2]<<5)|(ax[3]>>3);
   x2=(ax[6]<<5)|(ax[7]>>3);

if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//ǰ�����β�����+-ERR_RANGE��
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
   {
   	result.flag=1;			//�򿪱�־λ
	result.x=(x1+x2)/2;
	result.y=(y1+y2)/2;
   }
   else result.flag=0;

   SPI_Speed(0);		//����SPI�ٶ�Ϊ���
   AD7843_CS=1; 		//��Ƭѡ
   LCD_CS=0;
   
  }
 } 

 return result;
}




//��������ת����ʵ�����꺯����
//���� result.x���� result.y���� 
struct TFT_Pointer TFT_Cm()		                                  
{
 u16 a,b;				//��ʱ����
 struct TFT_Pointer result;

 result=xpt2046ad();	 //��ȡADֵ

//������X Y
   a=result.x;
   b=result.y;
/* ���������㹫ʽ
   lcdx=xa*tpx+xb;
   lcdy=ya*tpy+yb;
   lcdx,lcdyΪ������  tpx,tpyΪ������ֵ xa,yaΪ��������  xb,ybΪƫ����

   ���㷽�� 
   ����Ļ��ָ��lcdx,lcdyλ�û���ʮ��ͼ�� �ֱ�����Ļ�ϵ�4����λ��
   �ô����ʷֱ��� �õ����еĴ���ֵ
   ��������Ĺ�ʽ ����	xa,ya  xb,yb  ��������ʹ�ô��������ĻУ׼
  */
		 //��У׼����  
//		 result.x=0.065894*a-16;			//���õ���ADֵ���빫ʽ ����lcd����x y���� 
//		 result.y=0.084031*b-14;
		//��У׼����  
		 result.x=((float)T_i2c.xi/10000)*a+T_i2c.a;			//���õ���ADֵ���빫ʽ ����lcd����x y���� 
		 result.y=((float)T_i2c.yi/10000)*b+T_i2c.b;
 return result;								//��������ֵ
}













