//////////////////////////////////////////////////////////////////////////////////	 
//        
//******************************************************************************/
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

 int main(void)
 {	
	  IO_init();		//IO口初始化
		OLED_Init();	//初始化OLED  
	 // Init_SPI(); 	 //SPI初始化
		OLED_Clear(); 
		//Set_RTC();	//DS1302时钟初始化   
	while(1) 
	{		
		ds1302_scan(0,0,1);		//更新显示
	  delay_ms(200);
		
	}	  
	
}

