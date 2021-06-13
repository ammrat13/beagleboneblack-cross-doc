#pragma once

#include <stddef.h>
#include <stdint.h>


// Gets a register for a particular GPIO module
//
// This macro returns a register inside of a GPIO module as an lvalue. It uses
// the constants defined below. To use, set
//  * `module` to 0, 1, 2, 3
//  * `reg` to the name of the register without the prefix, like `OE`
#define GPIO_REG(module, reg) ( *( \
    (volatile uint32_t *const) \
    (GPIO_BASE[module] + GPIO_ ## reg ## _OFF) \
) )

// The constants for the base addresses of all the GPIO registers
#define GPIO0_BASE (0x44e07000)
#define GPIO1_BASE (0x4804c000)
#define GPIO2_BASE (0x481ac000)
#define GPIO3_BASE (0x481ae000)

// The offsets for GPIO control registers
#define GPIO_OE_OFF (0x134)
#define GPIO_SETDATAOUT_OFF   (0x194)
#define GPIO_CLEARDATAOUT_OFF (0x190)


// Types for accessing GPIOs programmatically
typedef enum gpio_t {
    GPIO0,
    GPIO1,
    GPIO2,
    GPIO3,
    NUM_GPIO
} gpio_t;

// An array of all the base addresses
extern const uintptr_t GPIO_BASE[NUM_GPIO];
