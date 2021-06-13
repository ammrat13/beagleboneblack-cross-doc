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
    // See TRM 25.4.1.15, TRM 25.4.1.2
    GPIO_REG(num, CTRL) = (0x0 << 0);
    GPIO_REG(num, SYSCONFIG) = (0x2 << 3) | (0x1 << 0);
}
