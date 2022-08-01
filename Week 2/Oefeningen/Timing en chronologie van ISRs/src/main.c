#include <avr/interrupt.h>
#include <leds.h>
#include <avr/delay.h>
#include <usart.h>

ISR(PCINT1_vect){
    if (bit_is_clear(PINC, PC1)) {
      printString("\nISR");
      lightUpLed(2);
      lightUpLed(3);
      _delay_ms(5000);
      lightDownLed(2);
      lightDownLed(3);
      _delay_ms(5000);
    }
}


int main(void){
  PCICR |= 0b00001110;
  PCMSK1 |= 0b00001110;
  sei();
  initUSART();
  enableAllLeds();
  lightDownAllLeds();
  while (1)
  {
    lightUpLed(1);
    lightUpLed(2);
    printString("\nAan");
    _delay_ms(2000);
    printString("\nNaar uit");
    lightDownLed(1);
    lightDownLed(2),
    printString("\nUit");
    _delay_ms(2000);
    printString("\nNaar aan");
  }
  
}

// Vragen:
// • Knippert LED D1 nog verder op het moment dat de ISR is gestart?
// Nee de led blijf in zijn huidige staat nadat de ISR is gestart.

// • Heeft de status van D2 invloed in het normale programma een invloed op de status van D2 bij het lopen van de ISR? 
// Nee

// • Knippert LED D1 en D2 verder nadat de ISR is afgehandeld(afgelopen dus)? 
// Ja ze gaan weer verder met hun routine

// • Wanneer LED D1 en D2 voor het starten van de ISR aan waren, zijn ze dan nog steeds aan na het uitvoeren van de ISR? 
// Ja, de ISR onderbreekt het programma en laat het erna weer verder gaan.

// • Wanneer LED D1 en D2 voor het starten van de ISR uit waren, zijn ze dan nog steeds uit na het uitvoeren van de ISR? 
// Ja, de ISR onderbreekt het programma en laat het erna weer verder gaan.

// • Wanneer LED D1 en D2 voor het starten van de ISR nog maar 0,5 seconden aan waren, zullen ze na het uitvoeren van de ISR dan nog 1,5 seconde hun status behouden? 
// Ja