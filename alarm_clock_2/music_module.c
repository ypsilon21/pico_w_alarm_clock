#include "music_module.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include <stdbool.h>

#include "audio_driver.h"

//how many ms of silence follow a note
#define NOTE_COOLDOWN 20

//tempo in beats/minute
uint16_t tempo = 100;
//volume in %
uint8_t volume = 50;

void music_setTempo(uint16_t bpm){
    tempo = bpm;
}

void music_setVolume(uint8_t volume_percentage){
    volume = volume_percentage;
}

//takes a Note and returns its corresponding frequency in Hz
uint16_t noteToFrequency(Note note){
    switch(note){
        case C3: return 130;
        case Cs3: return 138;
        case D3: return 146;
        case Ds3: return 155;
        case E3: return 164;
        case F3: return 174;
        case Fs3: return 185;
        case G3: return 196;
        case Gs3: return 208;
        case A3: return 220;
        case As3: return 233;
        case B3: return 246;

        case C4: return 261;
        case Cs4: return 277;
        case D4: return 293;
        case Ds4: return 311;
        case E4: return 329;
        case F4: return 349;
        case Fs4: return 369;
        case G4: return 392;
        case Gs4: return 415;
        case A4: return 440;
        case As4: return 466;
        case B4: return 493;

        default: return 0;
    }
}

//takes a NoteLength and returns the corresponding time in ms based on the set tempo
uint32_t noteLenghtToMs(NoteLength length){
    //length of a quarter note is 60s/ tempo(bpm)
    uint32_t quarterMs = (60 * 1000) / tempo;

    switch(length){
        case SXT: return (uint32_t) ((float) quarterMs) / 4.0f;
        case SXT_: return (uint32_t) ((float) quarterMs) / 4.0f + (uint32_t) ((float) quarterMs) / 8.0f;
        case EIG: return (uint32_t) ((float) quarterMs) / 2.0f;
        case EIG_: return (uint32_t) ((float) quarterMs) / 2.0f + (uint32_t) ((float) quarterMs) / 4.0f;
        case QUA: return quarterMs;
        case QUA_: return quarterMs + (uint32_t) ((float) quarterMs) / 2.0f;
        case HAL: return quarterMs * 2;
        case HAL_: return quarterMs * 3;
        case WHL: return quarterMs * 4;
        case WHL_: return quarterMs * 6;
        default: return quarterMs;
    }
}

//plays a Note for a given Length
void music_playNote(Note note, NoteLength length){
    if(note != BREAK){
        audio_set_dutyCycle(volume);
        audio_set_frequency(noteToFrequency(note));

        sleep_ms(noteLenghtToMs(length) - NOTE_COOLDOWN);
        audio_set_dutyCycle(0);
        sleep_ms(NOTE_COOLDOWN);
    }
    else sleep_ms(noteLenghtToMs(length));
}

//plays a Note for a given custom length
//length is given as a fraction of a quarter note 
void music_playNote_customLength(Note note, float length){
    if(note != BREAK){
        audio_set_dutyCycle(volume);
        audio_set_frequency(noteToFrequency(note));

        uint32_t quarterMs = (60 * 1000) / tempo;
        uint32_t len = (uint32_t) ((float) quarterMs) * length;
        sleep_ms(len - NOTE_COOLDOWN);
        audio_set_dutyCycle(0);
        sleep_ms(NOTE_COOLDOWN);
    }
    else sleep_ms(noteLenghtToMs(length));
}