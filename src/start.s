.section ".text.bootstrap", "axw"


.globl _start
_start:

    // Set the state of the processor
    mrs r0, cpsr
    orr r0, r0, #0x000000c0  // Disable IRQ and FIQ
    msr cpsr, r0

    // Call main
    bl main

loop:
    b loop
