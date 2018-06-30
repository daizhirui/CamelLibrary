/***************************************************
Project: DES_test
File Name: DES_test.c
Author: daizhirui
Date: Friday, June 15, 2018 at 12:27:27 PM Central European Summer Time
Copyright © 2018 daizhirui. All rights reserved.
****************************************************/

// Add your header files here
#include "mcu.h"
#include "DES.h"
#include "stdio.h"
// This is the interrupt function for user
void user_interrupt() {

}

// This is the main function
int main() {
	DES_Key originalKey;
    originalKey.key = 0x133457799BBCDFF1;

    DES_Key* subKeys = DES_generateSubKeys(originalKey);
    for (uint8_t index = 0; index < 17; index++) {
        printf("K%d = 0x%x%x\n", index, subKeys[index].apart[1], subKeys[index].apart[0]);
    }
    unsigned int a = 1;
    unsigned int b = a? 0x1f800000 : 0x1f800801;
    MessageData originalData;
    originalData.data = 0x123456789abcdef;
    printf("originalData = 0x%x%x\n", originalData.apart[1], originalData.apart[0]);
    MessageData encryptedData = DES_process(originalData, subKeys, DES_ENCRYPT_MODE);
    printf("encryptedData = 0x%x%x\n", encryptedData.apart[1], encryptedData.apart[0]);
    MessageData decryptedData = DES_process(encryptedData, subKeys, DES_DECRYPT_MODE);
    printf("decryptedData = 0x%x%x\n", decryptedData.apart[1], decryptedData.apart[0]);
}
