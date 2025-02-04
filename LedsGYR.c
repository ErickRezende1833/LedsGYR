#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"

#define LED_RED_PIN 13
#define LED_YELLOW_PIN 12
#define LED_GREEN_PIN 11

typedef enum {
    RED,
    YELLOW,
    GREEN
} LEDstate;

LEDstate currentState = RED;

bool repeating_timer_callback(struct repeating_timer *t) {

    gpio_put(LED_RED_PIN, 0);
    gpio_put(LED_YELLOW_PIN, 0);
    gpio_put(LED_GREEN_PIN, 0);

    switch (currentState) {
        case RED:
            currentState = YELLOW;
            break;
        case YELLOW:
            currentState = GREEN;
            break;
        case GREEN:
            currentState = RED;
            break;
    }

    return true;
}

int main() {

    stdio_init_all();

    gpio_init(LED_RED_PIN);
    gpio_init(LED_YELLOW_PIN);
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_YELLOW_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

    gpio_put(LED_RED_PIN, 1);

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
    
        printf("Estado atual do semáforo: ");
        switch (currentState) {
            case RED:
                printf("Vermelho\n");
                gpio_put(LED_RED_PIN, 1);
                gpio_put(LED_YELLOW_PIN, 0);
                gpio_put(LED_GREEN_PIN, 0);
                break;
            case YELLOW:
                printf("Amarelo\n");
                gpio_put(LED_RED_PIN, 0);
                gpio_put(LED_YELLOW_PIN, 1);
                gpio_put(LED_GREEN_PIN, 0);
                break;
            case GREEN:
                printf("Verde\n");
                gpio_put(LED_RED_PIN, 0);
                gpio_put(LED_YELLOW_PIN, 0);
                gpio_put(LED_GREEN_PIN, 1);
                break;
        }
        sleep_ms(100);
    }

    return 0;
}