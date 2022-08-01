#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>


void initBuzzer() { 
  DDRD |= (1 << PD3); 
}

void playTone(int frequency, uint32_t duration) {
  uint32_t periodInMicro = (uint32_t)(1000000/frequency);//we berekenen de periode in microseconden uit de frequency
  uint32_t durationInMicro = duration * 1000; //we willen duration in microseconden
  for (uint32_t time = 0; time < durationInMicro; time += periodInMicro) {//Zie tutorial over muziek voor meer uitleg!
    PORTD &= ~(1 << PD3);//aanzetten van de buzzer
    _delay_us(periodInMicro / 2);//helft van de periode wachten
    PORTD |= (1 << PD3);//afzetten van de buzzer
    _delay_us(periodInMicro / 2);//weer helft van de periode wachten
  }
}

void playWinningSong(){
  playTone(500,200);
  _delay_us(200);
  playTone(500,200);
  _delay_us(200);
  playTone(500,200);
  _delay_us(200);
  playTone(800,150);
  _delay_us(150);
  playTone(500,500);
  _delay_us(500);
  playTone(600,1000);
}

void playOneUpSound(){
  playTone(1319,125);
  _delay_us(130);
  playTone(1568,125);
  _delay_us(130);
  playTone(2637,125);
  _delay_us(130);
  playTone(2093,125);
  _delay_us(130);
  playTone(2349,125);
  _delay_us(130);
  playTone(3136,125);
}

void playFireBallSound(){
  playTone(392,40);
  _delay_us(40);
  playTone(784,40);
  _delay_us(40);
  playTone(1568,40);
}

void playCoinSound(){
  playTone(988,100);
  _delay_us(100);
  playTone(1319,850);
}