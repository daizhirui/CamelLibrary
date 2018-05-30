#include "autoUart.h"
#include "stdio.h"

void user_interrupt(){}

void main() {
    unsigned char buffer[10];
    unsigned char bufferSize = sizeof(buffer);
    unsigned char terminal = '?';
    unsigned int timeout = 100000000;
    RT_AUTOUART_Enable(0,buffer,bufferSize,NULL,&terminal,timeout);
    while(!__autoUartDataReady){}
    puts(buffer);
}
