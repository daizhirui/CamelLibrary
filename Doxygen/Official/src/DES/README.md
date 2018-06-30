# Data Encryption Standard (DES) Library for M2     {#DES}

Since M2 is a 32-bit chip, some special measurements should be used in the implementation.

## Data Structure

### 1. DES_Key

This is a data structure defined by union.
DES_Key.key is a 64-bit value.
DES_Key.apart is a 2*32-bit array.

To prepare a key for DES algorithm, declare an DES_Key at first.

```C
DES_Key originalKey;
```

Then store high 32 bits and low 32 bits respectively.

```C
originalKey.apart[1] = <#high32OfKey#>;
originalKey.apart[0] = <#low32OfKey#>;
```

### 2. MessageData

This is a data structure for storing data to encrypt or decrypt.

MessageData.data is a 64-bit value.
MessageData.apart is a 2*32-bit array.
MessageData.bytes is an 8*8-bit array.

To prepare a MessageData for DES algorithm, the operation is similar to DES_Key's.

You can load data byte by byte or uint32_t by uint32_t.

## Interface

### 1. DES_generateSubKeys

Generate 16 subKeys with a provided original key.

#### Definition

```C
DES_Key* DES_generateSubKeys(const DES_Key originalKey);
```

### 2. DES_process

Encrypt or decrypt data, require 16 subKeys provided by DES_generateSubKeys.
When mode = DES_ENCRYPT_MODE, encrypt data. When DES_DECRYPT_MODE, decrypt data.

#### Definition

```C
MessageData DES_process(MessageData originalData, DES_Key* subKeys, uint8_t mode);
```

### 3. DES

Encrypt or decrypt data, require original key.
When mode = DES_ENCRYPT_MODE, encrypt data. When DES_DECRYPT_MODE, decrypt data.

#### Definition

```C
MessageData DES(MessageData originalData, DES_Key originalKey, uint8_t mode);
```

## Example

```C
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

    // Generate 16 subKeys
    DES_Key* subKeys = DES_generateSubKeys(originalKey);
    for (uint8_t index = 0; index < 17; index++) {
        printf("K%d = 0x%x%x\n", index, subKeys[index].apart[1], subKeys[index].apart[0]);
    }

    MessageData originalData;
    originalData.data = 0x123456789abcdef;
    printf("originalData = 0x%x%x\n", originalData.apart[1], originalData.apart[0]);

    // encrypt data
    MessageData encryptedData = DES_process(originalData, subKeys, DES_ENCRYPT_MODE);
    printf("encryptedData = 0x%x%x\n", encryptedData.apart[1], encryptedData.apart[0]);

    // decrypt data
    MessageData decryptedData = DES_process(encryptedData, subKeys, DES_DECRYPT_MODE);
    printf("decryptedData = 0x%x%x\n", decryptedData.apart[1], decryptedData.apart[0]);
}
```
