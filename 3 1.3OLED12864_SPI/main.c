//////////////////////////////////////////////////////////////////////////////////	 
//              ˵��: //������ӣ������鴴�Ƽ����޹�˾ ����ƽ̨ Qi-Sun
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   P2^7��SCL��
//              D1   P2^6��SDA��
//              RES  ��P25
//              DC   ��P24
//              CS   ��P26  -----                       
//              ----------------------------------------------------------------
//******************************************************************************/
#include "stc8.h"
#include "oled.h"

 int main(void)
 {	//u16 t;
		//delay_init();	    	 //��ʱ������ʼ��	  
	//	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
		OLED_Init();			//��ʼ��OLED  
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
//		OLED_ShowChar(48,6,t);//��ʾASCII�ַ�	   
//		t++;
//		if(t>'~')t=' ';
//		OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ 	
			
		
//		delay_ms(500);
//		OLED_Clear();
//		delay_ms(500);
//		OLED_DrawBMP(0,0,128,8,BMP1);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
//		delay_ms(500);
//		OLED_DrawBMP(0,0,128,8,BMP2);
//		delay_ms(500);
	}	  
	
}

