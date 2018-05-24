//############################################################ 
// FILE NAME:   scan.c                                        
// AUTHOR:      Mas                                            
// PROJECT:     M2-Sejoy                                   
// DESCRIPTION: BP test program for Sejoy                                  
// COMPANY:     SHRIME
// original   - Guoyj                                       
// 2015/06/14 - Mas - Started                                
//                                                           
//###########################################################

#include "m2.h"
#include "m2_my.h"
#include "time.h"
#include "scan.h" 
#include "c_subfun.h"
//##########################################################
// FUNCTION NAME: modescan
// FUNCTION DESCRIPTION:
//   when mcu turn to sleep mode, key scan to determin
//   which work mode to turn to:
//   dbg/usr/off
//   IO_0 usr_mode    IO_1 DBG_mode
//   when the button is pressed, the voltage is low 
//##########################################################

void modescan()
{
  //print_uart("mode_in\r\n");
  int tmp;
  //detect whether sleep mode or not
  tmp = MY_SYS_CTL0_REG & 0x40;
  if(tmp)
  {
	MY_T0_CLK_REG = 1;
	mode_flag = 0;
	MemoryWrite32(0x01000588, 0x33);
	//print_uart("sleep_mode\r\n");
  }
  else
  {  
    //print_uart("normal_mode\r\n");
	mode_flag = 1;
	MemoryWrite32(0x01000588, 0x44);
    MY_T0_CLK_REG = 235;  	
  }
  MemoryWrite32(0x01000300, mode_flag);
  unsigned long tmp1;

  while(1)
  {
    //tmp1 = KEYPORT;
	//MemoryWrite32(0x01000308, tmp1);
	//tmp1 = MY_T0_CLK_REG;
	//MemoryWrite32(0x0100030c, tmp1);
    switch (KeyState)
    {	   
	   
       case 0:					// No key press
		{	
			//print_uart("case0 \r\n");
			//print_hex(mode_flag);
			MemoryWrite32(0x01000304, 0);
			Keyport_tmp = 0;
			KeyValue = 0;
			//ModeValue_temp = 1;
		    if((KEYPORT&PORTCODE)!=PORTCODE)   //KEYPORT is the io input data 
			{
				//print_uart("not all zero\r\n");
				KeyState++;
				KeyCnt = 0;
			}
			break;
			
		}
       case 1:					// Have key down state
         {
		    MemoryWrite32(0x01000304, 1);
		    //print_uart("case1\r\n");
			if((KEYPORT&PORTCODE)==PORTCODE)	// Identify twice. if so, jitter 
             {
               KeyState = 0;
               KeyCnt = 0;			   
             }
			else if(KeyCnt>=ModeDownTime)	// Key down time > 90ms
            {
               KeyState = 2;
			   Keyport_tmp = KEYPORT & 0x1f;
			   //print_hex(Keyport_tmp);
			}
           break;
		  
         }
        case 2:					// Identify mode type
	    {
		    MemoryWrite32(0x01000304, 2);
		    //print_uart("case2\r\n");
	        if((KEYPORT&PORTCODE)==PORTCODE)	// Identify short down -> state3
            {
               KeyState = 3;
               KeyCnt = 0;
            }
            else if(KeyCnt>=ModeLongDownTime)	// Identify key long down
             {
			   Keyport_tmp = KEYPORT & 0x1f;
			   //print_hex(Keyport_tmp);
               KeyState = 5;
               //KeyCnt = 0;
             }
			 //print_hex(Keyport_tmp);
            break;
			
		}
		case 3:					// Identify key up
		{
		    MemoryWrite32(0x01000304, 3);
	        //print_uart("case3\r\n");
			//print_hex(mode_flag);
			if((KEYPORT&PORTCODE)!=PORTCODE)
             {
               KeyState = 2;			// If shaking ,go back state2
             }
			else if(KeyCnt>=ModeUpTime)		// Enough up time count
			{
				KeyState = 4;
				//MemoryWrite32(0x01000334, Keyport_tmp);
				//print_hex(Keyport_tmp);
				if((Keyport_tmp&PORTCODE)==KeyMode)
				{
				    MemoryWrite32(0x01000584, 0x1234);
				    //print_uart("why?\r\n");
				    //MemoryWrite32(0x01000330, mode_flag);
					if(mode_flag == 0)
					{
					    MemoryWrite32(0x01000350, 0x55);
						ModeValue_temp = UsrMode;
						MY_SYS_CTL0_REG &= 0xbf;
					}//normal mode
					else
					{
						//RT_UART_Write('H');
						ModeValue_temp = OffMode;
					}
				}
				else if((Keyport_tmp&PORTCODE)==KeyM_Add)
					KeyValue_temp = (unsigned char) KeyM_Add;
				else if((Keyport_tmp&PORTCODE)==KeyM_Minus)
					KeyValue_temp = (unsigned char) KeyM_Minus;
				else if((Keyport_tmp&PORTCODE)==KeySet)
					KeyValue_temp = (unsigned char) KeySet;
				else if((Keyport_tmp&PORTCODE)==KeyStart)
					KeyValue_temp = (unsigned char) KeyStart;

			}
			break;	 
		}
		case 4:					// key short down finish
		{
		    //print_hex(mode_flag);
			MemoryWrite32(0x01000304, 4);
			//print_uart("case4\r\n");
			KeyState = 0;
			KeyCnt = 0;
			KeyValue=KeyValue_temp;
			ModeValue=ModeValue_temp;
			//MemoryWrite32(0x01000304, ModeValue);
			break;
		}
		case 5:					// Wait key long down up
		{
			MemoryWrite32(0x01000304, 5);
			//print_uart("case5 \r\n");
			if((KEYPORT&PORTCODE)==PORTCODE)
			{
				KeyState = 6;
				KeyCnt = 0;       //llb 
			}
			break;
		}
		case 6:					// Identify key long down up
		{
			MemoryWrite32(0x01000304, 6);
			//print_uart("case6 \r\n");
			if((KEYPORT&PORTCODE)!=PORTCODE)
			{
				KeyState = 5;
            }
			else if(KeyCnt>=ModeUpTime)
			{
				KeyState = 0;
				KeyCnt = 0;
				KeyValue_temp = 0;
				if((Keyport_tmp&PORTCODE)==KeyMode)
				{   
					ModeValue = DbgMode;
				}
			}
			break;
		}
		default:	
		{
			KeyState = 0;
			KeyCnt = 0;
			ModeValue = OffMode;
			break;
		}
	}
    //if((ModeValue==DbgMode) || (ModeValue==UsrMode)) 
    break;					// mode scan finish
  }
  //print_uart("mode_out\r\n");
}

