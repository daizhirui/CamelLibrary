#include "UART.h"
#include "mcu.h"

//########################################################//
//  Title:Sub-function for UART app	              		  //	 
//  AUTHER:lilb                                           //
//  PROJECT:m2                                            //
//########################################################//

void RT_UART_WriteChar(unsigned char value)
{	
	unsigned int uport;
	do {
		  uport=*(volatile unsigned*) uart_bport;
	} while (uport & WRITE_BUSY);
	
	
	*(volatile unsigned char*)uart_wport = value;
}

void RT_UART_WriteShort(unsigned short value)
{	
	unsigned int uport;
	do {
		  uport=*(volatile unsigned*) uart_bport;
	} while (uport & WRITE_BUSY);
	
	
	*(volatile unsigned short*)uart_wport = value;
}

void RT_UART_WriteLong(unsigned long value)
{	
	unsigned int uport;
	do {
		  uport=*(volatile unsigned*) uart_bport;
	} while (uport & WRITE_BUSY);
	
	
	*(volatile unsigned long*)uart_wport = value;
}

void RT_UART_WriteLongLong(long long value)
{	
	unsigned int uport;
	do {
		  uport=*(volatile unsigned*) uart_bport;
	} while (uport & WRITE_BUSY);
	
	
	*(volatile unsigned long*)uart_wport = value>>32;
	*(volatile unsigned long*)uart_wport = value;

}

void RT_UART_WriteString(unsigned char * string)
{
	unsigned int uport;
	while(*string) {
		do {
		  	uport=*(volatile unsigned*) uart_bport;
		} while (uport & WRITE_BUSY);
		*(volatile unsigned char*)uart_wport = *string++;
	}
}

void RT_UART_WriteLongArray(unsigned long * data, unsigned long num)
{
	unsigned long i;
	unsigned int uport;
	for (i = 0; i < num; i++) {
		do {
		  	uport=*(volatile unsigned*) uart_bport;
		} while (uport & WRITE_BUSY);
		*(volatile unsigned long*)uart_wport = data[i];
	}
}

unsigned char RT_UART_WaitRead()
{
	unsigned int uport;
	do {
		  uport=*(volatile unsigned*) uart_rdy_port;
	} while (uport & READ_RDY);
	uport = *(volatile unsigned*)uart_rport;//
	return uport;
}