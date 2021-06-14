#pragma once

#include <stdint.h>

#include "ctrl/ctrl.h"


// Get a pad configuration register
//
// This macro returns a pad configuration register as a lvalue. It uses the
// constants defined below. To use, set `pad` to the "pin name" of the pad.
//
// See Datasheet 4.2
#define PIN_CTRL_REG(pad) ( *( \
    (volatile uint32_t *const) \
    (CTRL_BASE + CTRL_CONF_ ## pin ## _OFF) \
) )


// Offsets for the pad configuration registers
// See TRM 9.3
#define CTRL_CONF_GPMC_A5_OFF (0x0854)
#define CTRL_CONF_GPMC_A6_OFF (0x0858)
#define CTRL_CONF_GPMC_A7_OFF (0x085c)
#define CTRL_CONF_GPMC_A8_OFF (0x0860)
