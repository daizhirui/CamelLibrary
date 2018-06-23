# Input Output Library for M2   {#IO}

## Interface

```C
void RT_IO_SetOutput(io);

void RT_IO_SetInput(io);

void RT_IO_SetInputOutput(io, mode);

void RT_IO_SetInputOutput16(mode);

void RT_IO_SetHigh(io);

void RT_IO_SetLow(io);

void RT_IO_SetLevel(io, level);

void RT_IO_SetLevel16(level);

uint8_t RT_IO_Read(io);

uint16_t RT_IO_Read16();
```

## Example

```C
// set IO as Input
RT_IO_SetOutput(5);                 // set io5 OUTPUT
RT_IO_SetInputOutput(5, OUTPUT);    // also set io5 OUTPUT.
RT_IO_SetInputOutput16(OUTPUT<<5);  // set io5 OUTPUT, but other io input.

// set IO output HIGH
RT_IO_SetHigh(5);           // set io5 output HIGH.
RT_IO_SetLevel(5, HIGH);    // also set io5 output HIGH.
RT_IO_SetLevel16(HIGH<<5);  // set io5 output HIGH, but other io output LOW.

// read io
uint8_t levelOfOneIO = RT_IO_Read(5);   // read io5
uint16_t levelOf16IO = RT_IO_Read16();  // read all io.
```
