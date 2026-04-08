#define MODE_COUNT (sizeof(modes) / sizeof(RGB))

const int RLED=9;
const int GLED=10;
const int BLED=11;
const int BUTTON=2;

typedef struct RGB {
  int r;
  int b;
  int g;
} RBG;

const RBG modes[] = {
  {0, 0, 0}, // OFF
  {255, 0, 0}, // red
  {0, 255, 0}, // green
  {0, 0, 255}, // blue
  {127, 255, 127}, // purple
  {255, 127, 127}, // teal
  {127, 127, 255}, // orange
  {127, 127, 127}, // white
};

boolean lastButton = LOW;
boolean currentButton = LOW;
int ledMode = 0;

void setup() {
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

boolean debounce(boolean last){
  boolean current = digitalRead(BUTTON);
  if (last != current){
    delay(50);
    current - digitalRead(BUTTON);
  }
  return current;
}

void cycleLedMode(){
  ledMode = ++ledMode < MODE_COUNT ? ledMode : 0;
}

void loop() {
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH){
    cycleLedMode();
  }
  lastButton = currentButton;

  RGB val = modes[ledMode];
  analogWrite(RLED, val.r);
  analogWrite(GLED, val.g);
  analogWrite(BLED, val.b);
}
