// Replacing the LiquidCrystal librayr to write code from scratch
#include "lcd.h"

LCD lcd = {
  .RS = 2,
  .E = 3,
  .data_pins = {4, 5, 6, 7},
  .blink = false
};

int time = 0;

void setup() {
  LCD_init(&lcd);
  LCD_print(&lcd, "Andrew's lib!");
}

void loop() {
  LCD_set_cursor(&lcd, 1, 0); // 2nd row, first position
  LCD_print(&lcd, time);
  delay(1000);
  time++;
}
