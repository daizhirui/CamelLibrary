/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Defines
 * AUTHOR: John & Jack 
 * DATE CREATED: 2013/10/10
 * FILENAME: LCD.c
 * PROJECT: M2Library
 * COPYRIGHT: Small World, Inc.
 * DESCRIPTION:
 *    M2 Hardware Defines
 * NOTE:
 * 		This LCD library is almost copied from old version. It hasn't
 * been checked again.	-- Astro, 2017/11/3
 *-------------------------------------------------------------------*/
#include "LCD.h"
#include "mcu.h"

//########################################################//
//  Title:Sub-function for LCD app			         	  //	 
//  AUTHER:lilb                                           //
//  PROJECT:m2                                            //
//########################################################//

//********************************************************//
// The following is the LCD disp app. You can use this 	  //
// Program to show high pressure, low pressure, and heart //
// rate.You can use this progrem to show time and special //
// signs as well.										  //
//********************************************************//
void LCD_Initialize()
{
	int i;
	for(i=0;i<4;i++)		//LCD  clear lcd
	{	
	  MemoryWrite32(LCD_RAM_REG+i*4,0);
	}
	for(i=0;i<4;i++)		//��ʱ��ʾ�����ʼ��
	{
		MemoryWrite32(segment+i*4,0);
	}
	for(i=0;i<3;i++)
	{
		MemoryWrite32(digit+i, 0);
	}
	MemoryWrite32(days,0);
	MemoryWrite32(days+1,31);
	MemoryWrite32(days+2,28);
	MemoryWrite32(days+3,31);
	MemoryWrite32(days+4,30);
	MemoryWrite32(days+5,31);
	MemoryWrite32(days+6,30);
	MemoryWrite32(days+7,31);
	MemoryWrite32(days+8,31);
	MemoryWrite32(days+9,30);
	MemoryWrite32(days+10,31);
	MemoryWrite32(days+11,30);
	MemoryWrite32(days+12,31);
	MemoryWrite32(LCDCode1,0x000A28A2);
	MemoryWrite32(LCDCode1+4,0x00077567);
	MemoryWrite32(LCDCode1+8,0x000F6BF5);
	MemoryWrite32(LCDCode1+12,0x000F7E53);
	MemoryWrite32(LCDCode2,0x000FBDA3);
	MemoryWrite32(LCDCode2+4,0x000F97FA);
	MemoryWrite32(LCDCode2+8,0x000BBA9B);
	MemoryWrite32(LCDCode2+12,0x00051451);
	MemoryWrite32(LCDCode3,0x000F7DE7);
	MemoryWrite32(LCDCode3+4,0x00076177);
	MemoryWrite32(LCDCode3+8,0x000F7EF1);
	MemoryWrite32(LCDCode3+12,0x000A2A02);
	MemoryWrite32(subsecond, 0);
	MemoryWrite32(second, 0);
	MemoryWrite32(minuteg, 0);
	MemoryWrite32(hourg, 0);
	MemoryWrite32(monthg, 1);
	MemoryWrite32(dayg, 1);
    SetMode = 0;
	MemoryWrite32(flaga,1);
}
void LCD_ShowAll()
{
	int i;
	for(i=0;i<4;i++)		//LCD  display all segment
	{	
		MemoryWrite32(LCD_RAM_REG+i*4,0xffffffff);
	}
	
}
void LCD_DispOn()
{
	MemoryWrite32(LCD_CTL0_REG, 0xd9);
}
void LCD_DisHiPressure(unsigned int b) 		//display systolic pressure					 
{	
	int tmp2,tmp1,tmp;
	unsigned long segtmp;
	unsigned int i;
	unsigned long d;
				//clear the systolic pressure
	d=MemoryRead32(LCD_RAM_REG);	//changed by liliubin 
							//don't clear M2,DP1 kPa,mmHg
	d=d&0xffffffd5;			//don't clear mmHg,KPa,M-1.
	MemoryWrite32(LCD_RAM_REG,d);
	d=MemoryRead32(LCD_RAM_REG+4);
	d=d&0xffffffc0;
	MemoryWrite32(LCD_RAM_REG+4,d);	
	d=MemoryRead32(LCD_RAM_REG+8);
	d=d&0xffffffc0;
	MemoryWrite32(LCD_RAM_REG+8,d);	
	d=MemoryRead32(LCD_RAM_REG+12);
	d=d&0xffffffc0;
	MemoryWrite32(LCD_RAM_REG+12,d);
	
	if(b>999)		//out of range,LCD displays��---��
	{	d=MemoryRead32(LCD_RAM_REG+8);			
		d=d|0x0000002A;
		MemoryWrite32(LCD_RAM_REG+8,d);		
	}
	else
	{
		LCD_ExtractDigit(b);
		tmp2=MemoryRead32(digit+2);
		if(tmp2!=0)			//display the hundreds digit;if it is equal to 0,don't display.
		{	LCD_GetSegCode1(tmp2);
			for(i=0;i<4;i++)				
			{	
				segtmp=MemoryRead32(segment+i*4);
				d=MemoryRead32(LCD_RAM_REG+i*4);			
				d=d|segtmp<<4;
				MemoryWrite32(LCD_RAM_REG+i*4,d);
			}
		}
		tmp1=MemoryRead32(digit+1);
		if(tmp2!=0||tmp1!=0)		//display the tens digit;if both hundreds digit and tens digit are equal to 0,don't display
		  {	LCD_GetSegCode1(tmp1);//change from d10 to digit[1]
			for(i=0;i<4;i++)				
			{	
				segtmp=MemoryRead32(segment+i*4);
				d=MemoryRead32(LCD_RAM_REG+i*4);	
			    d=d|segtmp<<2;
				MemoryWrite32(LCD_RAM_REG+i*4,d);
			}
		}
		tmp=MemoryRead32(digit);
		LCD_GetSegCode1(tmp);
		for(i=0;i<4;i++)				//display the single digit
		{	
			segtmp=MemoryRead32(segment+i*4);
			d=MemoryRead32(LCD_RAM_REG+i*4);	
			d=d|segtmp;
			MemoryWrite32(LCD_RAM_REG+i*4,d);
		}
	}


	

}
	
