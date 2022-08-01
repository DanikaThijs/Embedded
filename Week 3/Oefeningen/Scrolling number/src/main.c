#include <avr/io.h>
#include <display.h>
#include <util/delay.h>

int main(void){
  initDisplay();
  while(1){
    for (int i = 0; i < 10; i++)
    {
       for (int j = 0; j < 15; j++) {
          writeNumberToSegment(0,i);
          _delay_ms(5);
           writeNumberToSegment(1,(i+1)%10);
         _delay_ms(5);
          writeNumberToSegment(2,(i+2)%10);
         _delay_ms(5);
          writeNumberToSegment(3,(i+3)%10);
         _delay_ms(5);
        }
      }
    }
}
