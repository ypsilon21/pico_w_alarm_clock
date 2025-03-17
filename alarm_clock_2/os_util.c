#include <stdio.h>
#include "pico/stdlib.h"

#include "lcd_driver.h"
#include "button_driver.h"

#define ENTER_BUTTON 0

void wait_for_confirm(){
    while (!buttons_getButtonVal(ENTER_BUTTON));
    buttons_waitForNoInput();
    lcd_clear();
}

void put_error(char* errorMessage){
    lcd_clear();
    lcd_writeStr("[!] ");
    lcd_writeStr(errorMessage);
    wait_for_confirm();
}

void put_logStr(char* logMessage){
    lcd_clear();
    lcd_writeStr("[log] ");
    lcd_writeStr(logMessage);
    wait_for_confirm();
}

void put_logInt(uint32_t logMessage){
    lcd_clear();
    lcd_writeStr("[log] ");
    lcd_writeInt(logMessage);
    wait_for_confirm();
}