void LCD_DisLoPressure(unsigned int b)	//display diastolic pressure			 
{	unsigned int i;
	unsigned long d;
	int tmp2,tmp1,tmp;
	unsigned long segtmp;
				//clear the diastolic pressure
	d=MemoryRead32(LCD_RAM_REG);		
	d=d&0xffff81ff;				
	MemoryWrite32(LCD_RAM_REG,d);
	d=MemoryRead32(LCD_RAM_REG+4);
	d=d&0xffff81ff;
	MemoryWrite32(LCD_RAM_REG+4,d);	
	d=MemoryRead32(LCD_RAM_REG+8);
	d=d&0xffff81ff;
	MemoryWrite32(LCD_RAM_REG+8,d);	
	d=MemoryRead32(LCD_RAM_REG+12);
	d=d&0xffffd5ff;			//don't clear D-1,DP2,AM.
	MemoryWrite32(LCD_RAM_REG+12,d);
	
	if(b>999)		//out of range,LCD displays��---��
	{	d=MemoryRead32(LCD_RAM_REG+4);			
		d=d|0x00002a00;
		MemoryWrite32(LCD_RAM_REG+4,d);		
	}
	else
	{	
	   
		LCD_ExtractDigit(b);
		tmp2=MemoryRead32(digit+2);
	    LCD_GetSegCode2(tmp2);
		if(tmp2!=0)			//
		{	
			for(i=0;i<4;i++)				
			{
				segtmp=MemoryRead32(segment+i*4);
				d=MemoryRead32(LCD_RAM_REG+i*4);			
				d=d|segtmp<<9;
				MemoryWrite32(LCD_RAM_REG+i*4,d);
			}
		}
		tmp1=MemoryRead32(digit+1);
		LCD_GetSegCode2(tmp1);
		if(tmp2!=0||tmp1!=0)		//
		{	
			for(i=0;i<4;i++)				
			{	
				segtmp=MemoryRead32(segment+i*4);
				d=MemoryRead32(LCD_RAM_REG+i*4);	
			    d=d|segtmp<<11;
				MemoryWrite32(LCD_RAM_REG+i*4,d);
			}
		}
		tmp=MemoryRead32(digit);
		LCD_GetSegCode2(tmp);
		for(i=0;i<4;i++)		//
		{	
			segtmp=MemoryRead32(segment+i*4);
			d=MemoryRead32(LCD_RAM_REG+i*4);	
			d=d|segtmp<<13;
			MemoryWrite32(LCD_RAM_REG+i*4,d);
		}
	}
}	

