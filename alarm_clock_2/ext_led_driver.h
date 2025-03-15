#ifndef EXT_LED_DRIVER_H
#define EXT_LED_DRIVER_H

#include <stdbool.h>

int led_init();
void led_toggle();
void led_set(bool val);
void led_blink(uint16_t delay, uint8_t amount);

#endif