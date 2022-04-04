#ifndef _UART_H_
#define _UART_H_

#define MDIFF(second,first) (second-first-0x4)/0x4 

#include <stdint.h>

#define vol32 volatile uint32_t

// s 489

#define UART ((NRF_UART_REG*)0x40002000) 

typedef struct {
    vol32 TASKS_STARTRX;                     // 0x000 Start UART receiver
    vol32 TASKS_STOPRX;                     // 0x004 Stop UART receiver
    vol32 TASKS_STARTTX;                    // 0x008 Start UART transmitter
    vol32 TASKS_STOPTX;                     // 0x00C Stop UART transmitter
    vol32 RESERVED_00[MDIFF(0x1C,0x0C)];
    vol32 TASKS_SUSPEND;                    // 0x01C Suspend UART
    vol32 RESERVED_01[MDIFF(0x100,0x1C)];
    vol32 EVENTS_CTS;                       // 0x100 CTS is activated (set low). Clear To Send.
    vol32 EVENTS_NCTS;                      // 0x104 CTS is deactivated (set high). Not Clear To Send.
    vol32 EVENTS_RXDRDY;                    // 0x108 Data received in RXD
    vol32 RESERVED_02[MDIFF(0x11C,0x108)];
    vol32 EVENTS_TXDRDY;                    // 0x11C Data sent from TXD
    vol32 RESERVED_03[MDIFF(0x124,0x11C)];
    vol32 EVENTS_ERROR;                     // 0x124 Error detected
    vol32 RESERCED04[MDIFF(0x144,0x124)];
    vol32 EVENTS_RXTO;                      // 0x144 Receiver timeout
    vol32 RESERCED05[MDIFF(0x200,0x144)];
    vol32 SHORTS;                           // 0x200 Shortcuts between local events and tasks
    vol32 RESERCED06[MDIFF(0x304,0x200)];
    vol32 INTENSET;                         // 0x304 Enable interrupt
    vol32 INTENCLR;                         // 0x308 Disable interrupt
    vol32 RESERCED07[MDIFF(0x480,0x308)];
    vol32 ERRORSRC;                         // 0x480 Error source
    vol32 RESERCED08[MDIFF(0x500,0x480)];
    vol32 ENABLE;                           // 0x500 Enable UART
    vol32 RESERCED09[MDIFF(0x508,0x500)];
    vol32 PSEL_RTS;                         // 0x508 Pin select for RTS
    vol32 PSEL_RXD;                         // Feil i datablad! 0x50C Pin select for TXD
    vol32 PSEL_CTS;                         // 0x510 Pin select for CTS
    vol32 PSEL_TXD;                         // Feil i datablad! 0x514 Pin select for RXD
    vol32 RXD;                              // 0x518 RXD register
    vol32 TXD;                              // 0x51C TXD register
    vol32 RESERVED_10[MDIFF(0x524,0x51C)];
    vol32 BAUDRATE;                         // 0x524 Baud rate. Accuracy depends on the HFCLK source selected.
    vol32 RESERVED_11[MDIFF(0x56C,0x524)];
    vol32 CONFIG;                           // 0x56C Configuration of parity and hardware flow control

} NRF_UART_REG;

void uart_init();

void uart_send(char letter);

char uart_read();

#endif