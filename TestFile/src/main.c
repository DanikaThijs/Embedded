#include <button.h>
#include <display.h>
#include <util/delay.h>
#include <usart.h>

int counter;
int buttonsPushed[10];
int i = 0;

int main(){
  enableAllButtons();
  initDisplay();
  initUSART();
    while (i < 10)
    {
      if (buttonPushed(1) == 1)
      {
      buttonsPushed[i] = 1;
      i++;
      _delay_ms(200);
      }

      else if (buttonPushed(2) == 1)
      {
      buttonsPushed[i] = 2;
      i++;
      _delay_ms(200);
      }

      else if (buttonPushed(3) == 1)
      {
      buttonsPushed[i] = 3;
      i++;
      _delay_ms(200);
      }
    } 
  printf("\n[");
  for (int i = 0; i < 10; i++)
  {
    printf("%d ",buttonsPushed[i]);
  }
  printf("]");
}
