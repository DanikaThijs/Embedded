#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>

#define NUMBER_OF_LEDS 4

void enableLed(int ledNumber){
  if(ledNumber < 1 || ledNumber > NUMBER_OF_LEDS) return;
  DDRB |= (1<<(PB2 + (NUMBER_OF_LEDS - ledNumber)));
}

void enableMultipleLeds(uint8_t leds){
  if(leds / ((uint8_t) pow(2,NUMBER_OF_LEDS + PB2)) > 0 || leds % ((uint8_t) pow(2,PB2)) > 0) return;
  DDRB |= leds;
}

void enableAllLeds(){
  DDRB |= 0b00111100;
}



void disableLed(int ledNumber){
  if(ledNumber <1 || ledNumber>NUMBER_OF_LEDS) return;
  DDRB = (0<<(PB2 + (NUMBER_OF_LEDS - ledNumber)));
}

void disableMultipleLeds(uint8_t leds){
  if(leds / ((uint8_t) pow(2,NUMBER_OF_LEDS + PB2)) > 0 || leds % ((uint8_t) pow(2,PB2)) > 0) return;
  DDRB = leds;
}

void disableAllLeds(){
  DDRB = 0b00000000;
}



void lightUpLed(int ledNumber){
  if(ledNumber < 1 || ledNumber > NUMBER_OF_LEDS) return;
  PORTB &= ~(1<<(PB2 + (NUMBER_OF_LEDS - ledNumber)));
}

void lightUpLeds(uint8_t leds){
  if(leds / ((uint8_t) pow(2,NUMBER_OF_LEDS + PB2)) > 0 || leds % ((uint8_t) pow(2,PB2)) > 0) return;
  PORTB = leds;
}

void lightUpAllLeds(){
  PORTB = 0b00000000;
}



void lightDownLed(int ledNumber){
  if(ledNumber < 1 || ledNumber > NUMBER_OF_LEDS) return;
  PORTB |= (1<<(PB2 + (NUMBER_OF_LEDS - ledNumber)));
}

void lightDownLeds(uint8_t leds){
  if(leds / ((uint8_t) pow(2,NUMBER_OF_LEDS + PB2)) > 0 || leds % ((uint8_t) pow(2,PB2)) > 0) return;
  PORTB |= leds;
}

void lightDownAllLeds(){
  PORTB = 0b00111100;
}

void lightInverseOneLed(int ledNumber){
  if (ledNumber < 1 || ledNumber > NUMBER_OF_LEDS) return;
  PORTB ^= (1 << (PB2 + (NUMBER_OF_LEDS - ledNumber)));
}

void movingLedAnimation(int loops, int speed){
  lightDownAllLeds();
  while (loops > 0)
  {
   lightUpLed(1);
   _delay_ms(speed);
   lightUpLed(2);
   lightDownLed(1);
   _delay_ms(speed);
   lightUpLed(3);
   lightDownLed(2);
   _delay_ms(speed);
   lightUpLed(4);
   lightDownLed(3);
   _delay_ms(speed);
   _delay_ms(speed);
   lightUpLed(3);
   lightDownLed(4);
   _delay_ms(speed);
   lightUpLed(2);
   lightDownLed(3);
   _delay_ms(speed);
   lightUpLed(1);
   lightDownLed(2);
   _delay_ms(speed);
   lightDownLed(1);
   loops--;
  }
}

void dimLed(int ledNumber, int percentage, int duration){
  if (ledNumber < 1 || ledNumber > NUMBER_OF_LEDS) return;
  while(duration > 0){
  lightUpLed(ledNumber);
  _delay_ms(percentage/10);
  lightDownLed(ledNumber);
  _delay_ms(10-(percentage/10));
  duration-=10;
  }
}

void fadeInLed(int ledNumber, int duration){
  for (int i = 0; i < duration/10; i++)
  {
    dimLed(ledNumber,i,duration/100);
  }
  
}

void countdown(int duration){
  enableAllLeds();
  lightUpAllLeds();
  _delay_ms(duration/4);
  lightDownLed(4);
  _delay_ms(duration/4);
  lightDownLed(3);
  _delay_ms(duration/4);
  lightDownLed(2);
  _delay_ms(duration/4);
  lightDownLed(1);
  _delay_ms(500);
}

void morse_kort(){
  lightUpAllLeds();
  _delay_ms(200);
  lightDownAllLeds();
  _delay_ms(200);
}

void morse_lang(){
  lightUpAllLeds();
  _delay_ms(800);
  lightDownAllLeds();
  _delay_ms(200);
}

void morse_eindAnimatie(){
  _delay_ms(2000);
  movingLedAnimation(1,50);
  _delay_ms(2000);
}

