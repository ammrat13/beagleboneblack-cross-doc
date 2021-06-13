#include "pwr/cm.h"
#include "io/gpio.h"


int main(void) {

    // Set up the GPIO1 clock
    // It's off on reset
    gpio_enable(GPIO1);

    // Enable output on GPIO1 pin 21
    GPIO_REG_L(GPIO1, OE) &= ~(1<<21);

    // Set GPIO1 pin 21 high
    GPIO_REG_L(GPIO1, SETDATAOUT) = (1<<21);

    return 0;
}
