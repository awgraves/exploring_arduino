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

// turn ON light at position i
// set all others OFF
void lightPosition(int i){
  digitalWrite(LATCH, LOW);
  for (int j=7; j >= 0; j--){
    digitalWrite(SER, (j == i));
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
  digitalWrite(LATCH, HIGH);
}

int val = 0, prev = 0;

void loop() {
  // map the potentiometer read to a bit position
  val = map(analogRead(POT), 0, 1023, 7, 0);

  if (val != prev){
    lightPosition(val);
    prev = val;
  }
  delay(50);
}
