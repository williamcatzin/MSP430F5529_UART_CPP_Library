/***************************************************
File: main.cpp
Author: William Catzin
Date: 2022-09-01

Description: Example code to receive data
over UART0 (P3.3(Rx) and P3.4(Tx)) and transmit
the received message over UART1 (USB-to-UART bridge)
to a PuTTY session
******************************************************/

#include "UART.hpp"


UART serial;                        // Instantiate UART object
#define SIZE 14                     // Number of bytes to holde the message: "Embedded C++!\n"
char rxDATA[SIZE];                  // Array to store message
volatile unsigned char counter = 0;   // Counter to track data

int main() {
    __enable_interrupt();                   // Enable global interrupts
    serial.enable_RxISR();                  // Enable Rx0 interrupt
    char msg0[] = "Received Message!\n";
    char msg1[] = "Waiting...\n";
    // Super Loop
    while(1) {
        if(counter == SIZE) {
            serial.Tx1(rxDATA, SIZE);                           // Transmit message over USB-to-UART bridge
            serial.Tx1(msg0, sizeof(msg0)/sizeof(msg0[0]));
            counter = 0;                                        // Reset counter
            serial.enable_RxISR();                              // Enable global and Rx0 interrupts
            __enable_interrupt();
        } else {
            serial.Tx1(msg1, sizeof(msg1)/sizeof(msg1[0]));     // Transmit message to indicate pending
        }
    }
}

//*****************Receive Interrupt Service Routine********************
#pragma vector=USCI_A0_VECTOR
__interrupt void Rx0_ISR(void) 
{
    UCA0IFG &= ~UCRXIFG;            // Clear interrupt flag
    serial.Rx0(rxDATA, counter);      // Retrieve data
    counter++;
    // Disable global and Rx0 interrupts to print message                        
    if(counter == SIZE) {
        serial.disable_RxISR();
        __disable_interrupt();
    }
}
