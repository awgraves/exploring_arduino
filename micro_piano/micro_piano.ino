#include "pitches.h"

const int SPEAKER=9;

// color coded push buttons
const int RED=2;
const int ORANGE=3;
const int YELLOW=4;
const int GREEN=5;
const int BLUE=6;

void setup() {
  pinMode(SPEAKER, OUTPUT);
  pinMode(RED, INPUT);
  pinMode(ORANGE, INPUT);
  pinMode(YELLOW, INPUT);
  pinMode(GREEN, INPUT);
  pinMode(BLUE, INPUT);
}

void loop() {
  while(digitalRead(RED))
    tone(SPEAKER, NOTE_C4);
  while(digitalRead(ORANGE))
    tone(SPEAKER, NOTE_D4);
  while(digitalRead(YELLOW))
    tone(SPEAKER, NOTE_E4);
  while(digitalRead(GREEN))
    tone(SPEAKER, NOTE_F4);
  while(digitalRead(BLUE))
    tone(SPEAKER, NOTE_G4);
  
  noTone(SPEAKER);
}
