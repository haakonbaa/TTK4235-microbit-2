#include "gpio.h"
#include "uart.h"

int main() {
    gpio_init();
    gpio_lights_off();
    gpio_lights_on();
    while (1){
        // nothing
    }
    return 0;
}

/* Oppgaver

pinn UART_INT_RX: P0 6 (READ)
pinn UART_INT_TX: P1 8 (TRANSMIT)

*/