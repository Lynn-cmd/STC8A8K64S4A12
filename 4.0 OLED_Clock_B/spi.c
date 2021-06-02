
#include "stc8.h"
#include  "spi.h"
//SPI��ʼ��
//��Ҫ��SPI���� ��Ĭ��P1���ϵ���P4��  
//Ȼ���ʼ��SPI����
void Init_SPI()		     
{
//P4M0 &= 0xFD; 			  //���� P4.1 MISO�� ��Ϊ���빦��
//P4M1 |= 0x02;
P_SW1=0X04;				 //�� SPI ������ SS P22  MOSI P23  MISO P24  SCLK P25
SPDAT = 0;
SPSTAT=0xc0;             //SPDAT.7��SPDAT.6д11�����Խ��жϱ�־���㡣ע����д1������
SPCTL = 0xd0;            //  SSIG 1 ��������ģʽ SPEN 1 SPIʹ��  DORD 0 �ȷ����λ   MSTR 1 ����ģʽ
                         //  CPOL 0  SPICLK����ʱΪ��  CPHA  0 ������SPICLK��ǰʱ��������  ʱ��CPU_CLK/4 
}

//SPIΪȫ˫��ͨѶ  �����ڷ��͵�ͬʱ���Խ��յ�����
u8 SPI_SendByte(u8 SPI_SendData)
{
SPDAT= SPI_SendData;     // ������ д�� 
		
while((SPSTAT&0x80)==0); //�ȴ�д�����
SPSTAT = 0xc0;           //����жϱ�־����д��ͻ��־��ע���Ƕ�Ӧλд1��������	 
return  SPDAT;           //���صõ�������
}

 //SPIʱ����������
void SPI_Speed(u8 speed)
{

    switch(speed)					//ÿһ�ν��� ��Ҫ����Ϊ��� �ڽ��н���
    {
        case 0:	SPCTL&=0xFC;break;	              //SysClk/4,SPR1=0,SPR0=0 
        case 1:	SPCTL&=0xFC; SPCTL|=0x01;break;   //SysClk/16,SPR1=0,SPRO=1
        case 2:	SPCTL&=0xFC; SPCTL|=0x02;break;	  //SysClk/64,SPR1=1,SPR0=0
        case 3:	SPCTL&=0xFC; SPCTL|=0x03;break;	  //SysClk/128,SPR1=1,SPR0=1
    }
    
}




