#include <avr/io.h>
#include <util/delay.h>


void initBuzzer();
void playTone(int frequency, uint32_t duration);
void playWinningSong();
void playOneUpSound();
void playFireBallSound();
void playCoinSound();