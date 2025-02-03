#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define LED_RED_PIN 13
#define LED_YELLOW_PIN 12
#define LED_GREEN_PIN 11


int main() {
    
    stdio_init_all();

    
    gpio_init(LED_RED_PIN);
    gpio_init(LED_YELLOW_PIN);
    gpio_init(LED_GREEN_PIN);

    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_YELLOW_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

    while (true) {
        gpio_put(LED_RED_PIN, 1);
        gpio_put(LED_YELLOW_PIN, 0);
        gpio_put(LED_GREEN_PIN, 0);
        sleep_ms(3000);
        gpio_put(LED_RED_PIN, 0);
        gpio_put(LED_YELLOW_PIN, 1);
        gpio_put(LED_GREEN_PIN, 0);
        sleep_ms(3000);
        gpio_put(LED_RED_PIN, 0);
        gpio_put(LED_YELLOW_PIN, 0);
        gpio_put(LED_GREEN_PIN, 1);
        sleep_ms(3000);
        
    }

    return 0;
}
