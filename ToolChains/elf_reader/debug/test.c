/*
 * File: test.c
 * Project: M2 test
 * File Created: September 7th 2018 10:16:27 am
 * Author: zhaohy
 * -----
 * Last Modified: September 7th 2018 7:28:17 pm
 * Modified By: zhaohy
 * -----
 * Copyright (c) 2017 - 2018 LKcore Co., Ltd.
 */
#include "stdio.h"
int main(void) {
    short int list[20] = {0xffec, 0xffec, 0xffff, 0xffff, -255,  255,
                          65535,  0xffec, 65516,  0x0000, 0x0000};
    printf("-20 %s %d\n", -20 == list[0] ? "equal" : "not equal", list[0]);
    printf("255 %s %d\n", 255 == list[5] ? "equal" : "not equal", list[5]);
    for (int i = 0; i < 10; i++) {
        printf("list[%d] = %d\n", i, list[i]);
    }
    printf("\nuse tmp store\n");
    for (int i = 0; i < 10; i++) {
        short int tmp = list[i];
        printf("list[%d] = %d\n", i, tmp);
    }
    return 0;
}

void user_interrupt() {}