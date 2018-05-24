#include "UART1.h"
#include "mcu.h"

//########################################################//
//  Title:Sub-function for UART1 app	              		  //	 
//  AUTHER:lilb                                           //
//  PROJECT:m2                                            //
//########################################################//

void RT_UART1_WriteChar(unsigned char value)
{	
	unsigned int uport;
	do {
		  uport=*(volatile unsigned*) uart1_bport;
	} while (uport & WRITE_BUSY);
	
	
	*(volatile unsigned char*)uart1_wport = value;
}

void RT_UART1_WriteShort(unsigned short value)
{	
	unsigned int uport;
	do {
		  uport=*(volatile unsigned*) uart1_bport;
	} while (uport & WRITE_BUSY);
	
	
	*(volatile unsigned short*)uart1_wport = value;
}

void RT_UART1_WriteLong(unsigned long value)
{	
	unsigned int uport;
	do {
		  uport=*(volatile unsigned*) uart1_bport;
	} while (uport & WRITE_BUSY);
	
	
	*(volatile unsigned long*)uart1_wport = value;
}

void RT_UART_WriteLongLong(long long value)
{	
	unsigned int uport;
	do {
		  uport=*(volatile unsigned*) uart1_bport;
	} while (uport & WRITE_BUSY);
	
	
	*(volatile unsigned long*)uart1_wport = value>>32;
	*(volatile unsigned long*)uart1_wport = value;

}

void RT_UART1_WriteString(unsigned char * string)
{
	unsigned int uport;
	while(*string) {
		do {
		  	uport=*(volatile unsigned*) uart1_bport;
		} while (uport & WRITE_BUSY);
		*(volatile unsigned char*)uart1_wport = *string++;
	}
}

void RT_UART1_WriteLongArray(unsigned long * data, unsigned long num)
{
	unsigned long i;
	unsigned int uport;
	for (i = 0; i < num; i++) {
		do {
		  	uport=*(volatile unsigned*) uart1_bport;
		} while (uport & WRITE_BUSY);
		*(volatile unsigned long*)uart1_wport = data[i];
	}
}

unsigned char RT_UART1_WaitRead()
{
	unsigned int uport;
	do {
		  uport=*(volatile unsigned*) uart1_rdy_port;
	} while (uport & READ_RDY);
	uport = *(volatile unsigned*)uart1_rport;//
	return uport;
}