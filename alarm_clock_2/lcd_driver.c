#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdbool.h>

#include "ext_led_driver.h"

//defines for necessary addresses
#define I2C_PORT i2c0
#define SDA 4
#define SCL 5
#define LCD_ADDR 0x27 

//remembers the field and row of the cursor on the display
uint8_t field = 0;
uint8_t row = 0;

//lcd backlight status (on/off)
bool backlight = true;

//sends a byte via i2c to the display
void lcd_send_byte(uint8_t val, bool is_data) {
    uint8_t backlight_bit = backlight? 0x08 : 0x00;
    uint8_t high_nibble = (val & 0xF0) | (is_data ? 0x01 : 0x00) | backlight_bit;
    uint8_t low_nibble = ((val << 4) & 0xF0) | (is_data ? 0x01 : 0x00) | backlight_bit;
    
    uint8_t enable_high = high_nibble | 0x04;  // Set Enable bit (E=1)
    uint8_t enable_low = high_nibble & ~0x04;  // Clear Enable bit (E=0)

    i2c_write_blocking(I2C_PORT, LCD_ADDR, &enable_high, 1, false);
    sleep_us(50);
    i2c_write_blocking(I2C_PORT, LCD_ADDR, &enable_low, 1, false);
    sleep_us(50);

    enable_high = low_nibble | 0x04;  // Set Enable bit (E=1)
    enable_low = low_nibble & ~0x04;  // Clear Enable bit (E=0)

    i2c_write_blocking(I2C_PORT, LCD_ADDR, &enable_high, 1, false);
    sleep_us(50);
    i2c_write_blocking(I2C_PORT, LCD_ADDR, &enable_low, 1, false);
    sleep_us(50);
}

//initialises the i2c by manipulating the necessary pins
void lcd_i2c_init(){
    i2c_init(I2C_PORT, 100 * 1000);

    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);

    gpio_pull_up(SDA);
    gpio_pull_up(SCL);
}

//initialises the lcd
void lcd_init(){
    //first initialises the i2c
    lcd_i2c_init();

    sleep_ms(2000); // Wait for LCD power-up
    lcd_send_byte(0x03, false);
    sleep_ms(5);
    lcd_send_byte(0x03, false);
    sleep_us(100);
    lcd_send_byte(0x03, false);
    lcd_send_byte(0x02, false); // Set to 4-bit mode

    // Function Set: 2-line, 5x8 dots
    lcd_send_byte(0x28, false);
    // Display ON, Cursor OFF, Blink OFF
    lcd_send_byte(0x0C, false);
    // Clear Display
    lcd_send_byte(0x01, false);
    sleep_ms(2);
    // Disable Auto Cursor
    lcd_send_byte(0x04, false);
}

//sets cursor on the lcd screen
void lcd_setCursor(uint8_t col, uint8_t rw) {
    uint8_t row_offsets[] = {0x00, 0x40};  // Memory offsets for line 1 & 2
    lcd_send_byte(0x80 | (col + row_offsets[rw]), false);

    //update global position
    field = col;
    row = rw;
}

//clears the display and returns the cursor to 0,0
void lcd_clear(){
    lcd_send_byte(0x01, false);
    lcd_setCursor(0, 0);
}

//puts a char on the cursor spot, then moves the cursor
void lcd_writeChar(char c){
    if(field == 0 && row == 0) lcd_clear();

    lcd_send_byte(c, true); //writes onto the lcd

    //updates cursor
    field++;
    if(field == 16){
        field = 0;
        if(row == 0) row++;
        else row--;
    }
    lcd_setCursor(field, row);
}

//writes an entire string to the display
void lcd_writeStr(const char *str){
    while(*str){
        lcd_writeChar(*str++);
    }
}

//writes an Ascii character to the display based on the numerical value given
void lcd_writeAscii(uint8_t val){
    lcd_writeChar((char) val);
}

//writes a number to the display
void lcd_writeInt(uint32_t n){
    char str[10];
    sprintf(str, "%d", n);
    lcd_writeStr(str);
}

//changes cursor to line 1
void lcd_line1(){
    lcd_setCursor(0, 0);
}

//changes cursor to line 2
void lcd_line2(){
    lcd_setCursor(0, 1);
}

//returns the cursor position as a value between 0 and 31 
//(values >= 16 indicate second row)
uint8_t lcd_getCursor(){
    return field + row * 16;
}

//turns backlight on/off
void lcd_setBacklight(bool state){
    backlight = state;
}