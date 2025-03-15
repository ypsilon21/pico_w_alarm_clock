#include <stdio.h>
#include "pico/stdlib.h"
#include <stdbool.h>
#include "hardware/pwm.h"

#include "ext_led_driver.h"

#define AUDIO_PIN 15

void init_pwm(float dutyCycle){
    // Get the PWM slice number for this GPIO
    uint slice_num = pwm_gpio_to_slice_num(AUDIO_PIN);

    // Set the GPIO to PWM function
    gpio_set_function(AUDIO_PIN, GPIO_FUNC_PWM);

    // Set the PWM frequency (Example: 1 kHz)
    pwm_set_clkdiv(slice_num, 125.0f); // Clock divider
    pwm_set_wrap(slice_num, 1000); // 1000 ticks per cycle

    // Set duty cycle to 0% to start
    audio_set_dutyCycle(0.0f);

    // Enable PWM
    pwm_set_enabled(slice_num, true);
}

void audio_init(){
    gpio_init(AUDIO_PIN);
    gpio_set_dir(AUDIO_PIN, GPIO_OUT);
    init_pwm(0.0f);
}

void audio_set_dutyCycle(uint16_t dutyCycle){
    uint16_t level = (uint16_t)(((float) dutyCycle / 100.0) * 1000);
    pwm_set_gpio_level(AUDIO_PIN, level);
}

void audio_set_frequency(uint16_t frequency){
    // Get the PWM slice number for this GPIO
    uint slice_num = pwm_gpio_to_slice_num(AUDIO_PIN);
    //set frequency in Hz
    pwm_set_wrap(slice_num, frequency);
}