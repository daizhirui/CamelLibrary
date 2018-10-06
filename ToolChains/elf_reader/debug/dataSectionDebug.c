#include <stdio.h>

int main(void)
{
    short int shortInt = 0;
    unsigned short int uShortInt = 0;
    int aInt = 0;
    
    puts("Please input a short int: ");
    scanf("%hd",&shortInt);
    
    printf("The short int from stdin: %d\n", shortInt);
    uShortInt = *((unsigned short int*)&shortInt);
    printf("\t As unsigned short int: %d\n", uShortInt);
    aInt = shortInt;
    printf("\t As int: %d\n", aInt);
}
