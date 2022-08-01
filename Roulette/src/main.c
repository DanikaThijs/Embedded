#define __DELAY_BACKWARD_COMPATIBLE__
#include <display.h>
#include <button.h>
#include <usart.h>
#include <util/delay.h>
#include <Potentiometer.h>
#include <avr/interrupt.h>
#include <leds.h>
#include <stdlib.h>
#include <Buzzer.h>


#define INTRO "ROULETTE "
#define INZETTYPE1 "EN PLEIN "
#define INZETTYPE2 "NOIR ROUGE "
#define INZETTYPE3 "IMPAIR PAIR "
#define INZETTYPE4 "DOUZAINE "

int rouge[18]={1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
int noir[18]={2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};

int* lijst;


int startChips = 20;
int startSpel = 0;
int inzet_type = 0;
int stopType = 0;
int nummerKeuze = 1;

typedef struct {
  int* aantalChips;
  int* resultaat;
  char* inzetType; 
} LOGBOEK;

LOGBOEK logboek1;

int draaiAanWiel()
{
    int resultaat;
    srand(getPotentiometerWaarde());
    resultaat=rand()%36 +1;
    return resultaat;
}

int playCasino(int inzet, int gameType){
  int uitkomstWiel;

  // En plein
  if (gameType == 0)
  {
    while (stopType < 1)
    {
      if (nummerKeuze > 36 || nummerKeuze < 1){
        nummerKeuze = 1;
      }
      writeNumber(nummerKeuze);
    }
    loopAnimation(3);
    uitkomstWiel = draaiAanWiel();
    printf("\nUITKOMST VAN HET WIEL: %d", uitkomstWiel);
    if (uitkomstWiel == nummerKeuze)
    {
      printString("\nProficiat, het was juist!");
      stopType = 0;
      return inzet*35;
    }
    else{
      printString("\nHelaas, het was fout!");
      stopType = 0;
      return -inzet;
    }
  }

  // Noir rouge
  if (gameType == 1)
  {
    //Kies N of R
    while (stopType < 1)
    {
      if (nummerKeuze %2 == 0)
      {
        scrollingText("ROUGE ");
      }
      else{
        scrollingText("NOIR ");
      }
    }
    loopAnimation(3);
    uitkomstWiel = draaiAanWiel();
    printf("\nUITKOMST VAN HET WIEL: %d", uitkomstWiel);
    if (nummerKeuze%2 == uitkomstWiel%2)
    {
      printString("\nProficiat, het was juist!");
      stopType = 0;
      return inzet;
    }
    else{
      printString("\nHelaas, het was fout!");
      stopType = 0;
      return -inzet;
    }
    
  }
    
  // Pair impair
  if (gameType == 2)
  {
  while (stopType < 1)
    {
       if (nummerKeuze %2 == 0)
      {
        scrollingText("PAIR  ");
      }
      else{
        scrollingText("IMPAIR ");
      }
    }
    loopAnimation(3);
    uitkomstWiel = draaiAanWiel();
    printf("\nUITKOMST VAN HET WIEL: %d", uitkomstWiel);
    if (uitkomstWiel%2 == nummerKeuze%2)
    {
      printString("\nProficiat, het was juist!");
      stopType = 0;
      return inzet;
    }
    else{
      printString("\nHelaas, het was fout!");
      stopType = 0;
      return -inzet;
    }
  }
  
  // Douzaine
  if (gameType == 3)
  {
    while (stopType < 1)
    {
      if (nummerKeuze%3 == 0)
      {
        scrollingText(" 1-12");
      }
      else if (nummerKeuze%3 == 1)
      {
        scrollingText(" 13-24");
      }
      else if (nummerKeuze%3 == 2)
      {
        scrollingText(" 25-36");
      }
    }
    loopAnimation(3);
    uitkomstWiel = draaiAanWiel();
    printf("\nUITKOMST VAN HET WIEL: %d", uitkomstWiel);
    if (uitkomstWiel>=1 && uitkomstWiel <=12)
    {
      if (nummerKeuze%3 == 0)
      {
        printString("\nProficiat, het was juist!");
        stopType = 0;
        return inzet*2;
      }
      else{
        printString("\nHelaas, het was fout!");
        stopType = 0;
        return -inzet;
      }
    }
    else if (uitkomstWiel>=13 && uitkomstWiel <=24)
    {
      if (nummerKeuze%3 == 1)
      {
        printString("\nProficiat, het was juist!");
        stopType = 0;
        return inzet*2;
      }
      else{
        printString("\nHelaas, het was fout!");
        stopType = 0;
        return -inzet;
      }
    }
    else if (uitkomstWiel>=25 && uitkomstWiel <=36)
    {
      if (nummerKeuze%3 == 2)
      {
        printString("\nProficiat, het was juist!");
        stopType = 0;
        return inzet*2;
      }
      else{
        printString("\nHelaas, het was fout!");
        stopType = 0;
        return -inzet;
      }
    }
  }
  
}

int inzetType(){
  while (stopType < 1)
  {
      if (nummerKeuze %4 == 0)
      {
        scrollingText(INZETTYPE1);
      }
      else if (nummerKeuze %4 == 1){
        scrollingText(INZETTYPE2);
      }
      else if (nummerKeuze %4 == 2){
        scrollingText(INZETTYPE3);
      }
      else if (nummerKeuze %4 == 3){
        scrollingText(INZETTYPE4);
      }
  } 
  stopType = 0;
  printf("\nEinde keuze, stopType: %d",stopType);
  return nummerKeuze%4;
}

void scrollingText(char * str){
  size_t arrayLength = strlen(str);
  size_t i = 0;
  while (i < arrayLength)
    {
      int j = 0;
      while (j < 20)
        {
          writeCharToSegment(0,str[i]);
          _delay_ms(5);
          writeCharToSegment(1,str[(i+1)%arrayLength]);
          _delay_ms(5);
          writeCharToSegment(2,str[(i+2)%arrayLength]);
          _delay_ms(5);
          writeCharToSegment(3,str[(i+3)%arrayLength]);
          _delay_ms(5);
          j++;
        }
      i++;
    }
}


ISR(PCINT1_vect){
    if (bit_is_clear(PINC, PC1)) {
      startSpel = 1;
      nummerKeuze--;
      playTone(100,100);
    }
    if (bit_is_clear(PINC, PC2)) {
      stopType=1;
      playTone(100,100);
    }
    if (bit_is_clear(PINC, PC3)) {
      nummerKeuze++;
      inzet_type++;
      playTone(100,100);
    }
}

void test(int *aantalChips){

}

int main(void)
{
  initDisplay();
  initUSART();
  initPotentiometer();
  initBuzzer();
  logboek1.aantalChips = malloc(sizeof(int)*50);
  logboek1.resultaat = malloc(sizeof(int)*50);
  logboek1.inzetType = malloc(sizeof(char)*50);
  test(logboek1.aantalChips);
  playTone(100,200);
  playTone(150,200);
  PCICR |= 0b00001110;
  PCMSK1 |= 0b00001110;
  sei();
  int aantal = 15;
  lijst = calloc(aantal,sizeof(int));

  
  while (startSpel < 1)
  {
    scrollingText(INTRO);
  } 

  
  int aantalChips = startChips;
  while (aantalChips > 0)
  {
    int spelKeuze = inzetType();
    aantalChips += playCasino(2,spelKeuze);
    printf("\nAantal chips: %d",aantalChips);
  }
  playTone(400,100);
  playTone(500,100);
  while (1)
  {
    scrollingText("GAME OVER ");
  }
  
}
