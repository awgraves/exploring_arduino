#include <Servo.h>

const int POT=0;
const int SERVO=9;

int val=0;
Servo myServo;

void setup() {
  pinMode(POT, INPUT);
  pinMode(SERVO, OUTPUT);
  myServo.attach(SERVO);
}

void loop() {
  val = analogRead(POT);
  val = map(val, 0, 1023, 179, 0); // reverse rotation direction to match pot
 
  myServo.write(val);
  delay(15);
}
