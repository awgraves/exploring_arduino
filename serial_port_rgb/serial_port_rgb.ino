const int RED=9;
const int GREEN=10;
const int BLUE=11;

// final 8 bit color vals
typedef union {
  struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
  };
  uint8_t channel[3];
} RGB_T;

RGB_T rgb = {255, 0, 0};
int raw = 0;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);  // serial timeout to wait for int (affects parseInt func)

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // start with LED on white
  digitalWrite(RED, rgb.red);
  digitalWrite(GREEN, rgb.green);
  digitalWrite(BLUE, rgb.blue);
}

void loop() {
  if (Serial.available() > 0){
    // expect 3 numbers sep by non int chars
    // Serial.parseInt will skip non int chars until it finds a complete int
    for(int i=0; i<3; i++){
      raw = Serial.parseInt(); // this needs to be separate assignment, breaks otherwise?
      rgb.channel[i] = (uint8_t) constrain(raw, 0, 255);
    }

    // discard anything else leftover in buffer
    while(Serial.available())
    {
      Serial.read();
    }

    analogWrite(RED, rgb.red);
    analogWrite(GREEN, rgb.green);
    analogWrite(BLUE, rgb.blue);

    Serial.println("RED:\t" + String(rgb.red));
    Serial.println("GREEN:\t" + String(rgb.green));
    Serial.println("BLUE:\t" + String(rgb.blue) + "\n");
  }
}
