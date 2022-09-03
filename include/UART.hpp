/********************************************************************
File: UART.hpp
Author: William Catzin
Date: 2022-08-27
Description: UART low-level driver for the MSP430F5529

The MSP430F5529 contains a universal serial communication interface 
(USCI), which supports multiple serial communication modes with
one hardware module. The module contains two UARTs.

TODO: Add option to change buad rate
*********************************************************************/
#ifndef UART_H
#define UART_H

#include <msp430.h>


// Class for the UART driver
class UART 
{
    
    public:
        UART();               
        void Tx0(char *data, const unsigned char size);         // Transmit for UART0
        void Rx0(char *data, volatile unsigned char index);     // Receive for UART0 
        void Tx1(char *data, const unsigned char size);         // Transmit for UART1
        void Rx1(char *data, volatile unsigned char index);     // Receive for UART1

        void enable_RxISR()
        {
            // Enable receive interrupt
            UCA0IE |= UCRXIE;
        }

        void disable_RxISR()
        {
            UCA0IE &= ~UCRXIE;
        }
        
                                       
    private:
        void UART0_Init();                  // Initialize UART0
        void UART1_Init();                  // Initialize UART1
};
#endif


