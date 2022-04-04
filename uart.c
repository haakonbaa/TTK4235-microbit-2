#include "uart.h"
#include "gpio.h"

#define UART_INT_RX_PIN 6
#define UART_INT_TX_PIN 8

void uart_init() {
    // Konfigurer pinnene som input i GPIO modulen
    // s147: 1: INPUT, 0 : OUTPUT
    GPIO0->PIN_CNF[UART_INT_RX_PIN] = 0; // UART_INT_RX (read)
    GPIO1->PIN_CNF[UART_INT_TX_PIN] = 1; // UART_INT_TX (transmit)

    // Konfigurer pinnene til å brukes av UART modulen s496
    UART->PSEL_RXD = UART_INT_RX_PIN | 0b0 << 5; // GPIO 0
    UART->PSEL_TXD = UART_INT_TX_PIN | 0b1 << 5; // GPIO 1

    // Set baudrate til 9600
    UART->BAUDRATE = 0x00275000; // s496

    // Fortell UART at vi ikke har CTS eller RTS s495
    UART->PSEL_CTS = 0b1 << 31;
    UART->PSEL_RTS = 0b1 << 31;

    // ENABLE UART og start å ta i mot meldinger
    UART->ENABLE = 4;
    UART->TASKS_STARTRX = 1;
}

void uart_send(char letter) {
    // fig s176
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;
    while (UART->EVENTS_TXDRDY != 1){}
    UART->TASKS_STOPRX = 1;
}