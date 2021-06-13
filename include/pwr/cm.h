#pragma once

#include <stddef.h>
#include <stdint.h>

#include "io/gpio.h"


// Gets a register inside a clock domain
//
// This macro returns a register inside of a clock domain as an lvalue. It uses
// the constants defined below. To use, set
//  * `domain` to a clock domain, like `WKUP`, `PER`, ...
//  * `reg` to the name of the register without the prefix, like `GPIO0_CLKCTRL`
#define CM_REG(domain, reg) ( *( \
    (volatile uint32_t *const) \
    (CM_ ## domain ## _BASE + CM_ ## domain ## _ ## reg ## _OFF) \
) )


// The constants for the base addresses of the clock domain control registers
#define CM_PER_BASE  (0x44e00000)
#define CM_WKUP_BASE (0x44e00400)


// The offsets for GPIO clock control registers
#define CM_WKUP_GPIO0_CLKCTRL_OFF (0x008)
#define CM_PER_GPIO1_CLKCTRL_OFF  (0x0ac)
#define CM_PER_GPIO2_CLKCTRL_OFF  (0x0b0)
#define CM_PER_GPIO3_CLKCTRL_OFF  (0x0b4)
// An array containing the addresses of the clock control registers for GPIO
extern volatile uint32_t *const CM_GPIO_CLKCTRL[NUM_GPIO];
