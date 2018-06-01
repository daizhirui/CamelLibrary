#include "UART0_CPP.h"
#include "mcu.h"
Serial::Serial(unsigned char port)
{
    this->mask = (port%2) << 11;
}

unsigned char Serial::baudrate(unsigned int rate)
{
    switch (rate) {
        case 9600:
            MemoryWrite32(0x1f800702,0x0);
            break;
        case 19200:
            MemoryWrite32(0x1f800702,0x1000);
            break;
        case 38400:
            MemoryWrite32(0x1f800702,0x2000);
            break;
        default:
            return 0;
    }
    return 1;
}
unsigned char Serial::read()
{
    while(!MemoryRead32(UART0_DATA_RDY_REG|mask)){}
    return MemoryRead32(UART0_READ_REG|mask);
}
void Serial::write(unsigned char c)
{
    while(MemoryRead32(UART0_BUSY_REG|mask)){}
    MemoryWrite32(UART0_WRITE_REG|mask,c);
}
void Serial::write(unsigned char* str)
{
    while(*str){
        this->write(*str++);
    } // End of while
}
