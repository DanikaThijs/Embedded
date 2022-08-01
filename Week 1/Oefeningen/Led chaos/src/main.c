#define __DELAY_BACKWARD_COMPATIBLE__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <usart.h>
#include <leds.h>

int main(void){
   initUSART();
   enableAllLeds();
   lightDownAllLeds();
   time_t t;
   srand((unsigned) time(&t));
   for (int i = 0; i < 20; i++)
   {
      int randomLed = rand()%4+1;
      lightUpLed(randomLed);
      _delay_ms(rand()%900+100);
      lightDownLed(randomLed);
   }
   
}