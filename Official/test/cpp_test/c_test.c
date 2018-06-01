#include "UART0.h"
#include "stdio.h"
#include "string.h"
void user_interrupt(){}

void __putchar(unsigned char c)
{
    while (RT_UART0_Busy())
        ;
    RT_UART0_Write(c);
}

void __puts(char *string)
{
    while (*string)
    {
        if (*string == '\n') __putchar('\r');
        __putchar(*string++);
    }
}
int i[10];
int main()
{
    //memset(i,100,0);
    while(1){
        __puts("Hello!");
        //printf("%d\n", i[0]);
        i[0]++;
    }
    return 0;
}
