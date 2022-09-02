# MSP430F5529 UART DRIVER

## Getting Started

1. Set up msp430-gcc and mspdebug

Use the link to setup your environment and toolchain: [MSP430-GCC-TI Toolchain](https://github.com/chintal/toolchains/blob/master/msp430-gcc-ti.md)

2. Clone this repository

```bash
$ git clone https://github.com/williamcatzin/MSP430F5529_UART_CPP_Library.git
```
Build an example application

```bash
$ cd MSP430F5529_UART_CPP_LIBRARY
$ make
```
You should see the following

```bash
Compiling...
msp430-gcc -mmcu=msp430f5529 -Iinclude  -c src/main.cpp -o bin/main.o
Compiling...
msp430-gcc -mmcu=msp430f5529 -Iinclude  -c src/UART.cpp -o bin/UART.o
Linking...
msp430-gcc -mmcu=msp430f5529 -o bin/main bin/main.o bin/UART.o
Finished!
```
Then run

```bash
make flash
```
You should see the following

```bash
Flashing...
mspdebug tilib "prog bin/main"
MSPDebug version 0.22 - debugging tool for MSP430 MCUs
Copyright (C) 2009-2013 Daniel Beer <dlbeer@gmail.com>
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

MSP430_GetNumberOfUsbIfs
MSP430_GetNameOfUsbIf
Found FET: ttyACM0
MSP430_Initialize: ttyACM0
Firmware version is 31501001
MSP430_VCC: 3000 mV
MSP430_OpenDevice
MSP430_GetFoundDevice
Device: MSP430F5529 (id = 0x002f)
8 breakpoints available
MSP430_EEM_Init
Chip ID data: 55 29 19
Erasing...
Programming...
Writing  806 bytes at 4400 [section: .text]...
Writing  128 bytes at ff80 [section: .vectors]...
Done, 934 bytes total
MSP430_Run
MSP430_Close
```

