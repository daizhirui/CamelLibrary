#include "CORE.h"
#include "mcu.h"

void RT_Delay_ms(unsigned long ms)
{	
	unsigned int i;
	while(ms--)
	{
		for (i = 0; i < 200; i++)
			asm("nop");
	}
}

/***********************************************************
 *函数名称：RAM清零
 *函数功能：清除RAM子程序
 *入口参数：无
 *出口参数：无
 *中间参数：无
 *说明：
 *说明：
**********************************************************/
void RT_Clr_Ram()  
{
    unsigned long i;
    for(i=0;i<2048;i++)
    {
      (*(volatile unsigned char *)(0x01000000 + i)) = 0; 
    }
}
