#include <stdio.h>
#include "user_bootloader.h"


int main(int argc, char const *argv[]) {
    #if defined(test)
    puts("test is defined.\n");
    test();
    #else
    puts("test is not defined.\n");
    test();
    #endif
    return 0;
}
