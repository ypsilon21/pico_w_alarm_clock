#include <stdio.h>
#include "pico/stdlib.h"
#include <stdbool.h>
#include "hardware/pwm.h"

#include "ext_led_driver.h"

#define AUDIO_PIN 15

void audio_init(){
    gpio_init(AUDIO_PIN);
    gpio_set_dir(AUDIO_PIN, GPIO_OUT);
}

void pwm_pulse(float duty_cycle){
    // Get the PWM slice number for this GPIO
    uint slice_num = pwm_gpio_to_slice_num(AUDIO_PIN);

    // Set the GPIO to PWM function
    gpio_set_function(AUDIO_PIN, GPIO_FUNC_PWM);

    // Set the PWM frequency (Example: 1 kHz)
    pwm_set_clkdiv(slice_num, 125.0f); // Clock divider
    pwm_set_wrap(slice_num, 1000); // 1000 ticks per cycle

    // Set duty cycle
    uint16_t level = (uint16_t)((duty_cycle / 100.0) * 1000);
    pwm_set_gpio_level(AUDIO_PIN, level);

    // Enable PWM
    pwm_set_enabled(slice_num, true);
}