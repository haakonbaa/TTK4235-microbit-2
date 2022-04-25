#include "gpio.h"
#include "uart.h"

typedef enum {
    NONE = 0,
    A,
    B,
} BtnState;

int main() {
    gpio_init();
    gpio_lights_off();
    uart_init();
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