void LCD_DisHeartRate(unsigned int b)			//display heart rate
{	unsigned int i,d1,d10;
	unsigned long d;
	int segtmp;
				//clear the heart rate 
	d=MemoryRead32(LCD_RAM_REG);		
	d=d&0xfc3fffff;				
	MemoryWrite32(LCD_RAM_REG,d);
	d=MemoryRead32(LCD_RAM_REG+4);
	d=d&0xfc3fffff;
	MemoryWrite32(LCD_RAM_REG+4,d);	
	d=MemoryRead32(LCD_RAM_REG+8);
	d=d&0xfc3fffff;
	MemoryWrite32(LCD_RAM_REG+8,d);	
	d=MemoryRead32(LCD_RAM_REG+12);
	d=d&0xfd9fffff;			//don't clear No.
	MemoryWrite32(LCD_RAM_REG+12,d);	
	
	if(b>99)				//if the heart rate is a three-figure number,display"HR"
	{	
		LCD_DisSign(HR);	
	}
	d10=b/10%10;
	d1=b%10;
	LCD_GetSegCode3(d10);
	for(i=0;i<4;i++)			//
	{	
		segtmp=MemoryRead32(segment+i*4);
		d=MemoryRead32(LCD_RAM_REG+i*4);	
		d=d|segtmp<<24;
		MemoryWrite32(LCD_RAM_REG+i*4,d);
	}	
	LCD_GetSegCode3(d1);
	for(i=0;i<4;i++)			//
	{	
		segtmp=MemoryRead32(segment+i*4);
		d=MemoryRead32(LCD_RAM_REG+i*4);	
		d=d|segtmp<<22;
		MemoryWrite32(LCD_RAM_REG+i*4,d);
	}	
}

void LCD_DisTime(unsigned int hour,unsigned int minute)	//display time
{	unsigned int i;
	unsigned long d;
	int segtmp;
	d=MemoryRead32(LCD_RAM_REG);		
	d=d&0xffc07fff;				   	//clear 9AGDE 
	MemoryWrite32(LCD_RAM_REG,d);
	d=MemoryRead32(LCD_RAM_REG+4);
	d=d&0xffc07fff;					//B9
	MemoryWrite32(LCD_RAM_REG+4,d);
	d=MemoryRead32(LCD_RAM_REG+8);
	d=d&0xffc07fff;					//C9
	MemoryWrite32(LCD_RAM_REG+8,d);
	d=MemoryRead32(LCD_RAM_REG+12);
	d=d&0xffeaffff;			//clear 'H1',don't clear 'PM',':' //don't clear ":","HT","PM"
	MemoryWrite32(LCD_RAM_REG+12,d);


	//LCD_DisSign(colon);			//display������
	if(hour>12)				//display in duodecimal system
	{	hour=hour%12;
		LCD_DisSign(PM);		//pm=1
		LCD_ClearSign(AM);
	}
	else
	{	LCD_DisSign(AM);		//am=1;
		LCD_ClearSign(PM);
	}		

	if(hour>9)
	{	
		//LCD_DisSign(H1);		//
		LCD_DisSign(B9);
		LCD_DisSign(C9);
	}
	LCD_GetSegCode2(hour%10);
	
	for(i=0;i<4;i++)		//
	{	
		segtmp=MemoryRead32(segment+i*4);
		d=MemoryRead32(LCD_RAM_REG+i*4);	
		//d=d|segtmp<<22;
		d=d|(segtmp<<16);
		MemoryWrite32(LCD_RAM_REG+i*4,d); 
	}				
					//display minute			
	LCD_GetSegCode2(minute/10);
	for(i=0;i<4;i++)
	{	
		segtmp=MemoryRead32(segment+i*4);
		d=MemoryRead32(LCD_RAM_REG+i*4);	
		//d=d|segtmp<<24;
		d=d|(segtmp<<18);
		MemoryWrite32(LCD_RAM_REG+i*4,d); 
	}
	LCD_GetSegCode2(minute%10);
	for(i=0;i<4;i++)
	{	
		segtmp=MemoryRead32(segment+i*4);
		d=MemoryRead32(LCD_RAM_REG+i*4);	
		//d=d|segtmp<<26;
		d=d|(segtmp<<20);
		MemoryWrite32(LCD_RAM_REG+i*4,d); 
	}
}


