#include <stdio.h>
#include "pico/stdlib.h"
#include <stdbool.h>
#include "hardware/pwm.h"

#define AUDIO_PIN 15


void audio_set_dutyCycle(uint16_t dutyCycle){
    uint16_t level = (uint16_t)(((float) dutyCycle / 100.0) * 1000);
    pwm_set_gpio_level(AUDIO_PIN, level);
}

void audio_set_frequency(uint16_t frequency){
    // Get the PWM slice number for this GPIO
    uint slice_num = pwm_gpio_to_slice_num(AUDIO_PIN);
    //set frequency in Hz
    uint32_t wrap = (125000000 / (125.0f * frequency)) - 1;
    pwm_set_wrap(slice_num, wrap);
}

void init_pwm(float dutyCycle){
    // Get the PWM slice number for this GPIO
    uint slice_num = pwm_gpio_to_slice_num(AUDIO_PIN);

    // Set the GPIO to PWM function
    gpio_set_function(AUDIO_PIN, GPIO_FUNC_PWM);

    // Set the PWM frequency (Example: 440 Hz)
    pwm_set_clkdiv(slice_num, 125.0f); // Clock divider
    audio_set_frequency(440);

    // Set duty cycle to 0% to start
    audio_set_dutyCycle(0);

    // Enable PWM
    pwm_set_enabled(slice_num, true);
}

void audio_init(){
    gpio_init(AUDIO_PIN);
    gpio_set_dir(AUDIO_PIN, GPIO_OUT);
    init_pwm(0.0f);
}