#include <stdio.h>
#include "pico/stdlib.h"

void setup_slave();

#define LED_PIN 14

void setup_led()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

int main()
{
    stdio_init_all();
    printf("start\n");

    setup_led();
    setup_slave();

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
