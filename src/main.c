#include "pwr/cm.h"
#include "io/gpio.h"


int main(void) {

    gpio_enable(GPIO1);
    gpio_make_output(GPIO1, 1<<21);
    gpio_set(GPIO1, 1<<21);

    return 0;
}
