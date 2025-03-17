#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "ext_led_driver.h"
#include "button_driver.h"
#include "lcd_driver.h"
#include "audio_driver.h"
#include "music_module.h"

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

    music_setVolume(50);
    music_setTempo(130);

    while(1){
        music_playNote(C3, QUA);
        music_playNote(D3, QUA);
        music_playNote(E3, QUA);
        music_playNote(F3, QUA);
        music_playNote(G3, HAL);
        music_playNote(G3, HAL);
        for(uint8_t i = 0; i < 2; i++){
            music_playNote(A3, QUA);
            music_playNote(A3, QUA);
            music_playNote(A3, QUA);
            music_playNote(A3, QUA);
            music_playNote(G3, HAL_);
        }
        music_playNote(F3, QUA);
        music_playNote(F3, QUA);
        music_playNote(F3, QUA);
        music_playNote(F3, QUA);
        music_playNote(E3, HAL);
        music_playNote(E3, HAL);
        music_playNote(G3, QUA);
        music_playNote(G3, QUA);
        music_playNote(G3, QUA);
        music_playNote(G3, QUA);
        music_playNote(C3, HAL);

        music_playNote(BREAK, WHL);
    }

    buttons_init();
    while(1){
        buttons_waitForInput();
        for(uint8_t i = 0; i < 4; i++){
            if(buttons_getButtonVal(i)){
                lcd_clear();
                lcd_writeChar('0' + (char) i);
                //led_blink(140, i + 1);
                buttons_waitForNoInput();
                lcd_clear();
            }
        }
    }
}
