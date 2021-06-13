#include "pwr/cm.h"


volatile uint32_t *const CM_GPIO_CLKCTRL[NUM_GPIO] = {
    &CM_REG(WKUP, GPIO0_CLKCTRL),
    &CM_REG(PER,  GPIO1_CLKCTRL),
    &CM_REG(PER,  GPIO2_CLKCTRL),
    &CM_REG(PER,  GPIO3_CLKCTRL),
};
