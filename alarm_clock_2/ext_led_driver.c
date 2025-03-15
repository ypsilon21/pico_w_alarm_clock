#include <stdio.h>
#include "pico/stdlib.h"
#include <stdbool.h>

#define EXT_LED_PIN 15

bool status = false;

int led_init(){
    gpio_init(EXT_LED_PIN);
    gpio_set_dir(EXT_LED_PIN, GPIO_OUT);
    return EXT_LED_PIN;
}

void led_set(bool val){
    gpio_put(EXT_LED_PIN, val);
    status = val;
}

void led_toggle(){
    led_set(!status);
}

void led_blink(uint16_t delay, uint8_t amount){
    led_set(false);
    for(uint8_t i = 0; i < amount * 2; i++){
        led_toggle();
        sleep_ms(delay);
    }
}
