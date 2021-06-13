#include "io/gpio.h"

#include "pwr/cm.h"


const uintptr_t GPIO_BASE[NUM_GPIO] = {
    GPIO0_BASE,
    GPIO1_BASE,
    GPIO2_BASE,
    GPIO3_BASE,
};


void gpio_enable(gpio_t num) {
    // Turn on the required and optional clock, then wait for fully functional
    // See TRM 8.1.12.2.3
    *CM_GPIO_CLKCTRL[num] = (0x1 << 18) | (0x2 << 0);
    while((*CM_GPIO_CLKCTRL[num] >> 16 & 0x3) != 0x0);

    // Enable the module
    // See TRM 25.4.1.15
    GPIO_REG(num, CTRL) = (0x0 << 0);

    // Reset the module and wait for completion
    // See TRM 25.4.1.2, TRM 25.4.1.14
    GPIO_REG(num, SYSCONFIG) = (0x1 << 1);
    while((GPIO_REG(num, SYSSTATUS) >> 0 & 0x1) == 0x0);

    // Disable the debounce clock since we only needed it for reset
    // Again, wait for fully functional
    // See TRM 8.1.12.2.3
    *CM_GPIO_CLKCTRL[num] &= ~(0x1 << 18);
    while((*CM_GPIO_CLKCTRL[num] >> 16 & 0x3) != 0x0);

    // Enable the module and turn on idling
    // See TRM 25.4.1.2
    GPIO_REG(num, SYSCONFIG) = (0x2 << 3) | (0x1 << 0);
}

void gpio_disable(gpio_t num) {
    // Disable the module completely
    // See TRM 25.4.1.15
    GPIO_REG(num, CTRL) = (0x1 << 0);

    // Disable the clocks completely and wait
    // See TRM 8.1.12.2.3
    *CM_GPIO_CLKCTRL[num] = (0x0 << 18) | (0x0 << 0);
    while((*CM_GPIO_CLKCTRL[num] >> 16 & 0x3) != 0x3);
}


// See TRM 25.4.1.16
void gpio_make_input(gpio_t num, uint32_t mask) {
    GPIO_REG(num, OE) |= mask;
}
void gpio_make_output(gpio_t num, uint32_t mask) {
    GPIO_REG(num, OE) &= ~mask;
}

// See TRM 25.4.1.18, TRM 25.4.1.26, TRM 25.4.1.25
void gpio_set(gpio_t num, uint32_t mask) {
    GPIO_REG(num, SETDATAOUT) = mask;
}
void gpio_clr(gpio_t num, uint32_t mask) {
    GPIO_REG(num, CLEARDATAOUT) = mask;
}


// See TRM 25.4.1.16, TRM 25.4.1.17, TRM 25.4.1.18
uint32_t gpio_get(gpio_t num) {
    // Get which bits are set as input
    uint32_t input_mask = GPIO_REG(num, OE);

    // Get the data we read from the GPIO and what we wrote to it
    uint32_t re = GPIO_REG(num, DATAIN);
    uint32_t wr = GPIO_REG(num, DATAOUT);

    // Return the read or written bits
    return (re & input_mask) | (wr & ~input_mask);
}
