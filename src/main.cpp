#include <stdio.h>
#include "pico/stdlib.h"

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

void setup_led()
{
    gpio_init(LED_PIN);
    gpio_set_function(LED_PIN, GPIO_FUNC_SIO);
    gpio_set_dir(LED_PIN, GPIO_OUT);
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
        gpio_put(LED_PIN, true);
        sleep_ms(1000);

        gpio_put(LED_PIN, false);
        sleep_ms(1000);

        //tight_loop_contents();
    }

    return 0;
}
