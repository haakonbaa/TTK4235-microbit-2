#include "gpio.h"
#include "uart.h"

int main() {
    gpio_init();
    gpio_lights_off();
    gpio_lights_on();
    uart_init();
    uart_send('H');
    while (1){
        uart_send('H');
        uart_send('\n');
    }
    return 0;
}

/* Oppgaver

pinn UART_INT_RX: P0 6 (READ)
pinn UART_INT_TX: P1 8 (TRANSMIT)

*/