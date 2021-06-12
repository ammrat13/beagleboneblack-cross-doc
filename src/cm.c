#include "cm.h"

#include <stddef.h>


static const uintptr_t CM_PER_BASE  = 0x44e00000;
static const uintptr_t CM_WKUP_BASE = 0x44e00400;


volatile uint32_t *const CM_WKUP_GPIO0_CLKCTRL_PTR = (volatile uint32_t *const) (CM_WKUP_BASE + 0x008);
volatile uint32_t *const CM_PER_GPIO1_CLKCTRL_PTR  = (volatile uint32_t *const) (CM_PER_BASE  + 0x0ac);
volatile uint32_t *const CM_PER_GPIO2_CLKCTRL_PTR  = (volatile uint32_t *const) (CM_PER_BASE  + 0x0b0);
volatile uint32_t *const CM_PER_GPIO3_CLKCTRL_PTR  = (volatile uint32_t *const) (CM_PER_BASE  + 0x0b4);
