#include <stdio.h>
#include "pico/stdlib.h"
#include <stdbool.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define AUDIO_PIN 15
#define PWM_FREQUENCY 15000

uint32_t wrapVal = 0;

void audio_set_dutyCycle(uint16_t dutyCycle){
    uint16_t level = (uint16_t)(((float) dutyCycle / 100.0) * 1000);
    pwm_set_gpio_level(AUDIO_PIN, level);
}

void audio_play_frequency(uint16_t frequency, uint32_t length, uint8_t volume) {
    uint slice_num = pwm_gpio_to_slice_num(AUDIO_PIN);
    uint32_t half_period_us = 1000000 / (2 * frequency); // Half-period of square wave

    uint32_t start_time = to_ms_since_boot(get_absolute_time());

    while (to_ms_since_boot(get_absolute_time()) - start_time < length) {
        pwm_set_chan_level(slice_num, PWM_CHAN_A, wrapVal * (volume / 100));  // 50% duty cycle (ON)
        sleep_us(half_period_us);
        pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);  // 0% duty cycle (OFF)
        sleep_us(half_period_us);
    }

    pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);  // Stop sound
}

void init_pwm() {
    gpio_set_function(AUDIO_PIN, GPIO_FUNC_PWM);  // Set pin to PWM mode
    uint slice_num = pwm_gpio_to_slice_num(AUDIO_PIN); // Get PWM slice for this pin

    uint32_t sys_clk = clock_get_hz(clk_sys);  // Get system clock (default 125 MHz)
    float divider = 1.0f; // Clock divider
    uint32_t wrap_value = sys_clk / (PWM_FREQUENCY * divider); // Calculate wrap value
    wrapVal = wrap_value;

    // Configure PWM
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, divider); // No clock divider (1.0)
    pwm_config_set_wrap(&config, wrap_value); // Set wrap value

    pwm_init(slice_num, &config, true); // Initialize and start PWM

    pwm_set_chan_level(slice_num, PWM_CHAN_A, wrap_value / 2); // Set 50% duty cycle
}

void audio_init(){
    gpio_init(AUDIO_PIN);
    gpio_set_dir(AUDIO_PIN, GPIO_OUT);
    init_pwm();
}