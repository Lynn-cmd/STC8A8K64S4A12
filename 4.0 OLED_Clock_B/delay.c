

#include "stc8.h"
#include "delay.h"

/*
24MHz主频下 
在示波器下看
*/

						  //此函数只针对 STC8系列 其他芯片待测
void delay_us(u16 us)	  //24M内部晶振 示波器下 驱动IO动作 计算测试结果 
{
  u16 i;
  u8 m;
  for(i=0;i<us;i++)
  for(m=0;m<2;m++); 
}

void delay_ms(u16 ms)	  //24M内部晶振 示波器下 驱动IO动作 计算测试结果
{
 u16 m;
 for(m=0;m<ms;m++)
 delay_us(1100);
}





