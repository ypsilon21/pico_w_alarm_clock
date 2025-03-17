#include <stdio.h>
#include "pico/stdlib.h"
#include <stdbool.h>

void buttons_init(){
    for(uint8_t i = 0; i < 4; i++){
        gpio_init(i);
        gpio_set_dir(i, GPIO_IN);
        gpio_pull_up(i);
    }
}

bool buttons_getButtonVal(uint8_t val){
    if(val >= 4) return false;
    return !gpio_get(val);
}

uint8_t buttons_getValues(){
    uint8_t res = (uint8_t) buttons_getButtonVal(3);
    res += (uint8_t) buttons_getButtonVal(2) << 1;
    res += (uint8_t) buttons_getButtonVal(1) << 2;
    res += (uint8_t) buttons_getButtonVal(0) << 3;

    return res;
}

void buttons_waitForInput(){
    while(buttons_getValues() == 0){};
}

void buttons_waitForNoInput(){
    while(buttons_getValues() != 0){};
}