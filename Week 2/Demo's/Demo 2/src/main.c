#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>

int main() {
  initUSART();
  DDRC &= ~(1 << PC1); //Knop 1 hangt aan C1, we zetten in het Data Direction Register de overeenkomstige bit op 0
  printf("DDRC: ");
  printBinaryByte(DDRC);
  PORTC |= (1 << PC1); //Pull up aanzetten van C1: PINC komt op high te staan
  printf("\nPORTC: ");
  printBinaryByte(PORTC);
  while (1) {
    printf("\nPINC: ");
    printBinaryByte(PINC);
    if ((PINC & (1 << PC1)) == 1) {//op deze manier kunnen we testen of de PC1-e bit van PINC op 0 staat (knop ingeduwd)).
      printf(" - Button 0 pushed!\n");
    } else {
      printf(" - Button 0 NOT pushed!!\n");
    } 
    _delay_ms(1000);
  }
  return 0;
}