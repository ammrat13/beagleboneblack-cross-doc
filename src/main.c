#include "pwr/cm.h"
#include "io/gpio.h"


int main(void) {

    gpio_reset(GPIO1);
    gpio_make_output(GPIO1, 1<<21);

    while(1) {
        volatile uint32_t i;

        gpio_enable(GPIO1);
        gpio_set(GPIO1, 1<<21);
        gpio_disable(GPIO1);
        for(i = 0; i < 1000000; i++);

        gpio_enable(GPIO1);
        gpio_clr(GPIO1, 1<<21);
        gpio_disable(GPIO1);
        for(i = 0; i < 1000000; i++);
    }

    return 0;
}
