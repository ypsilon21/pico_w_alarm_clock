#ifndef LCD_DRIVER_DRIVER_H
#define LCD_DRIVER_DRIVER_H

//FUNCTIONS:

//to initialise the lcd + the i2c
void lcd_init();

//to write Strings, Chars or Ascii Characters (by Ascii value)
void lcd_writeStr(const char *str);
void lcd_writeChar(char c);
void lcd_writeAscii(uint8_t val);

//sets and gets cursor
void lcd_setCursor(uint8_t col, uint8_t rw);
uint8_t lcd_getCursor();

//changes lines
void lcd_line1();
void lcd_line2();

//clears display
void lcd_clear();

//turns backlight on/off
void lcd_setBacklight(bool state);

#endif