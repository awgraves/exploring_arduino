#ifndef LCD_I2C_H
#define LCD_I2C_H

#include <Wire.h>

// arduino uses pinA4 (SDA) and pinA5(SDC)
// where are multiplexed to a I2C hardware interface
typedef struct {
  bool blink; // whether to blink the cursor
} LCD;

void LCD_init(LCD *lcd);
void LCD_clear(LCD *lcd);

void LCD_print(LCD *lcd, char *s);
void LCD_print(LCD *lcd, int i);

void LCD_write_char(LCD *lcd, unsigned int c);
void LCD_create_char(LCD *lcd, unsigned int addr, unsigned int byte_array[8]);

void LCD_set_cursor(LCD *lcd, unsigned int row, unsigned int col);
#endif
