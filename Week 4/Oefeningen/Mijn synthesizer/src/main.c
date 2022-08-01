#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>
#include <Buzzer.h>
#include <display.h>
#include <Potentiometer.h>
#include <button.h>
#include <avr/interrupt.h>
#include <leds.h>
#include <usart.h>

int MAX_FREQUENTIE = 1050;
int frequentie;
ISR(PCINT1_vect) {
  if (bit_is_clear(PINC, PC1)) {
      if (bit_is_set(PORTB,PB3))
    {
        lightUpLed(3);
        writeString("Aan");
        //playTone(frequentie,500);
    }
    else{
      lightUpLed(3);
      writeString("uit");
  }
    }
    
  }


int main(){
  initDisplay();
  initPotentiometer();
  initUSART();
  
  initBuzzer();
  //PCICR |= _BV(PCIE1);            
  //PCMSK1 |= _BV(PC1);
  //sei(); 
  while(1){
    frequentie = (float)getPotentiometerWaarde()+523;
    while(frequentie < MAX_FREQUENTIE){ 
      frequentie = getPotentiometerWaarde()+523;
      writeNumber(frequentie);
      playTone(frequentie,250);
    }
  writeStringAndWait("NAN",2000);
  writeNumberAndWait(frequentie,2000);
  }
}