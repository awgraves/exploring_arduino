// Replacing the LiquidCrystal librayr to write code from scratch
#include "lcd.h"

LCD lcd = {
  .RS = 2,
  .E = 3,
  .data_pins = {4, 5, 6, 7},
  .blink = false
};

void setup() {
  LCD_init(&lcd);
  LCD_print(&lcd, "Andrew's lib!");

  // create progress bar bitmaps
  unsigned int bitmap[8];
  for(int i=0; i<5; i++){
    for(int j=0; j<8; j++){
      bitmap[j] = B11111 & (B11111 << (4-i));
    }
    LCD_create_char(&lcd, i, bitmap);
  }
}

void loop() {
  LCD_set_cursor(&lcd, 1, 0); // 2nd row, first position
  LCD_print(&lcd, "                "); // clear progress with spaces

  for(int i=0; i<16; i++){
    for (int j=0; j<5; j++){
      LCD_set_cursor(&lcd, 1, i);
      LCD_write_char(&lcd, j);
      delay(100);
    }
  }
}