void LCD_DisDate(unsigned int month,unsigned int day)		//display day
{	unsigned int i;
	unsigned long d;
	int segtmp;
	
	d=MemoryRead32(LCD_RAM_REG);		
	d=d&0x03ffffff;			//don't clear 'D-2'
	MemoryWrite32(LCD_RAM_REG,d);
	d=MemoryRead32(LCD_RAM_REG+4);
	d=d&0x03ffffff;
	MemoryWrite32(LCD_RAM_REG+4,d);
	d=MemoryRead32(LCD_RAM_REG+8);
	d=d&0x03ffffff;
	MemoryWrite32(LCD_RAM_REG+8,d);
	d=MemoryRead32(LCD_RAM_REG+12);
	d=d&0x13ffbbff;			//clear 'M1',don't clear 'M-2' //clear 13AGD E13 don't clear M-2
	MemoryWrite32(LCD_RAM_REG+12,d);
	LCD_DisSign(M_2);
	//LCD_DisSign(D_2);
	
	if(month>9)
	{	
		LCD_DisSign(B13);
		LCD_DisSign(C13);
		//LCD_DisSign(M1);		//M1=1;
	}
	LCD_GetSegCode3(month%10);
	for(i=0;i<4;i++)
	{	
		segtmp=MemoryRead32(segment+i*4);
		d=MemoryRead32(LCD_RAM_REG+i*4);	
		//d=d|segtmp<<20;
		d=d|segtmp<<30;
		MemoryWrite32(LCD_RAM_REG+i*4,d); 
	}
	LCD_GetSegCode3(day/10);
	for(i=0;i<4;i++)
	{	
		segtmp=MemoryRead32(segment+i*4);
		d=MemoryRead32(LCD_RAM_REG+i*4);	
		//d=d|segtmp<<18;
		d=d|segtmp<<28;
		MemoryWrite32(LCD_RAM_REG+i*4,d); 
	}
	LCD_GetSegCode1(day%10);
	for(i=0;i<4;i++)
	{	
		segtmp=MemoryRead32(segment+i*4);
		d=MemoryRead32(LCD_RAM_REG+i*4);	
		//d=d|segtmp<<16;
		d=d|segtmp<<26;
		MemoryWrite32(LCD_RAM_REG+i*4,d); 
	}
}

void LCD_DisSign(unsigned int x,unsigned int y)		//display special sign
{	
	unsigned long c=0x00000001,d;
	d=MemoryRead32(LCD_RAM_REG+x);
	d=d|c<<y;
	MemoryWrite32(LCD_RAM_REG+x,d);
}

void LCD_ClearSign(unsigned int x,unsigned int y)		//clear special sign
{	unsigned long c=0x00000001,d;
	d=MemoryRead32(LCD_RAM_REG+x);
	d=d&~(c<<y);
	MemoryWrite32(LCD_RAM_REG+x,d);
}

void LCD_GetSegCode1(unsigned int b)		//get the display segment code,red part of the truth table 
{	unsigned int i;
	unsigned long d;
	unsigned long tmp;
	unsigned long segtmp;
	for(i=0;i<4;i++)
	{	
		tmp=MemoryRead32(LCDCode1+i*4);
		d=tmp>>(b*2);
		segtmp=d&0x00000003;
		MemoryWrite32(segment+i*4,segtmp);
	}
}

void LCD_GetSegCode2(unsigned int b)		//get the display segment code,red part of the truth table
{	unsigned int i;
	unsigned long d;
	unsigned long tmp;
	unsigned long segtmp;
	for(i=0;i<4;i++)
	{	
		tmp=MemoryRead32(LCDCode2+i*4);
		d=tmp>>(b*2);
		segtmp=d&0x00000003;
		MemoryWrite32(segment+i*4,segtmp);
		//segment[i]=d&0x00000003;
	}
}

void LCD_GetSegCode3(unsigned int b)		//get the display segment code,green part 
{	unsigned int i;
	unsigned long d;
	unsigned long tmp;
	unsigned long segtmp;
	for(i=0;i<4;i++)
	{	
		tmp=MemoryRead32(LCDCode3+i*4);
		d=tmp>>(b*2);
		//d=LCDCode3[i]>>(b*2);
		segtmp=d&0x00000003;
		MemoryWrite32(segment+i*4, segtmp);
		//segment[i]=d&0x00000003;
	}
}

void LCD_ExtractDigit(unsigned int b)
{	
	int tmp,tmp1,tmp2;
	tmp=b%10;	//store single digit
	MemoryWrite32(digit,tmp);
	b=b/10;
	tmp1=b%10;	//store tens digit
	MemoryWrite32(digit+1,tmp1);
	tmp2=b/10;	//store hundreds digit
	MemoryWrite32(digit+2,tmp2);
}

