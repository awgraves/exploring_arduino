const int POT=0;
int val = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(POT);
  Serial.println(val);
  delay(500);
}
