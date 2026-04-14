const int SER = 8;
const int LATCH = 9;
const int CLK = 10;

void setup() {
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
}

void shift(int i){
  digitalWrite(LATCH, LOW);
  shiftOut(SER, CLK, MSBFIRST, i);
  digitalWrite(LATCH, HIGH);
}

void loop() {
  shift(B10101010);
  delay(500);
  shift(B01010101);
  delay(500);
}
