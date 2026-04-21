#include "lcd_i2c.h"

const int POT=0;

LCD lcd = { .blink=false};
int val, prev;

void setup() {
  LCD_init(&lcd);
  LCD_print(&lcd, "LCD over I2C!");

  // create progress bar bitmaps
  unsigned int bitmap[8];
  for(int i=0; i<5; i++){
    for(int j=0; j<8; j++){
      bitmap[j] = B11111 & (B11111 << (4-i));
    }
    LCD_create_char(&lcd, i, bitmap);
  }

  pinMode(POT, INPUT);
  prev = -1; // force first render
}


void print_status(int n){ 
  // print number 0-100
  LCD_set_cursor(&lcd, 1, 0); // 2nd row, first position
  LCD_print(&lcd, "   "); // clear out 3 digits
  LCD_set_cursor(&lcd, 1, 0); // 2nd row, first position
  LCD_print(&lcd, val);
  // print the bar
  // always start at 4th column
  LCD_set_cursor(&lcd, 1, 3);
  // 16 cols - 3 = 13 x 5 = 65 total vertical slices
  int j = map(n, 0, 100, 0, 65);
  int col = 0;
  while (j >= 5){
    LCD_write_char(&lcd, 4);
    j -= 5;
    col++;
  }
  if (j > 0){
    LCD_write_char(&lcd, j-1); // the remained will be a partial block
    col++;
  }

  // remaining space
  while(col <= 12){
    LCD_print(&lcd, " ");
    col++;
  }
}

void loop() {
  val = analogRead(POT);
  val = map(val, 0, 1022, 0, 100); // give little wiggle room at top for stability

  if (val != prev){
    print_status(val);
  }
  prev = val;

  delay(50);
}
