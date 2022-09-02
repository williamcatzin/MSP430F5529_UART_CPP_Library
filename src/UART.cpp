#include "UART.hpp"
#include <msp430.h>


//  UART class contructor definiton
UART::UART()
{
    // Stop Watchdog Timer
    WDTCTL = WDTPW + WDTHOLD;

    // Port 3
    // Select P3.3(Tx) and P3.4(Rx)
    P3SEL |= 0x18;
    // Initialize UART0
    this->UART0_Init();

    // Port 4
    // Select P4.4(Tx) and P4.5(Rx)
    P4SEL |= 0x30;
    // Initialize UART1
    this->UART1_Init();
}

// Initialize UART0 with buad rate of 9600
void UART::UART0_Init()
{
    // Reset UART state machine
    UCA0CTL1 |= UCSWRST;
    // Choose clock source with 32768 Hz
    UCA0CTL1 |= UCSSEL_1;
    // Set baud rate to 9600
    UCA0BR0 = 3;
    // Set bit rate to 32768 Hz
    UCA0BR1 = 0x00;
    // Set modulation register to UCBRSx = 3
    UCA0MCTL = 0x06;
    // Not used
    UCA0CTL0 = 0x00;
    // Start UCSI
    UCA0CTL1 &= ~UCSWRST;
}

// Initialize UART1 with buad rate of 9600
void UART::UART1_Init()
{
    // Reset UART state machine
    UCA1CTL1 |= UCSWRST;
    // Choose clock source with 32768 Hz
    UCA1CTL1 |= UCSSEL_1;
    // Set baud rate to 9600
    UCA1BR0 = 3;
    // Set bit rate to 32768 Hz
    UCA1BR1 = 0x00;
    // Set modulation register to UCBRSx = 3
    UCA1MCTL = 0x06;
    // Not used
    UCA1CTL0 = 0x00;
    // Start UCSI
    UCA1CTL1 &= ~UCSWRST;
}

//***************************************UART0(RX, TX)************************************
// Transmit subroutine
void UART::Tx0(char *data, const unsigned char size)
{
    volatile char i;
    // Iterate over the number of bytes to transmit
    for(i = 0; i < size; i++) {
        UCA0TXBUF = data[i];        // Insert byte into transmit buffer
        while(UCA0STAT & UCBUSY);   // Wait for transmit buffer to finish
    }

    UCA0TXBUF = 0x0A;           // newline
    while(UCA0STAT & UCBUSY);
    UCA0TXBUF = 0x0D;           // newline
    while(UCA0STAT & UCBUSY);
}

// Receive subroutine
void UART::Rx0(char *data, const unsigned char size)
{
    volatile char i;
    // Iterate over the number of bytes to receive
    for(i = 0; i < size; i++) {
        while(UCA0STAT & UCBUSY);       // Wait for Rx0 buffer
        data[i] = UCA0RXBUF;            // Move byte in receive buffer into data[i]
    }
}
//****************************************************************************************

//***************************************UART1(RX, TX)************************************
// Transmit subroutine
void UART::Tx1(char *data, const unsigned char size)
{
    volatile char i;
    // Iterate over the number of bytes to transmit
    for(i = 0; i < size; i++) {
        UCA1TXBUF = data[i];        // Insert byte into transmit buffer
        while(UCA1STAT & UCBUSY);   // Wait for transmit buffer
    }

    UCA1TXBUF = 0x0A;           // newline
    while(UCA1STAT & UCBUSY);
    UCA1TXBUF = 0x0D;           // newline
    while(UCA1STAT & UCBUSY);
}

// Receive subroutine
void UART::Rx1(char *data, const unsigned char size)
{
    volatile char i;
    // Iterate over the number of bytes
    for(i = 0; i < size; i++) {
        while(UCA1STAT & UCBUSY);       // Wait for Rx0 buffer
        data[i] = UCA1RXBUF;            // Store incoming byte in the ith location in data
    }
}

