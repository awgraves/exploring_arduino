#include "lcd.h"
#include "Arduino.h"
#include <stdlib.h>

const int CMD_8BIT_MODE = 0x3;
const int CMD_4BIT_MODE = 0x2;

const int CMD_CLEAR = 0x01;
const int CMD_DISPLAY_ON = 0x0C;
const int _BLINK_CURSOR = 0x01;

const int CMD_SET_CURSOR = 0x80;

enum RegisterMode { COMMAND = LOW, CHAR = HIGH };

static void set_register_mode(LCD *lcd, RegisterMode rm);
static void write_nibble(LCD *lcd, int n);
static void write_byte(LCD *lcd, int n);

/* Public API */
void LCD_init(LCD *lcd) {
  // arduino setup
  pinMode(lcd->E, OUTPUT);
  pinMode(lcd->RS, OUTPUT);
  for (int i = 0; i < 4; i++)
    pinMode(lcd->data_pins[i], OUTPUT);

  // see
  // https://www.alldatasheet.com/datasheet-pdf/view/63673/HITACHI/HD44780.html
  // page 46, 4bit mode initialization sequence
  delay(50);
  set_register_mode(lcd, COMMAND);
  // init sequence
  // begin 8 bit mode
  write_nibble(lcd, CMD_8BIT_MODE);
  delay(5);
  write_nibble(lcd, CMD_8BIT_MODE);
  delay(1);
  write_nibble(lcd, CMD_8BIT_MODE);
  delay(1);
  // enter 4 bit mode
  write_nibble(lcd, CMD_4BIT_MODE);
  delay(1);

  write_byte(lcd, CMD_CLEAR);
  write_byte(lcd, CMD_DISPLAY_ON | (lcd->blink ? _BLINK_CURSOR : 0));
}

void LCD_print(LCD *lcd, char *s) {
  set_register_mode(lcd, CHAR);
  while (*s)
    write_byte(lcd, *(s++));
}
void LCD_print(LCD *lcd, int i) {
  set_register_mode(lcd, CHAR);
  char buf[10];
  itoa(i, buf, 10);
  LCD_print(lcd, buf);
}

void LCD_set_cursor(LCD *lcd, unsigned int row, unsigned int col) {
  set_register_mode(lcd, COMMAND);
  int addr = row < 1 ? 0x00 : 0x40; // max 2 rows
  addr += (col > 15 ? 15 : col);    // max 15 cols
  write_byte(lcd, CMD_SET_CURSOR | addr);
};

void LCD_clear(LCD *lcd) {
  set_register_mode(lcd, COMMAND);
  write_byte(lcd, CMD_CLEAR);
}

/* Low level */
static void set_register_mode(LCD *lcd, RegisterMode m) {
  digitalWrite(lcd->RS, m);
}

static void pulse(LCD *lcd) {
  digitalWrite(lcd->E, LOW);
  delay(1);
  digitalWrite(lcd->E, HIGH);
  delay(1);
  digitalWrite(lcd->E, LOW);
  delay(1);
}

// flushes right-most 4 bits of n
static void write_nibble(LCD *lcd, int n) {
  // set the data bit outputs
  for (int i = 0; i < 4; i++)
    digitalWrite(lcd->data_pins[i], ((n >> i) & 1));
  pulse(lcd);
}

static void write_byte(LCD *lcd, int b) {
  write_nibble(lcd, b >> 4);
  write_nibble(lcd, b);
}
