
#include "UART0_CPP.h"
extern "C" {
    void user_interrupt(){}
}
// unsigned char __used;
int main()
{
    Serial uart0 = Serial(0);
    while(1){
        uart0.write((unsigned char*)"Hello!");
    }
    return 0;
}
