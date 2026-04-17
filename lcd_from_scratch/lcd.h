#ifndef LCD_H
#define LCD_H

typedef struct {
  int RS;           // register select pin num
  int E;            // enable pin num
  int data_pins[4]; // 4 bit mode, must list in LSB order
  bool blink;       // whether to blink the cursor
} LCD;

void LCD_init(LCD *lcd);
void LCD_clear(LCD *lcd);

void LCD_print(LCD *lcd, char *s);
void LCD_print(LCD *lcd, int i);

void LCD_set_cursor(LCD *lcd, unsigned int row, unsigned int col);
#endif
