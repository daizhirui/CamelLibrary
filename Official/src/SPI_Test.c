/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Library Test
 * AUTHOR: Astro
 * DATE CREATED: 2017/10/31
 * FILENAME: SPI_Test.c
 * PROJECT: M2Library Test
 * COPYRIGHT: Camel Microelectronics, Ltd.
 * DESCRIPTION:
 *--------------------------------------------------------------------*/
#include "SPI.h"
#include "str.h"
void user_interrupt(){}
void master(){
    char c;
    spi_Modeset(Master);
    spi_ChipSelect();
    spi_ClearState();
    while(1){
        c=spi_MasterTransfer('A');
        putchar(c);
    }
}
void slave(){
    char c;
    spi_Modeset(Slave);
    spi_ClearState();
    spi_Write_('B');
    while(1){
        c=spi_SlaveTransfer('B');
        putchar(c);
    }
}
void main(){
    puts("1=Master,0=Slave\n");
    switch(getch()){
        case '0':slave();break;
        case '1':master();
    }
}
