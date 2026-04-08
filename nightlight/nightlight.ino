const int LED=9;
const int LIGHT=0;

const int MIN_LIGHT=489;
const int MAX_LIGHT=765;

int val = 0;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  val = analogRead(LIGHT);
  val = map(val, MIN_LIGHT, MAX_LIGHT, 255, 0);
  val = constrain(val, 0, 255);
  analogWrite(LED, val);
}
