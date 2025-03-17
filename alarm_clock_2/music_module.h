#ifndef MUSIC_MODULE_H
#define MUSIC_MODULE_H

#include <stdio.h>
#include "pico/stdlib.h"

typedef enum{
    C3, Cs3, D3, Ds3, E3, F3, Fs3, G3, Gs3, A3, As3, B3,
    C4, Cs4, D4, Ds4, E4, F4, Fs4, G4, Gs4, A4, As4, B4,
    BREAK
} Note;

typedef enum{
    SXT, EIG, QUA, HAL, WHL,
    SXT_, EIG_, QUA_, HAL_, WHL_
} NoteLength;

void music_setTempo(uint16_t bpm);
void music_setVolume(uint8_t volume_percentage);
void music_playNote(Note note, NoteLength length);
void music_playNote_customLength(Note note, float length);


#endif