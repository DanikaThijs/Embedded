#include <Button.h>
#include <usart.h>
#include <avr/delay.h>

int main(void){
  enableButton(1);
  enableButton(2);
  enableButton(3);
  initUSART();
  while (1)
  {
    if (buttonPushed(1) == 1)
    {
      printString("\nButton 1 pushed!");
      _delay_ms(150);
    }
    else if (buttonPushed(2) == 1)
    {
      printString("\nButton 2 pushed!");
      _delay_ms(150);
    }
    else if (buttonPushed(3) == 1)
    {
      printString("\nButton 3 pushed!");
      _delay_ms(150);
    }
  }
}
  