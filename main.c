#include "gpio.h"
#include "uart.h"

int isADown() {
    return (~GPIO0->IN) & (1 << 14);
}

int isBDown() {
    return ((~GPIO0->IN) & (1 << 23));
}

int main() {
    gpio_init();
    gpio_lights_off();
    uart_init();
     while (1) {
        if (isADown()) {
            uart_send('A');
        }
        if (isBDown()) {
            uart_send('B');
        }
    }
    return 0;
}

/* Oppgaver

pinn UART_INT_RX: P0 6 (READ)
pinn UART_INT_TX: P1 8 (TRANSMIT)

*/