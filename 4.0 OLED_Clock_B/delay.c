

#include "stc8.h"
#include "delay.h"

/*
24MHz��Ƶ�� 
��ʾ�����¿�
*/

						  //�˺���ֻ��� STC8ϵ�� ����оƬ����
void delay_us(u16 us)	  //24M�ڲ����� ʾ������ ����IO���� ������Խ�� 
{
  u16 i;
  u8 m;
  for(i=0;i<us;i++)
  for(m=0;m<2;m++); 
}

void delay_ms(u16 ms)	  //24M�ڲ����� ʾ������ ����IO���� ������Խ��
{
 u16 m;
 for(m=0;m<ms;m++)
 delay_us(1100);
}





