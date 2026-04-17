// Replacing the LiquidCrystal to write code from scratch


const int RS=2; // Register select - LOW is COMMAND, HIGH is Char
const int E=3; // Enable

// Data lines
const int DB4=4;
const int DB5=5;
const int DB6=6;
const int DB7=7;

const int DB_ARRAY[] = {DB4, DB5, DB6, DB7};

enum RegisterMode { COMMAND = LOW, CHAR=HIGH };

void set_register_mode(RegisterMode m){
  digitalWrite(RS, m);
  delay(3);
}

void pulse(){
  digitalWrite(E, LOW);
  delay(1);
  digitalWrite(E, HIGH);
  delay(1);
  digitalWrite(E, LOW);
  delay(1);
}

// flushes right-most 4 bits of n
void flush_nibble(int n){
  // set the data bit outputs
  for (int i=0; i < 4; i++)
    digitalWrite(DB_ARRAY[i], ((n >> i) & 1));
  pulse();
}

void flush_byte(int b){
  flush_nibble(b >> 4);
  flush_nibble(b);
}

void init_lcd(){
  // see https://www.alldatasheet.com/datasheet-pdf/view/63673/HITACHI/HD44780.html
  // page 46, 4bit mode initialization sequence
  delay(50);
  set_register_mode(COMMAND);
  // init sequence
  // begin 8 bit mode
  flush_nibble(B0011);
  delay(5);
  flush_nibble(B0011);
  delay(1);
  flush_nibble(B0011);
  delay(1);
  // enter 4 bit mode
  flush_nibble(B0010);
  delay(1);
}

void setup() {
  pinMode(RS, OUTPUT);
  pinMode(E, OUTPUT);
  for(int i=0; i<4; i++)
    pinMode(DB_ARRAY[i], OUTPUT);
  
  init_lcd();

  // clear display
  flush_byte(B00000001);

  // display on
  flush_byte(B00001101);

  set_register_mode(CHAR);

  // write A
  flush_byte(B01000001);

  // write B
  flush_byte(B01000010);

  // write C
  flush_byte(B01000011);

  // write 1
  flush_byte(B00110001);

  // write 2
  flush_byte(B00110010);

  // write 3
  flush_byte(B00110011);
}

void loop() {
}
