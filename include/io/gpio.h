#pragma once

#include <stddef.h>
#include <stdint.h>


// Get a register for a particular GPIO module
//
// These macros returns a register inside of a GPIO module as an lvalue. They
// use the constants and variables defined below. To use, set
//  * `module` to GPIO0, GPIO1, GPIO2, GPIO3
//  * `reg` to the name of the register without the prefix, like `OE`
//
// The `GPIO_REG_L` macro provides additional safety, only accepting literal
// values for the first argument instead of any variable containing the required
// value.
#define GPIO_REG_L(module, reg) ( *( \
    (volatile uint32_t *const) \
    (module ## _BASE + GPIO_ ## reg ## _OFF) \
) )
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
#define GPIO_SYSCONFIG_OFF (0x010)
#define GPIO_SYSSTATUS_OFF (0x114)
#define GPIO_CTRL_OFF      (0x130)
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


// Ensure that a GPIO module is up and running
void gpio_enable(gpio_t num);
// Ensure that a GPIO module is no longer running
void gpio_disable(gpio_t num);

// Set the output enable `mask` of a module
void gpio_oe_set(gpio_t num, uint32_t mask);
// Turn on the `mask`ed bits
void gpio_set(gpio_t num, uint32_t mask);
// Turn off the `mask`ed bits
void gpio_clr(gpio_t num, uint32_t mask);

// Read from a GPIO module
uint32_t gpio_get(gpio_t num);
