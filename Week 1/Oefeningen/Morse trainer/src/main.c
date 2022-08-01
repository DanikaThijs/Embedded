#include <leds.h>
#include <usart.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
  char morse_code[] = {65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90};
  int count = 0;
  time_t t;
  srand((unsigned) time(&t));

  initUSART();
  enableAllLeds();
  lightDownAllLeds();
  countdown(4000);
  while (count < 10)
  {
    int randomNumber = rand() % 25 + 65;
    printf("\nLetter %i:", count+1);
    //A
    if (randomNumber == morse_code[0])
    {
      morse_kort();
      morse_lang();
      _delay_ms(2000);
      printString("\nDe juiste letter was A");
      morse_eindAnimatie();
    }

    //B
    else if (randomNumber == morse_code[1])
    {
      morse_lang();
      morse_kort();
      morse_kort();
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was B");
      morse_eindAnimatie();
    }

    //C
    else if (randomNumber == morse_code[2])
    {
      morse_lang();
      morse_kort();
      morse_lang();
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was C");
      morse_eindAnimatie();
    }

    //D
    else if (randomNumber == morse_code[3])
    {
      morse_lang();
      morse_kort();
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was D");
      morse_eindAnimatie();
    }

    //E
    else if (randomNumber == morse_code[4])
    {
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was E");
      morse_eindAnimatie();
    }

    //F
    else if (randomNumber == morse_code[5])
    {
      morse_kort();
      morse_kort();
      morse_lang();
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was F");
      morse_eindAnimatie();
    }

    //G
    else if (randomNumber == morse_code[6])
    {
      morse_lang();
      morse_lang();
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was G");
      morse_eindAnimatie();
    }

    //H
    else if (randomNumber == morse_code[7])
    {
      morse_kort();
      morse_kort();
      morse_kort();
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was H");
      morse_eindAnimatie();
    }

    //I
    else if (randomNumber == morse_code[8])
    {
      morse_kort();
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was I");
      morse_eindAnimatie();
    }

    //J
    else if (randomNumber == morse_code[9])
    {
      morse_kort();
      morse_lang();
      morse_lang();
      morse_lang();
      _delay_ms(2000);
      printString("\nDe juiste letter was J");
      morse_eindAnimatie();
    }

    //K
    else if (randomNumber == morse_code[10])
    {
      morse_lang();
      morse_kort();
      morse_lang();
      _delay_ms(2000);
      printString("\nDe juiste letter was K");
      morse_eindAnimatie();
    }

    //L
    else if (randomNumber == morse_code[11])
    {
      morse_kort();
      morse_lang();
      morse_kort();
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was L");
      morse_eindAnimatie();
    }

    //M
    else if (randomNumber == morse_code[12])
    {
      morse_lang();
      morse_lang();
      _delay_ms(2000);
      printString("\nDe juiste letter was M");
      morse_eindAnimatie();
    }

    //N
    else if (randomNumber == morse_code[13])
    {
      morse_lang();
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was N");
      morse_eindAnimatie();
    }

    //O
    else if (randomNumber == morse_code[14])
    {
      morse_lang();
      morse_lang();
      morse_lang();
      _delay_ms(2000);
      printString("\nDe juiste letter was O");
      morse_eindAnimatie();
    }

    //P
    else if (randomNumber == morse_code[15])
    {
      morse_kort();
      morse_lang();
      morse_lang();
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was P");
      morse_eindAnimatie();
    }

    //Q
    else if (randomNumber == morse_code[16])
    {
      morse_lang();
      morse_lang();
      morse_kort();
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was Q");
      morse_eindAnimatie();
    }

    //R
    else if (randomNumber == morse_code[17])
    {
      morse_kort();
      morse_lang();
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was R");
      morse_eindAnimatie();
    }

    //S
    else if (randomNumber == morse_code[18])
    {
      morse_kort();
      morse_kort();
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was S");
      morse_eindAnimatie();
    }

    //T
    else if (randomNumber == morse_code[19])
    {
      morse_lang();
      _delay_ms(2000);
      printString("\nDe juiste letter was T");
      morse_eindAnimatie();
    }

    //U
    else if (randomNumber == morse_code[20])
    {
      morse_kort();
      morse_kort();
      morse_lang();
      _delay_ms(2000);
      printString("\nDe juiste letter was U");
      morse_eindAnimatie();
    }

    //V
    else if (randomNumber == morse_code[21])
    {
      morse_kort();
      morse_kort();
      morse_kort();
      morse_lang();
      _delay_ms(2000);
      printString("\nDe juiste letter was V");
      morse_eindAnimatie();
    }

    //W
    else if (randomNumber == morse_code[22])
    {
      morse_kort();
      morse_lang();
      morse_lang();
      _delay_ms(2000);
      printString("\nDe juiste letter was W");
      morse_eindAnimatie();
    }

    //X
    else if (randomNumber == morse_code[23])
    {
      morse_lang();
      morse_kort();
      morse_kort();
      morse_lang();
      _delay_ms(2000);
      printString("\nDe juiste letter was X");
      morse_eindAnimatie();
    }

    //Y
    else if (randomNumber == morse_code[24])
    {
      morse_lang();
      morse_kort();
      morse_lang();
      morse_lang();
      _delay_ms(2000);
      printString("\nDe juiste letter was Y");
      morse_eindAnimatie();
    }

    //Z
    else if (randomNumber == morse_code[25])
    {
      morse_lang();
      morse_lang();
      morse_kort();
      morse_kort();
      _delay_ms(2000);
      printString("\nDe juiste letter was Z");
      morse_eindAnimatie();
    }

    else{
      printf("\nOepsie deze letter bestaat niet (gevonden ASCII cijfer: %d)", randomNumber);

    }
    
    count++;
  }
  
  movingLedAnimation(5,100);
}