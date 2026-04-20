#include "lcd_i2c.h"
#include "Arduino.h"
#include <stdlib.h>

const int ADDR = 0x27;

// note that the i2c module uses highest 4 bits as data lines
// and lowest 4 bits for RS, E, EN, and a backlight control
const int RS = 0x01;
const int EN = 0x04;
const int BACKLIGHT = 0x08;

const int CMD_8BIT_MODE = 0x3;
const int CMD_4BIT_MODE = 0x2;

const int CMD_CLEAR = 0x01;
const int CMD_DISPLAY_ON = 0x0C;
const int _BLINK_CURSOR = 0x01;

const int CMD_SET_CGRAM_ADDR = 0x40;

const int CMD_SET_CURSOR = 0x80;

enum RegisterMode { COMMAND = LOW, CHAR = HIGH };

static void write_nibble(LCD *lcd, int n, RegisterMode m);
static void write_byte(LCD *lcd, int n, RegisterMode m);

/* Public API */
void LCD_init(LCD *lcd) {
  // arduino setup - the Wire lib already handles SDA and SDC setup
  Wire.begin();

  // see
  // https://www.alldatasheet.com/datasheet-pdf/view/63673/HITACHI/HD44780.html
  // page 46, 4bit mode initialization sequence
  delay(50);
  // init sequence
  // begin 8 bit mode
  write_nibble(lcd, CMD_8BIT_MODE, COMMAND);
  delay(5);
  write_nibble(lcd, CMD_8BIT_MODE, COMMAND);
  delay(1);
  write_nibble(lcd, CMD_8BIT_MODE, COMMAND);
  delay(1);
  // enter 4 bit mode
  write_nibble(lcd, CMD_4BIT_MODE, COMMAND);
  delay(1);

  write_byte(lcd, CMD_CLEAR, COMMAND);
  write_byte(lcd, CMD_DISPLAY_ON | (lcd->blink ? _BLINK_CURSOR : 0), COMMAND);
}

void LCD_print(LCD *lcd, char *s) {
  while (*s)
    write_byte(lcd, *(s++), CHAR);
}
void LCD_print(LCD *lcd, int i) {
  char buf[10];
  itoa(i, buf, 10);
  LCD_print(lcd, buf);
}

void LCD_set_cursor(LCD *lcd, unsigned int row, unsigned int col) {
  int addr = row < 1 ? 0x00 : 0x40; // max 2 rows
  addr += (col > 15 ? 15 : col);    // max 15 cols
  write_byte(lcd, CMD_SET_CURSOR | addr, COMMAND);
};

void LCD_clear(LCD *lcd) { write_byte(lcd, CMD_CLEAR, COMMAND); }

void LCD_create_char(LCD *lcd, unsigned int addr, unsigned int byte_array[8]) {
  addr &= 0x7; // can only be 0-7, mask off additional bits

  // left shift addr by 3 because each custom char takes up 8 bytes
  write_byte(lcd, CMD_SET_CGRAM_ADDR | (addr << 3), COMMAND);

  for (int i = 0; i < 8; i++) {
    write_byte(lcd, byte_array[i], CHAR);
  }
}
void LCD_write_char(LCD *lcd, unsigned int c) { write_byte(lcd, c, CHAR); }

/* Low level */
static void iicwrite(int data) {
  Wire.beginTransmission(ADDR);
  Wire.write(data);
  Wire.endTransmission();
}

static void pulse(LCD *lcd, int data, RegisterMode m) {
  // data goes in highest 4 bits, controls are in lower 4
  int REG = m ? RS : 0;
  iicwrite(data | REG | BACKLIGHT);
  iicwrite(data | EN | REG | BACKLIGHT);
  delayMicroseconds(1);
  iicwrite(data | REG | BACKLIGHT);
  delayMicroseconds(50);
}

// flushes right-most 4 bits of n
static void write_nibble(LCD *lcd, int n, RegisterMode m) {
  // shift those bottom 4 bits upwards into the 'data' bits for the wire
  pulse(lcd, n << 4, m);
}

static void write_byte(LCD *lcd, int b, RegisterMode m) {
  write_nibble(lcd, b >> 4, m);
  write_nibble(lcd, b, m);
}
