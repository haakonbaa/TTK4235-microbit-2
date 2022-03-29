#include "gpio.h"

int main() {
    gpio_init();
    gpio_lights_off();
    gpio_lights_on();
    while (1){
        // nothing
    }
    return 0;
}