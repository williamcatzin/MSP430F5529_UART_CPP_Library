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

#define SIZE 14     // Size to hold the message: "Embedded C++!\n"

int main() {
    UART serial;        // Instantiate UART object      
    char data[SIZE];    // array to hold incoming message

    // Super Loop
    while(1) {
        serial.Rx0(data, SIZE);     // Receive message over UART0
        serial.Tx1(data, SIZE);     // Transmmit message over UART1
    }
}