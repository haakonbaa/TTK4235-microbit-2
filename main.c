#include "gpio.h"
#include "uart.h"

int isADown() {
    return (~GPIO0->IN) & (1 << 14);
}

int isBDown() {
    return ((~GPIO0->IN) & (1 << 23));
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
    BtnState state = NONE;
    while (1) { 
        if (isADown()) {
            if (state != A) {
                uart_send('A');
            }
            state = A;
        } else if (isBDown()) {
            if (state != B) {
                uart_send('B');
            }
           state = B;
        } else {
            state = NONE;
        }
    }
    return 0;
}

/* Oppgaver

pinn UART_INT_RX: P0 6 (READ)
pinn UART_INT_TX: P1 8 (TRANSMIT)

*/