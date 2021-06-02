
#include  "stc8.h"
#include  "gui.h"
#include  "tft.h"
#include  "delay.h" 
#include  "zifu8x16.h"			
#include  "hz16x16.h"		  //汉字16X16
#include "oled.h"
////显示汉字及字符  横向显示
////x1 y1 显示的初始位置
////*str 要显示的数据
////dcolor 显示汉字 字符的颜色
////bgcolor 显示汉字 字符的背景颜色  不支持背景屏幕自有色
void GUI_sprintf_hzstr16h(u8 x1,u16 y1,u8 *str,u16 dcolor,u16 bgcolor)	  
{  
	 u8 l=0;
	while(*str)
	{	
	  if(*str<0x80)		  //小于128   ascii 都在数组内
	  {	  
		GUI_sprintf_char(x1,y1+l*8,*str,dcolor,bgcolor,1);
		l+=1;
		str++;
		}
	  else
	  {	  
	   //GUI_sprintf_hz1616(x1,y1+l*8,(u8*)str,dcolor, bgcolor,1);
			str+=2;l+=2;
	  }
	}	
}


//显示汉字字符串 纵向显示
//x1 y1 显示的初始位置
//*str 要显示的数据
//dcolor 显示字符的颜色
//bgcolor 显示字符的背景颜色  
void GUI_sprintf_hzstr16x(u8 x1,u16 y1,u8 *str,u16 dcolor,u16 bgcolor)	  
{  
	 u8 l=0;
	while(*str)
	{	
	  if(*str<0x80)		  //小于128   ascii 都在数组内
	  {	  
		GUI_sprintf_char(x1+l*8,y1,*str,dcolor,bgcolor,0);
		l+=1;
		str++;
		}
	  else
	  {	  
	   //GUI_sprintf_hz1616(x1+l*8,y1,(u8*)str,dcolor, bgcolor,0);
			str+=2;l+=2;
	  }
	}	
}


//显示英文或数字字符
//函数支持 字符的纵向和横向显示 （要配合扫描方式）
//x  y  要显示字符的初始坐标
//value 显示字符数据
//dcolor 显示的字符颜色  bgcolor显示字符的背景颜色
//mode   0 字符纵向显示  1 字符横向显示
void GUI_sprintf_char(u8 x,u16 y,u8 value,u16 dcolor,u16 bgcolor,u8 mode)	
{  
	u8 i,j;
	u8 *temp=zifu816;    //temp是*temp的地址  这里temp就是zifu的首地址 
 	                    
	temp+=(value-32)*16;   //确定要显示的值
				           //用ascii表  前32个ascii没有存入zifu库里 所以要减32
	                       //每个字符用16个字节显示 所以在乘以16  就是对应的显示位的首地址

	  if(mode==0)Address_set(x,y,x+7,y+15);    //设置区域		   
	  if(mode==1)Address_set(x,y,x+7,y+15); //设置区域   		    
		for(j=0;j<16;j++)
		{
			for(i=0;i<8;i++)		    //先横扫
			{ 		     
			 	if((*temp&(1<<(7-i)))!=0)		   //将1 左移 然后对应位进行相与 				
				  Lcd_Write_Data(dcolor);		   //显示字符颜色
				 
				else				
				  Lcd_Write_Data(bgcolor);		   //显示背景颜色		
			}
			temp++;								   //下一字节
		 }


}

////只显示10位数据
//void number10(u8 x,u16 y,u16 dat)	//坐标 要显示的数据	 
//{	
//	OLED_ShowChar(x,y,dat/10%10+'0');
//	OLED_ShowChar(x+8,y,dat%10+'0');
//}

	
