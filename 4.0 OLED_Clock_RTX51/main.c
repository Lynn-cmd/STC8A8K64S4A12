//////////////////////////////////////////////////////////////////////////////////	 
//        
//******************************************************************************/
#include <rtx51tny.h>
#include "stc8.h"
#include "oled.h"
#include  "def.h"	    		  //宏定义 常用函数
#include  "delay.h"				  //延时函数
#include  "ds1302.h"

//真对 STC8A系列 IO口初始化
//除P3 P5口外 其他IO默认准双向IO口 所以当用的P3 P5口是要进行初始化一下   
void IO_init(void)
{
  P3M0 = 0X00;
  P3M1 = 0X00;
  P5M0 = 0X00;
  P5M1 = 0X00;
}
 
void job0() _task_ 0		//task0
{
	  IO_init();		//IO Init 口初始化
		OLED_Init();	// OLED Init 
		OLED_Clear(); 
		//Set_RTC();	//DS1302 Clock init   
	os_create_task(1);		//raise task1
	//Delete init task0
	//RTX51 require each task to have a 'while(1)', which task0 don;t have 
	os_delete_task(0);	
}

void job1() _task_ 1		//任务1
{
	while(1)
	{
		ds1302_scan(0,0,1);		//更新显示
	  delay_ms(200);
	}
}

