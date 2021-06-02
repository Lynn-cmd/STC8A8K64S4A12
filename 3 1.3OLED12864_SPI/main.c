//////////////////////////////////////////////////////////////////////////////////	 
//              说明: //启光电子：启光灵创科技有限公司 电商平台 Qi-Sun
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   P2^7（SCL）
//              D1   P2^6（SDA）
//              RES  接P25
//              DC   接P24
//              CS   接P26  -----                       
//              ----------------------------------------------------------------
//******************************************************************************/
#include "stc8.h"
#include "oled.h"

 int main(void)
 {	//u16 t;
		//delay_init();	    	 //延时函数初始化	  
	//	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
		OLED_Init();			//初始化OLED  
		OLED_Clear()  	; 

	while(1) 
	{		
		OLED_Clear();
		OLED_ShowCHinese1(0,0,0);//
		OLED_ShowCHinese1(18,0,1);
		OLED_ShowCHinese1(36,0,2);
		OLED_ShowCHinese1(54,0,3);
		OLED_ShowString(71,0,","); 
		OLED_ShowCHinese1(0,2,4);
		OLED_ShowCHinese1(18,2,5);
		OLED_ShowCHinese1(36,2,6);
		OLED_ShowCHinese1(54,2,7);
		OLED_ShowCHinese1(72,2,8);
		//OLED_ShowCHinese1(0,17,4);
//		OLED_ShowCHinese1(72,0,4);
//		OLED_ShowCHinese1(90,0,5);
		
		OLED_ShowString(0,6,"Lynn 20210530");
		//OLED_ShowString(0,2,"1.3' OLED TEST");
		//OLED_ShowString(8,2,"STC8A");  
//	 	OLED_ShowString(0,4,"Qi-sun");  
//		OLED_ShowString(40,4,"123");  
//		OLED_ShowString(0,6,"STC8A,");  
//		OLED_ShowString(63,6,"CODE:");  

		while(1);
//		OLED_ShowChar(48,6,t);//显示ASCII字符	   
//		t++;
//		if(t>'~')t=' ';
//		OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
			
		
//		delay_ms(500);
//		OLED_Clear();
//		delay_ms(500);
//		OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
//		delay_ms(500);
//		OLED_DrawBMP(0,0,128,8,BMP2);
//		delay_ms(500);
	}	  
	
}

