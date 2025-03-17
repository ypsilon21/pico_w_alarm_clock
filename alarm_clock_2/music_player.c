#include "music_player.h"
#include <stdio.h>
#include "pico/stdlib.h"

#include "os_util.h"
#include "music_module.h"

Note convert_bsnf_to_note(char note, uint8_t octave){
    
}

NoteLength convert_bsnf_to_length(uint8_t length){
    
}

void music_file_play(char* path){
    FILE* song = fopen(path, "r");
    if(song == NULL){
        put_error(".bsnf file not found");
        return;
    }

    uint8_t block[4];
    fread(&block, 4, 1, song);
    uint16_t tempo = block[0]*100 + block[1]*10 + block[0];
    music_setTempo(tempo);

    Note note;
    NoteLength length;
    while (fread(&block, 4, 1, song) == 1) { 
        if(block[3] != ' '){
            put_error("wrong formatting in .bsnf file");
            return;
        }
        note = convert_bsnf_to_note((char) block[0], block[1]);
        length = convert_bsnf_to_length(block[3]);
        music_playNote(note, length);
    }

    fclose(song);
}

void music_play(Song song){
    switch(song){
        case ALLE_MEINE_ENTCHEN: music_file_play("alle_meine_entchen.bsnf"); break;
        default: break;
    }
}