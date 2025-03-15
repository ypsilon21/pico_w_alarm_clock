#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "ext_led_driver.h"
#include "button_driver.h"
#include "lcd_driver.h"
#include "audio_driver.h"

int main()
{
    stdio_init_all();

    // Initialise the Wi-Fi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    // Example to turn on the Pico W LED
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    lcd_init();
    lcd_writeStr("hallo :3");

    led_init();
    audio_init();

    float dutyCycle = 10;
    pwm_pulse(dutyCycle);

    buttons_init();
    while(1){
        buttons_waitForInput();
        for(uint8_t i = 0; i < 4; i++){
            if(buttons_getButtonVal(i)){
                lcd_clear();
                if(i == 0) dutyCycle -= 10.0f;
                else if(i == 1) dutyCycle += 10.0f;
                pwm_pulse(dutyCycle);
                //led_blink(140, i + 1);
                buttons_waitForNoInput();
                lcd_clear();
            }
        }
    }
}
