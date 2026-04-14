const int SER = 8;
const int LATCH = 9;
const int CLK = 10;

const int POT = 0;

void setup() {
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);

  pinMode(POT, INPUT);
}

void shift(int i){
  digitalWrite(LATCH, LOW);
  shiftOut(SER, CLK, MSBFIRST, i);
  digitalWrite(LATCH, HIGH);
}

int readPause(){
  return map(analogRead(POT), 0, 1023, 150, 25);
}

int i = 0;
void loop() {
  while (i < 7){
    shift(1 << i++);
    delay(readPause());
  }
  while (i > 0){
    shift(1 << i--);
    delay(readPause());
  }
}
