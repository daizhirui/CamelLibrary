/**
 * @file DES.c
 * @author Zhirui Dai
 * @date 14 Jun 2018
 * @copyright 2018 Zhirui
 * @brief Standard Encryption Standard Library for M2
 */
#include "DES.h"
//#define DEBUG
#ifdef DEBUG
#include "stdio.h"
#endif

/**
* @brief Half of the key.
*/
typedef uint32_t half_DES_Key;

/**
* @brief Store the C key and the D key of a DES key.
*/
typedef struct {
    half_DES_Key cKey;
    half_DES_Key dKey;
} DES_Key_pair;

/*! \cond PRIVATE */
#define __high32__(X)                   (X.apart[1])
#define __low32__(X)                    (X.apart[0])
#define __getBitAt__(val, pos)          (((val) & (0x1 << (pos))) >> (pos))
#define __L_part__(X)                   (X.apart[1])
#define __R_part__(X)                   (X.apart[0])
/*! \endcond */

/*! \cond PRIVATE */
// Table PC-1 for generating permuted key K+ from original key K.
const uint8_t __permuted_key_table_PC1__[56] = { \
    7,15,23,31,39,47,55, \
    63,6,14,22,30,28,46, \
    54,62,5,13,21,29,37, \
    45,53,61,4,12,20,28, \
    1,9,17,25,33,41,49, \
    57,2,10,18,26,34,42, \
    50,58,3,11,19,27,35, \
    43,51,59,36,44,52,60
};

