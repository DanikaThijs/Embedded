#include <avr/io.h>
#include <display.h>
#include <usart.h>
#include <util/delay.h>
#include <Potentiometer.h>

int main(void){
  initUSART();
  initDisplay();
  initPotentiometer();
  while (1)
  {
    writeNumber(getPotentiometerWaarde());
  }
  
}