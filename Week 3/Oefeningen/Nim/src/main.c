#include <avr/io.h>
#include <display.h>
#include <usart.h>
#include <util/delay.h>
#include <Potentiometer.h>
#include <avr/interrupt.h>
#include <button.h>
#include <stdlib.h>


int aantalLucifers = 21;
int button_pushed = 0;
int luciferKeuze = 2;
int turn = 0;
int computer;
int randomNumber;
int i = 0;
int j;
int *overgeblevenLucifers;
int *weggenomenLucifers;
char *wieAanBeurt;



ISR(PCINT1_vect){

    if (bit_is_clear(PINC, PC1)) {
        button_pushed++;
    }
}

char whosTurn(){
  j = i%10000;
  i++;
  if (turn%2==0)
  {
    if (j>5000)
    {
      return 0;
    }
    else{
      return 80;
    }
  }
  else{
    if (j>5000)
    {
      return 0;
    }
    else{
      return 67;
    }
  }
}

int display3(){
  return (aantalLucifers%10);
}

int display2(){
  return ((aantalLucifers/10)%10);
}

int keuzeAantalLucifers(){
   if (buttonPushed(1)==1&&luciferKeuze>1&&whosTurn()==80)
    {
      luciferKeuze--;
      _delay_ms(200);
      return luciferKeuze;
    }
    
   if (buttonPushed(2)==1&&aantalLucifers>0&&whosTurn()==80)
    {
      aantalLucifers-=luciferKeuze;
      *(overgeblevenLucifers + turn) = aantalLucifers;
      *(weggenomenLucifers + turn) = luciferKeuze;
      *(wieAanBeurt + turn) = 'P';
      //printf("\nJe nam %d lucifer(s) weg, er blijven er nog %d over",luciferKeuze, aantalLucifers);
      _delay_ms(200);
      turn++;
    }  
   if(buttonPushed(2)==1&&aantalLucifers>0&&whosTurn()==67){
      aantalLucifers -= computer;
      *(overgeblevenLucifers + turn) = aantalLucifers;
      *(weggenomenLucifers + turn) = computer;
      *(wieAanBeurt + turn) = 'C';
      //printf("\nDe computer nam %d lucifer(s) weg, er blijven er nog %d over",computer, aantalLucifers);
      _delay_ms(200);
      turn++;
    }
   if (buttonPushed(3)==1&&luciferKeuze<3&&whosTurn()==80)
    {
      luciferKeuze++;
      _delay_ms(200);
      return luciferKeuze;
    }
   if (whosTurn()==67&&aantalLucifers>0)
    {
      computer = (aantalLucifers-1)%(3 + 1);
      if (computer == 0)
      {
        computer = ((randomNumber%3)+1);
        return computer;
      }
      return computer;
    }
}

void printLogboek(){
  printf("\n\n\t\tNim logboek");
  printf("\n\t\t-----------");
  for (int i = 1; i < turn; i++)
    {
      printf("\nZet: %d\nBeurt: %d\nWeggenomen lucifers: %d\nOvergebleven lucifers: %d\n", i, *(wieAanBeurt+i), (char)*(weggenomenLucifers+i), *(overgeblevenLucifers+i));
    }
    
}


int main(void){
  initUSART();
  initDisplay();
  initPotentiometer();
  overgeblevenLucifers = (int*)calloc(21, sizeof(int));
  weggenomenLucifers = (int*)calloc(21,sizeof(int));
  wieAanBeurt = (char*)calloc(21,sizeof(char));
  printString("\nDraai aan de potentiometer om een seed te genereren");
  for (int i = 3; i > 0; i--)
  {
    printf("\n%d..",i);
    _delay_ms(1000);
  }
  srand(getPotentiometerWaarde());
  randomNumber = rand() % 10000;
  PCICR |= _BV(PCIE1);
  PCMSK1 |= _BV(PC1);
  sei();
  printf("\nJe seed is: %d",randomNumber);
  if (randomNumber%2==0)
  {
    printf("\nDe speler mag beginnen");
    turn = 0;
  }
  else{
    printf("\nDe computer mag beginnen");
    turn = 1;
  }
  
  printString("\nDruk op knop 1 om het spel te starten");

  while (button_pushed < 1)
  {
  writeNumber(randomNumber);
  }
  printString("\nHet spel is gestart!");
  
  while (aantalLucifers>0)
  {  
    writeNumberToSegment(3,display3());
    writeNumberToSegment(2,display2());
    writeCharToSegment(1,whosTurn());
    writeNumberToSegment(0,keuzeAantalLucifers()); 
  }
  printLogboek();
  loopAnimation(2);
  while (1)
  {

    if (whosTurn()==67)
    {
      scrollingText("\nDe computer is gewonnen ");
    }
    else{
      scrollingText("\nJe bent gewonnen ");
    }
  }
  
  
  
}