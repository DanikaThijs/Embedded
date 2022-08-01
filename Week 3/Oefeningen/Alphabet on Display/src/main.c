#include <avr/io.h>
#include <display.h>
#include <usart.h>
#include <util/delay.h>

int main(void){
  initUSART();
  initDisplay();
  while (1)
  {
  writeCharToSegment(0,'A');
  _delay_ms(500);
  writeStringAndWait("Hallo",500);
  }
}