# Flash Library for M2  {#Flash}

## Interface

```C
void RT_Flash_Write(value, address);

void RT_Flash_Erase1k(address);

void RT_Flash_EraseFrom(address);

void RT_Flash_SetMAC(id);
```

## Example

```C
RT_Flash_Write(0x123, 0x10000000);     // write 0x123 to address 0x10000000
RT_Flash_Erase1k(0x10000000);          // erase 1k-byte, starting from address 0x10000000
```
