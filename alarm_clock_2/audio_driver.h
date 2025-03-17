#ifndef AUDIO_DRIVER_H
#define AUDIO_DRIVER_H

void audio_init();
void audio_set_dutyCycle(uint16_t dutyCycle);
void audio_play_frequency(uint16_t frequency, uint32_t length, uint8_t volume);

#endif