#include "lcd_i2c.h"

const int POT=0;
const int BUTTON=9;

LCD lcd;
int pot_val, pot_prev; // potentiometer
int button_val, button_prev; // backlight toggle btn

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
  pinMode(BUTTON, INPUT);

  pot_prev = -1; // force first render
}


void print_status(int n){ 
  // print number 0-100
  LCD_set_cursor(&lcd, 1, 0); // 2nd row, first position
  LCD_print(&lcd, "   "); // clear out 3 digits
  LCD_set_cursor(&lcd, 1, 0); // 2nd row, first position
  LCD_print(&lcd, pot_val);
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

bool debounce(){
  int val = digitalRead(BUTTON);
  if (val != button_prev){
    delay(5);
    val = digitalRead(BUTTON);
  }
  return val;
}

void loop() {
  pot_val = analogRead(POT);
  pot_val = map(pot_val, 0, 1022, 0, 100); // give little wiggle room at top for stability

  if (pot_val != pot_prev){
    print_status(pot_val);
  }
  pot_prev = pot_val;

  button_val = debounce();
  if (button_val && !button_prev){
    LCD_toggle_display(&lcd);
  }
  button_prev = button_val;

  delay(50);
}
