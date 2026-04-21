const int RED=9;
const int GREEN=10;
const int BLUE=11;

const int BUTTON=2;

const int LEDS[] = {RED, BLUE, GREEN};

volatile int selectedLED=0;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  pinMode(BUTTON, INPUT);

  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  attachInterrupt(digitalPinToInterrupt(BUTTON), swap, FALLING);
}

void swap() {
  // turn off current LED
  digitalWrite(LEDS[selectedLED], LOW);
  // loop through options
  selectedLED = (selectedLED + 1) % 3;
}


void loop() {
  for (int i=0; i < 255; i++){
    analogWrite(LEDS[selectedLED], i);
    delay(10);
  }
  for(int i=255; i >= 0; i--){
    analogWrite(LEDS[selectedLED], i);
    delay(10);
  }
  delay(1000);
}
