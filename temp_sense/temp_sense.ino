
const int RLED=9;
const int GLED=10;
const int BLED=11;
const int TEMP=0;

const int LOWER_BOUND=157;
const int UPPER_BOUND=159;

int val = 0;

void setup() {
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  pinMode(TEMP, INPUT);
}

void loop() {
  val = analogRead(TEMP);

  if (val < LOWER_BOUND){
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, HIGH);
  } else if (val > UPPER_BOUND){
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
  } else {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, LOW);
  }
}