void LCD_BlinkSign(unsigned int x,unsigned int y)		//blink special sign
{	unsigned long c=0x00000001,d;
	int a;
	a=MemoryRead32(flaga);
	if(a==1)
	{
		d=MemoryRead32(LCD_RAM_REG+x);
		d=d^(c<<y);	//XOR
		MemoryWrite32(LCD_RAM_REG+x,d);
	}
	else
	{
		LCD_DisSign(x,y);
	}
}

void LCD_BlinkMinute()
{	unsigned long d;
	unsigned int a;
	a=MemoryRead32(flaga);
	if(a==1)
	{	
		d=MemoryRead32(LCD_RAM_REG);		
		//d=d&0xf0ffffff;				
		d=d&0xffc3ffff;
		MemoryWrite32(LCD_RAM_REG,d);
		d=MemoryRead32(LCD_RAM_REG+4);
		d=d&0xffc3ffff;
		MemoryWrite32(LCD_RAM_REG+4,d);
		d=MemoryRead32(LCD_RAM_REG+8);
		d=d&0xffc3ffff;
		MemoryWrite32(LCD_RAM_REG+8,d);
		d=MemoryRead32(LCD_RAM_REG+12);
		d=d&0xffebffff;			//don't clear 'PM',':' 
		MemoryWrite32(LCD_RAM_REG+12,d);
	}
	if(a==0)
	{	
		LCD_DisTime(hourg,minuteg);	
	}
}

void LCD_BlinkHour()
{	unsigned long d;
	unsigned int a;
	a=MemoryRead32(flaga);
	if(a==1)
	{	d=MemoryRead32(LCD_RAM_REG);		
		d=d&0xfffc7fff;				
		MemoryWrite32(LCD_RAM_REG,d);
		d=MemoryRead32(LCD_RAM_REG+4);
		d=d&0xfffc7fff;
		MemoryWrite32(LCD_RAM_REG+4,d);
		d=MemoryRead32(LCD_RAM_REG+8);
		d=d&0xfffc7fff;
		MemoryWrite32(LCD_RAM_REG+8,d);
		d=MemoryRead32(LCD_RAM_REG+12);
		d=d&0xfffeffff;			//clear 'H1'
		MemoryWrite32(LCD_RAM_REG+12,d);
	}
	if(a==0)
	{	
		LCD_DisTime(hourg,minuteg);
	}
}

void LCD_BlinkDay()
{	unsigned long d;
	unsigned int a;
	a=MemoryRead32(flaga);
	if(a==1)
	{	d=MemoryRead32(LCD_RAM_REG);		
		d=d&0xC7ffffff;			//don't clear 'D-2'
		MemoryWrite32(LCD_RAM_REG,d);
		d=MemoryRead32(LCD_RAM_REG+4);
		d=d&0xC3ffffff;
		MemoryWrite32(LCD_RAM_REG+4,d);
		d=MemoryRead32(LCD_RAM_REG+8);
		d=d&0xC3ffffff;
		MemoryWrite32(LCD_RAM_REG+8,d);
		d=MemoryRead32(LCD_RAM_REG+12);
		d=d&0xd3ffffff;			//don't clear 'M-2' 
		MemoryWrite32(LCD_RAM_REG+12,d);

	}
	if(a==0)
	{	
		LCD_DisDate(monthg,dayg);
	}
}

void LCD_BlinkMonth()
{	unsigned long d;
	unsigned int a;
	a=MemoryRead32(flaga);
	a = a&0x1;
	if(a==1)
	{	
	    //print_uart("\r\n a=1\r\n");
		d=MemoryRead32(LCD_RAM_REG);		
		d=d&0x3bffffff;			//
		MemoryWrite32(LCD_RAM_REG,d);
		d=MemoryRead32(LCD_RAM_REG+4);
		d=d&0x3fffffff;
		MemoryWrite32(LCD_RAM_REG+4,d);
		d=MemoryRead32(LCD_RAM_REG+8);
		d=d&0x3fffffff;
		MemoryWrite32(LCD_RAM_REG+8,d);
		d=MemoryRead32(LCD_RAM_REG+12);
		d=d&0x3fffbbff;			//clear 'M1'
		MemoryWrite32(LCD_RAM_REG+12,d);
	}
	if(a==0)
	{	
	    //print_uart("\r\n a=0\r\n");
		LCD_DisDate(monthg, dayg);	
	}
}
