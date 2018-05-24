/***********************************************************
 * 文件名:rtc.c
 * 作者: 郭永军 
 * 创建时间:  2014.12.11
 * 所属项目: m2
 * 公司: 杭州世佳电子
 * 邮箱：guoyj_sejoy@163.com
 * 代码编写工具：UltraEdit
 * 模块功能：M2 RTC相关硬件设置和上电初始化
 * 修改记录: 格式（修改日期、修改人、修改内容）
 *
 *
 *
 *
 *
 ***********************************************************/

/*Follow Is Include Files*/
#include "RTC.h"
#include "mcu.h"

/***********************************************************
 *函数名称：RT_RTC_Init12 RT_RTC_Init24
 *函数功能：RTC时钟初始化
 *入口参数：无
 *出口参数：无
 *中间参数：无
 *说明：RTC使能的同时晶振也打开，这个不确定到时候要问一下
 *说明：
**********************************************************/


void RT_RTC_Read(unsigned char *d_year,unsigned char *d_mon,unsigned char *d_day,unsigned char *d_hour,unsigned char *d_min,unsigned char *d_sec)
{
	unsigned long time;
	time = MemoryRead32(RTC_TIME_REG);
	if (d_year != 0)
		*d_year =(unsigned char)((time>>26)&0x3f);     //读取年 
	if (d_mon != 0)
      	*d_mon = (unsigned char)((time>>22)&0x0f);   //读取月 
	if (d_day != 0)                   
      	*d_day = (unsigned char)((time>>17)&0x1f);     //读取日
	if (d_hour != 0)                                 
      	*d_hour = (unsigned char)((time>>12)&0x1f);    //读取时 
	if (d_min != 0)                                
      	*d_min = (unsigned char)((time>>6)&0x3f);   //读取分   
	if (d_sec != 0)                              	
		*d_sec = (unsigned char)(time&0x3f);
}