// Table for shift C key and D key.
const uint8_t __keyPair_leftshift_table__[17] = {
    0, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

// Table PC-2 for generating final 16 48-bit subKeys.
const uint8_t __permuted_key_table_PC2__[48] = { \
    42, 39, 45, 32, 55, 51, \
    53, 28, 41, 50, 35, 46, \
    33, 37, 44, 52, 30, 48, \
    40, 49, 29, 36, 43, 54, \
    15, 4, 25, 19, 9, 1, \
    26, 16, 5, 11, 23, 8, \
    12, 7, 17, 0, 22, 3, \
    10, 14, 6, 20, 27, 24
};

// IP Table for initially permuted message data.
const uint8_t __permuted_message_table_IP__[64] = {
    6, 14, 22, 30, 38, 46, 54, 62, \
    4, 12, 20, 28, 36, 44, 52, 60, \
    2, 10, 18, 26, 34, 42, 50, 58, \
    0, 8, 16, 24, 32, 40, 48, 56, \
    7, 15, 23, 31, 39, 47, 55, 63, \
    5, 13, 21, 29, 37, 45, 53, 61, \
    3, 11, 19, 27, 35, 43, 51, 59, \
    1, 9, 17, 25, 33, 41, 49, 57
};

// Table for expanding 32bit data to 48bit.
const uint8_t __E_BIT_SELECTION_TABLE__[48] = {
    0, 31, 30, 29, 28, 27, \
    28, 27, 26, 25, 24, 23, \
    24, 23, 22, 21, 20, 19, \
    20, 19, 18, 17, 16, 15, \
    16, 15, 14, 13, 12, 11, \
    12, 11, 10, 9, 8, 7, \
    8, 7, 6, 5, 4, 3, \
    4, 3, 2, 1, 0, 31
};

// Table for compressing 48bit data to 32bit
const uint8_t __S_TABLE__[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12 , 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

// Table for permuting 32bit data.
const uint8_t __PERMUTATION_P_TABLE__[32] = {
    16, 25, 12, 11, \
    3, 20, 4, 15, \
    31, 17, 9, 6, \
    27, 14, 1, 22, \
    30, 24, 8, 18, \
    0, 5, 29, 23, \
    13, 19, 2, 26, \
    10, 21, 28, 7
};

// Table for permuting 64bit data finally.
const uint8_t __PERMUTATION_P_1_TABLE__[64] = {
    24, 56, 16, 48, 8, 40, 0, 32, \
    25, 57, 17, 49, 9, 41, 1, 33, \
    26, 58, 18, 50, 10, 42, 2, 34, \
    27, 59, 19, 51, 11, 43, 3, 35, \
    28, 60, 20, 52, 12, 44, 4, 36, \
    29, 61, 21, 53, 13, 45, 5, 37, \
    30, 62, 22, 54, 14, 46, 6, 38, \
    31, 63, 23, 55, 15, 47, 7, 39
};
/*! \endcond */

/**
* @brief Generate 16 subKeys with the original DES key.
* @param originalKey The original DES key.
* @return DES_Key*   A pointer to an array of 17 keys: 1 original key and 16 subKeys.
*/
DES_Key* DES_generateSubKeys(const DES_Key originalKey)
{
	static DES_Key subKeys[17];

	uint8_t index = 0, pos = 0, shiftLen;
	uint32_t bit = 0;

    // Generate initial permuted key K_0
    subKeys[0].key = 0x0;
    for (; index < 56; index++) {
        pos = __permuted_key_table_PC1__[index];
        if (pos < 32) {   // get bit from low 32bit of originalKey
            bit = __getBitAt__(__low32__(originalKey), pos);
        } else {  // get bit from hight 32bit of originalKey
            bit = __getBitAt__(__high32__(originalKey), pos - 32);
        }
        if (index < 24) {
            __high32__(subKeys[0]) <<= 1;
            __high32__(subKeys[0]) |= (bit & 0x1);
        }
        else {
            __low32__(subKeys[0]) <<= 1;
            __low32__(subKeys[0]) |= (bit & 0x1);
        }
    }
    // Generate C_0 and D_0
    DES_Key_pair keyPairGroup[17];
    keyPairGroup[0].dKey = (__low32__(subKeys[0]) & 0xFFFFFFF);
    keyPairGroup[0].cKey = __high32__(subKeys[0]);
    keyPairGroup[0].cKey <<= 4;
    keyPairGroup[0].cKey |= (__low32__(subKeys[0]) >> 28);
    // Generate cKey and dKey for K_1 ~ K_16
    for (index = 1; index < 17; index++) {
        shiftLen = __keyPair_leftshift_table__[index];
        keyPairGroup[index].cKey = (keyPairGroup[index - 1].cKey << (4 + shiftLen)) >> 4;
        keyPairGroup[index].cKey |= (keyPairGroup[index - 1].cKey >> (28 - shiftLen));
        keyPairGroup[index].dKey = (keyPairGroup[index - 1].dKey << (4 + shiftLen)) >> 4;
        keyPairGroup[index].dKey |= (keyPairGroup[index - 1].dKey >> (28 - shiftLen));
    }
    // Assemble K_1 ~ K_16 from cKeys and dKeys.
    uint8_t bitIndex;
    for (index = 1; index < 17; index++) {
        subKeys[index].key = 0x0;
        for (bitIndex = 0; bitIndex < 48; bitIndex++) { // generate key[index]
            pos = __permuted_key_table_PC2__[bitIndex]; // pos = which bit to get
            if (pos < 28) { // get bit from dKey
                bit = __getBitAt__(keyPairGroup[index].dKey, pos);
            } else {    // get bit from cKey
                bit = __getBitAt__(keyPairGroup[index].cKey, pos - 28);
            }
            if (bitIndex < 16) {    // set the bit in high32 part
                __high32__(subKeys[index]) <<= 1;
                __high32__(subKeys[index]) |= bit;
            } else {    // set the bit in low32 part
                __low32__(subKeys[index]) <<= 1;
                __low32__(subKeys[index]) |= bit;
            }
        }
    }
    return subKeys;
}

/*! \cond PRIVATE */
/**
 * @brief Calculate the R part with the last item and the current key.
 * @param lastItem  The message data combined by the last L part and R part.
 * @param key       The current DES key, 48-bit.
 * @return uint32_t The R part.
 */
uint32_t __calculate_R_part__(MessageData lastItem, DES_Key key)
{
    register uint32_t r_part = 0x0;
    MessageData temp;
    temp.data = 0x0;

    register uint32_t index, bit, pos, i, j;
    // expand R part of lastItem from 32bit to 48bit
    for (index = 0; index < 16; index++) {  // high 16 bits
        pos = __E_BIT_SELECTION_TABLE__[index];
        __high32__(temp) <<= 1;
        __high32__(temp) |= __getBitAt__(__R_part__(lastItem), pos);
    }
    for (index = 16; index < 48; index++) { // low 32 bits
        pos = __E_BIT_SELECTION_TABLE__[index];
        __low32__(temp) <<= 1;
        __low32__(temp) |= __getBitAt__(__R_part__(lastItem), pos);
    }
    __low32__(temp) ^= __low32__(key);      // XOR with the key, low32
    __high32__(temp) ^= __high32__(key);    // XOR with the key, high32
    __high32__(temp) &= 0xFFFF;             // make sure high 16bit of high32 part is 0x0.
    // index = 0
    bit = (__high32__(temp) & (0x3F << 10)) >> 10;
    i = (((bit & 0x20) >> 4) | (bit & 0x1));
    j = (bit & 0x1e) >> 1;
    r_part <<= 4;
    r_part |= (__S_TABLE__[0][i][j] & 0xF);
    // index = 1
    bit = (__high32__(temp) & (0x3F << 4)) >> 4;
    i = (((bit & 0x20) >> 4) | (bit & 0x1));
    j = (bit & 0x1e) >> 1;
    r_part <<= 4;
    r_part |= (__S_TABLE__[1][i][j] & 0xF);
    // index = 2
    bit = ((__high32__(temp) & 0xF) << 2) | (__low32__(temp) >> 30);
    i = (((bit & 0x20) >> 4) | (bit & 0x1));
    j = (bit & 0x1e) >> 1;
    r_part <<= 4;
    r_part |= (__S_TABLE__[2][i][j] & 0xF);
    // index >= 3
    for (index = 3, pos = 24; index < 8; index++, pos -= 6) {   // compress R part from 48bit to 32bit by S_TABLE
        bit = (__low32__(temp) & (0x3F << pos)) >> pos;
        i = (((bit & 0x20) >> 4) | (bit & 0x1));
        j = (bit & 0x1e) >> 1;
        r_part <<= 4;
        r_part |= (__S_TABLE__[index][i][j] & 0xF);
    }
    // P
    __R_part__(temp) = r_part;
    r_part = 0x0;               // clear part
    for (index = 0; index < 32; index++) {
        pos = __PERMUTATION_P_TABLE__[index];
        r_part <<= 1;
        r_part |= __getBitAt__(__R_part__(temp), pos);
    }
    r_part ^= __L_part__(lastItem);   // XOR L(n-1)
    return r_part;
}
/*! \endcond */

/**
* @brief Process data with specific subkeys and specific mode.
* @param originalData   data to process.
* @param subKeys        17 keys: 1 original key and 16 subkeys.
* @param mode           DES_ENCRYPT_MODE or DES_DECRYPT_MODE
* @return MessageData   Processed data.
*/
MessageData DES_process(MessageData originalData, DES_Key* subKeys, uint8_t mode)
{
    register uint32_t index, pos;
    MessageData output, temp;
    // Initialize output and temp.
    output.data = 0x0;
    temp.data = 0x0;

    // Generate initial permuted data
    for (index = 0; index < 32; index++) {  // high 32 bits
        pos = __permuted_message_table_IP__[index];
        __L_part__(temp) <<= 1;
        if (pos < 32) { // get bit from low32
            __L_part__(temp) |= __getBitAt__(__low32__(originalData), pos);
        } else {    // get bit from high32
            __L_part__(temp) |= __getBitAt__(__high32__(originalData), pos - 32);
        }
    }
    for (index = 32; index < 64; index++) { // low 32 bits
        pos = __permuted_message_table_IP__[index];
        __R_part__(temp) <<= 1;
        if (pos < 32) { // get bit from low32
            __R_part__(temp) |= __getBitAt__(__low32__(originalData), pos);
        } else {    // get bit from high32
            __R_part__(temp) |= __getBitAt__(__high32__(originalData), pos - 32);
        }
    }

    // Iteration
    // n = [1, 16]
    // mode = ENCRYPT_MODE = 0x0: L(n) = R(n-1), R(n) = L(n-1) + f(R(n-1), subKey(n))
    // mode = DECRYPT_MODE = 0x1: L(n) = R(n-1), R(n) = L(n-1) + f(R(n-1), subKey(17-n))
    // MessageData.apart[0] = R part, MessageData.apart[1] = L part
    if (mode == DES_DECRYPT_MODE) { // Decrypt mode
        for (index = 1; index < 17; index++) {  // Iteration of L part and R part
            __L_part__(output) = __R_part__(temp);
            __R_part__(output) = __calculate_R_part__(temp, subKeys[17 - index]);
            temp = output;
        }
    } else {    // Encrypt mode
        for (index = 1; index < 17; index++) {  // Iteration of L part and R part
            __L_part__(output) = __R_part__(temp);
            __R_part__(output) = __calculate_R_part__(temp, subKeys[index]);
            temp = output;
        }
    }

    // exchange L part and R part.
    __L_part__(temp) = __R_part__(output);
    __R_part__(temp) = __L_part__(output);
    output.data = 0x0;   // clear output
    // final permutation by P-1 table
    for (index = 0; index < 32; index ++) {     // high 32 bits
        pos = __PERMUTATION_P_1_TABLE__[index];
        __high32__(output) <<= 1;
        if (pos < 32) { // get bit from low32
            __high32__(output) |= __getBitAt__(__low32__(temp), pos);
        } else {    // get bit from high32
            __high32__(output) |= __getBitAt__(__high32__(temp), pos - 32);
        }
    }
    for (index = 32; index < 64; index ++) {    // low 32 bits
        pos = __PERMUTATION_P_1_TABLE__[index];
        __low32__(output) <<= 1;
        if (pos < 32) { // get bit from low32
            __low32__(output) |= __getBitAt__(__low32__(temp), pos);
        } else {    // get bit from high32
            __low32__(output) |= __getBitAt__(__high32__(temp), pos - 32);
        }
    }
    return output;
}

/**
* @brief Process data with specific original key and specific mode.
* @param originalData   data to process.
* @param originalKey    the original key.
* @param mode           DES_ENCRYPT_MODE or DES_DECRYPT_MODE
* @return MessageData   Processed data.
*/
MessageData DES(MessageData originalData, DES_Key originalKey, uint8_t mode)
{
    return DES_process(originalData, DES_generateSubKeys(originalKey), mode);
}
