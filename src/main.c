#include <stddef.h>
#include <stdint.h>


const uintptr_t CM_PER_BASE              = 0x44e00000;
const size_t    CM_PER_GPIO1_CLKCTRL_OFF = 0xac;

const uintptr_t GPIO1_BASE            = 0x4804C000;
const size_t    GPIO_OE_OFF           = 0x134;
const size_t    GPIO_SETDATAOUT_OFF   = 0x194;
const size_t    GPIO_CLEARDATAOUT_OFF = 0x190;


int main(void) {

    // Set up the GPIO1 clock
    // It's off on reset
    *((volatile uint32_t*) (CM_PER_BASE + CM_PER_GPIO1_CLKCTRL_OFF)) = (1<<18) | (2);

    // Enable output on GPIO1 pin 21
    *((volatile uint32_t*) (GPIO1_BASE + GPIO_OE_OFF)) &= ~(1<<21);

    // Set GPIO1 pin 21 high
    *((volatile uint32_t*) (GPIO1_BASE + GPIO_SETDATAOUT_OFF)) = (1<<21);

    return 0;
}
