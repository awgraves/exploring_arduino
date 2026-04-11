#include "pitches.h"

const int SPEAKER=9;

#define EXAMPLE 0
#define BEETHOVEN 1
#define ROW_ROW_ROW 2

#define SONG ROW_ROW_ROW
#define NOTE_COUNT (sizeof(notes) / sizeof(Note))

typedef struct {
  int pitch;
  int duration; // in millis: 250 is quarter note, 125 is eight note
} Note;

#if SONG == EXAMPLE
Note notes[] = {
  {NOTE_A4, 250}, {NOTE_E3, 250}, {NOTE_A4, 250}, {0, 250},
  {NOTE_A4, 250}, {NOTE_E3, 250}, {NOTE_A4, 250}, {0, 250},
  {NOTE_E4, 125}, {NOTE_D4, 125}, {NOTE_C4, 125}, {NOTE_B4, 125}, {NOTE_A4, 125}, {NOTE_B4, 125}, {NOTE_C4, 125}, {NOTE_D4, 125},
  {NOTE_A4, 250}, {NOTE_E3, 250}, {NOTE_A4, 250}, {0, 250},
};
#elif SONG == BEETHOVEN
Note notes[] = {
  {NOTE_G4, 150}, {NOTE_G4, 150}, {NOTE_G4, 150}, {NOTE_DS4, 1000}, {0, 500},
  {NOTE_F4, 150}, {NOTE_F4, 150}, {NOTE_F4, 150}, {NOTE_D4, 1000}, {0, 500}
};
#elif SONG == ROW_ROW_ROW
Note notes[] = {
  {NOTE_C4, 500},{NOTE_C4, 500},{NOTE_C4, 400},{NOTE_D4, 150}, {NOTE_E4, 500},
  {NOTE_E4, 400},{NOTE_D4, 150},{NOTE_E4, 400},{NOTE_F4, 150}, {NOTE_G4, 750},
  {NOTE_C5, 150},{NOTE_C5, 150},{NOTE_C5, 225},{NOTE_G4, 150}, {NOTE_G4, 150}, {NOTE_G4, 225},
  {NOTE_E4, 150},{NOTE_E4, 150},{NOTE_E4, 225},{NOTE_C4, 150}, {NOTE_C4, 150}, {NOTE_C4, 225},
  {NOTE_G4, 400},{NOTE_F4, 150},{NOTE_E4, 400},{NOTE_D4, 150}, {NOTE_C4, 750}, {0, 50},
};
#endif

void setup() {
  Note note;
  for (int i=0; i<NOTE_COUNT; i++){
    note = notes[i];
    tone(SPEAKER, note.pitch, note.duration);
    delay(note.duration);
  }
}

void loop() {
  // use reset button on arduino to play again
}
