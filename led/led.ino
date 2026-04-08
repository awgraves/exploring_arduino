const int LED=9;

void setup() {
  pinMode(LED, OUTPUT);
}

// intervals
//void loop() {
//  for (int i=100; i<=1000; i+=100){
//    digitalWrite(LED, HIGH);
//    delay(i);
//    digitalWrite(LED, LOW);
//    delay(i);
//  }
//}

void loop() {
  for (int i=0; i<256; i++){
    analogWrite(LED, i);
    delay(10);
  }
  for (int i=255; i>=0; i--){
    analogWrite(LED, i);
    delay(10);
  }
}
