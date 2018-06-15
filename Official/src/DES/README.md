# Data Encryption Standard (DES) Library for M2

Since M2 is a 32-bit chip, some special measurements should be used in the implementation.

## Data Structure

### DES_Key

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

### MessageData

This is a data structure for storing data to encrypt or decrypt.

MessageData.data is a 64-bit value.
MessageData.apart is a 2*32-bit array.
MessageData.bytes is an 8*8-bit array.

To prepare a MessageData for DES algorithm, the operation is similar to DES_Key's.

You can load data byte by byte or uint32_t by uint32_t.

## Interface

### DES_generateSubKeys

Generate 16 subKeys with a provided original key.

#### Definition

```C
DES_Key* DES_generateSubKeys(const DES_Key originalKey);
```

### DES_process

Encrypt or decrypt data, require 16 subKeys provided by DES_generateSubKeys.
When mode = DES_ENCRYPT_MODE, encrypt data. When DES_DECRYPT_MODE, decrypt data.

#### Definition

```C
MessageData DES_process(MessageData originalData, DES_Key* subKeys, uint8_t mode);
```

### DES

Encrypt or decrypt data, require original key.
When mode = DES_ENCRYPT_MODE, encrypt data. When DES_DECRYPT_MODE, decrypt data.

#### Definition

```C
MessageData DES(MessageData originalData, DES_Key originalKey, uint8_t mode);
```

## Example

An example is showed in [DES_test.c](DES_test.c). This example can be used directly in [CamelStudioX](https://github.com/daizhirui/CamelStudioX_Mac/releases/latest).
