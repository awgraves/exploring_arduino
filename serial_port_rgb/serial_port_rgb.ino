const int RED=9;
const int GREEN=10;
const int BLUE=11;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);  // serial timeout to wait for int

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // start with LED on white
  digitalWrite(RED, 255);
  digitalWrite(GREEN, 255);
  digitalWrite(BLUE, 255);
}

int raw[3] = {0, 0, 0};

// final 8 bit color vals
int rgb[3] = {255, 255, 255};

void loop() {

  if (Serial.available() > 0){
    // expect 3 numbers sep by non int chars
    // Serial.parseInt will skip non int chars until it finds a complete int
    for(int i =0; i<3; i++)
      raw[i] = Serial.parseInt();

    // discard anything else leftover in buffer
    while(Serial.available())
    {
      Serial.read();
    }

    for(int i=0; i<3; i++)
      rgb[i] = constrain(raw[i], 0, 255); // use pure rgb vals rather than percentage 0-100

    analogWrite(RED, rgb[0]);
    analogWrite(GREEN, rgb[1]);
    analogWrite(BLUE, rgb[2]);

    Serial.println("RED:\t" + String(rgb[0]));
    Serial.println("GREEN:\t" + String(rgb[1]));
    Serial.println("BLUE:\t" + String(rgb[2]) + "\n");
  }
}
