//////////////////////////////////////////////////////////////////////////////////	 
//        
//******************************************************************************/
#include <rtx51tny.h>
#include "stc8.h"
#include "oled.h"
#include  "def.h"	    		  //�궨�� ���ú���
#include  "delay.h"				  //��ʱ����
#include  "ds1302.h"

//��� STC8Aϵ�� IO�ڳ�ʼ��
//��P3 P5���� ����IOĬ��׼˫��IO�� ���Ե��õ�P3 P5����Ҫ���г�ʼ��һ��   
void IO_init(void)
{
  P3M0 = 0X00;
  P3M1 = 0X00;
  P5M0 = 0X00;
  P5M1 = 0X00;
}
 
void job0() _task_ 0		//task0
{
	  IO_init();		//IO Init �ڳ�ʼ��
		OLED_Init();	// OLED Init 
		OLED_Clear(); 
		//Set_RTC();	//DS1302 Clock init   
	os_create_task(1);		//raise task1
	//Delete init task0
	//RTX51 require each task to have a 'while(1)', which task0 don;t have 
	os_delete_task(0);	
}

void job1() _task_ 1		//����1
{
	while(1)
	{
		ds1302_scan(0,0,1);		//������ʾ
	  delay_ms(200);
	}
}

