#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT PORTB
#define BUTTON_PORT PORTC
#define BUTTON_PIN PINC
#define LED_DDR DDRB
#define BUTTON_DDR DDRC
#define BUTTON1 PC1
#define LED1 PB2
#define LED2 PB3

// Check eerst de code in de main functie!
// Deze ISR wordt aangeroepen als Pin Change Interrupt 1 afgaat (PCINT1_vect)
// Dit is de interrupt voor PORTC, die waarop de knopjes hangen...
ISR(PCINT1_vect) {
  // knop 1 is ingedrukt (bit staat op 0)?
  if (bit_is_clear(BUTTON_PIN, BUTTON1)) {
    // We wachten 1000 microseconden en checken dan nog eens (debounce!)
    _delay_us(1000);
    // knop 0 is ingedrukt (bit staat op 0)?
    if (bit_is_clear(BUTTON_PIN, BUTTON1)) {
      if (bit_is_set(LED_PORT, LED2)) {  // als led2 uitstaat (bit staat op 1)
        LED_PORT &= ~_BV(LED2);          // zet led2 aan (zet bit op 0)
      } else {                           // anders
        LED_PORT |= _BV(LED2);           // zet led2 uit (zet bit op 1)
      }
    }
  }
}

int main() {
  LED_DDR |= _BV(LED1) | _BV(LED2);   // we gaan led1 en led2 gebruiken
  LED_PORT |= _BV(LED1) | _BV(LED2);  // 2 leds uitzetten
  BUTTON_DDR &= ~_BV(BUTTON1);        // we gaan knop1 gebruiken
  BUTTON_PORT |= _BV(BUTTON1);        // pull up aanzetten
  PCICR |= _BV(PCIE1);  // in Pin Change Interrupt Control Register: geef aan
                        // welke interrupt(s) je wil activeren (PCIE0: poort B,
                        // PCIE1: poort C, PCIE2: poort D)
  PCMSK1 |= _BV(BUTTON1);  // in overeenkomstig Pin Change Mask Register: geef
                           // aan welke pin(s) van die poort de ISR activeren
  sei();  // Set Enable Interrupts --> globaal interrupt systeem aanzetten
  while (1) {
    LED_PORT &= ~_BV(LED1);  // led1 aanzetten
    _delay_ms(100);
    LED_PORT |= _BV(LED1);  // led1 uitzetten
    _delay_ms(100);
  }
  return 0;
}