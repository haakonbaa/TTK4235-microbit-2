#include <stdio.h>

#include "gpio.h"
#include "uart.h"

ssize_t _write(int fd, const void *buf, size_t count) {
    char *letter = (char *)(buf);
    for (int i = 0; i < count; i++) {
        uart_send(*letter);
        letter++;
    }
    return count;
}

ssize_t _read(int fd, void *buf, size_t count) {
    char *str = (char *)(buf);
    char letter;
    do {
        letter = uart_read();
    } while (letter == '\0');
    *str = letter;
    return 1;
}

typedef enum {
    NONE = 0,
    A,
    B,
} BtnState;

int main() {
    gpio_init();
    gpio_lights_off();
    uart_init();
    int a = 0;
    int b = 0;
    iprintf("\e[1;1H\e[2J");
    iprintf("Skriv inn et tall:\n\r");
    iscanf("%d",&a);
    iprintf("Skriv inn et nytt:\n\r");
    iscanf("%d",&b);
    iprintf("Tallene ganget sammen er: %d\n\r",a*b);
    iprintf("The average grade in TTK%d was in %d and %d: %c\n\r\n", 4235, 2019, 2018, 'C');
    BtnState state = NONE;
    while (1) {
        // Send A eller B om knappene trykkes ned
        if ((~GPIO0->IN) & (1 << 14)) {
            if (state != A) {
                uart_send('A');
            }
            state = A;
        } else if ((~GPIO0->IN) & (1 << 23)) {
            if (state != B) {
                uart_send('B');
            }
            state = B;
        } else {
            state = NONE;
        }
        // Lytt etter mottak. Toggle led-matrise dersom noe blir mottat
        char rec = uart_read();
        if (rec != '\0') {
            // Er det innafor å lese denne?
            if (GPIO0->OUT & (1 << 21)) {
                gpio_lights_off();
            } else {
                gpio_lights_on();
            }
        }
    }
    return 0;
}

/* Oppgaver

pinn UART_INT_RX: P0 6 (READ)
pinn UART_INT_TX: P1 8 (TRANSMIT)

*/