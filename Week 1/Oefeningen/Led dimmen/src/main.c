#include <util/delay.h>
#include <avr/io.h>
#include <leds.h>
  
int main(void){
  while (1)
  {
  enableAllLeds();
  lightDownAllLeds();
  fadeInLed(1,1000);
  dimLed(2,40,500);
  dimLed(3,60,500);
  dimLed(4,80,500);
  }
}