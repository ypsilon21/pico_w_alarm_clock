#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H

void buttons_init();
uint8_t buttons_getValues();
bool buttons_getButtonVal(uint8_t val);
void buttons_waitForInput();
void buttons_waitForNoInput();

#endif