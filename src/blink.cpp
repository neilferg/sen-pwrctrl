#include "pico/stdlib.h"
#include "hardware/pio.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "blink.pio.h"
void blink_program_init(PIO pio, uint sm, uint offset, uint pin, float div);

#ifdef __cplusplus
}
#endif


// Helper function (for use in C program) to initialize this PIO program
void blink_program_init(PIO pio, uint sm, uint offset, uint pin, float div)
{
    // Sets up state machine and wrap target. This function is automatically
    // generated in blink.pio.h.
    pio_sm_config c = blink_program_get_default_config(offset);

    // Allow PIO to control GPIO pin (as output)
    pio_gpio_init(pio, pin);

    // Connect pin to SET pin (control with 'set' instruction)
    sm_config_set_set_pins(&c, pin, 1);

    // Set the pin direction to output (in PIO)
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);
    
    // Set the clock divider for the state machine
    sm_config_set_clkdiv(&c, div);

    // Load configuration and jump to start of the program
    pio_sm_init(pio, sm, offset, &c);
}

