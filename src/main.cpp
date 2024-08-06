#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"




#ifdef __cplusplus
extern "C" {
#endif

#include "blink.pio.h"
void blink_program_init(PIO pio, uint sm, uint offset, uint pin, float div);

#ifdef __cplusplus
}
#endif

void setup_slave();

#define LED_PIN 14
#define SWITCH_PIN 12
#define SEN_IRQ_PIN 2

#ifdef __cplusplus
extern "C" {
#endif

static void gpio_irq_callback(uint gpio, uint32_t event_mask);

#ifdef __cplusplus
}
#endif

int ledstate = -1;
bool irqstate = false;

void gpio_irq_callback(uint gpio, uint32_t event_mask)
 {
     irqstate = (! irqstate);
     printf("irqstate -> %d\n", irqstate);
     gpio_put(SEN_IRQ_PIN, irqstate);
 }

#define PIO_LED

void setup_led()
{
#ifndef PIO_LED
    gpio_init(LED_PIN);
    gpio_set_function(LED_PIN, GPIO_FUNC_SIO);
    gpio_set_dir(LED_PIN, GPIO_OUT);
#else
    static const uint led_pin = 14;
    static const float pio_freq = 2000;

    // Choose PIO instance (0 or 1)
    PIO pio = pio0;

    // Get first free state machine in PIO 0
    uint sm = pio_claim_unused_sm(pio, true);

    // Add PIO program to PIO instruction memory. SDK will find location and
    // return with the memory offset of the program.
    uint offset = pio_add_program(pio, &blink_program);

    // Calculate the PIO clock divider
    float div = (float)clock_get_hz(clk_sys) / pio_freq;

    // Initialize the program using the helper function in our .pio file
    blink_program_init(pio, sm, offset, led_pin, div);

    // Start running our PIO program in the state machine
    pio_sm_set_enabled(pio, sm, true);
#endif
}

void setup_switch()
{
    gpio_init(SWITCH_PIN);
    gpio_set_function(SWITCH_PIN, GPIO_FUNC_SIO);
    gpio_set_dir(SWITCH_PIN, GPIO_IN);
    gpio_pull_up(SWITCH_PIN);

    gpio_init(SEN_IRQ_PIN);
    gpio_set_function(SEN_IRQ_PIN, GPIO_FUNC_SIO);
    gpio_set_dir(SEN_IRQ_PIN, GPIO_OUT);
    irqstate = false;
    gpio_put(SEN_IRQ_PIN, irqstate);

    uint32_t event_mask = GPIO_IRQ_EDGE_FALL /*| GPIO_IRQ_EDGE_RISE*/;
    gpio_set_irq_enabled_with_callback(SWITCH_PIN, event_mask, true, gpio_irq_callback);
}

int main()
{
    stdio_init_all();
    printf("start\n");

    setup_led();
    setup_slave();
    setup_switch();

    while (true)
    {
#ifndef PIO_LED
        gpio_put(LED_PIN, true);
        sleep_ms(1000);

        gpio_put(LED_PIN, false);
        sleep_ms(1000);
#endif

        //tight_loop_contents();
    }

    return 0;
}
