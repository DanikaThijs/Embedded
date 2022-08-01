#include <button.h>
#include <leds.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <display.h>
#include <usart.h>
#include <stdlib.h>

#define DELAY 500

int button_pushed = 0;
int teller = 0;
int uitkomst;


void gereratePuzzle(uint8_t array[], int size){
    srand(teller); 
    initUSART();
    for (int i = 0; i < size; i++)
    {
         array[i] = (rand()%3)+1;
         
    }
}

void printPuzzle(uint8_t array[], int size){
    initUSART();
    printString("\nFout, het juiste patroon was: [");
    for (int i = 0; i < size; i++)
    {
        printf("%d ",array[i]);;
    }
    printString("]");
}

void playPuzzle(uint8_t array[], int size){
    disableAllLeds();
    for (int i = 0; i < size; i++)
    {
        enableLed(array[i]);
        lightUpLed(array[i]);
        _delay_ms(DELAY);
        lightDownLed(array[i]);
        disableLed(array[i]);
        _delay_ms(DELAY);
    }
}

int readInput(uint8_t array[], int size){
    int b = 0;
    uint8_t userInput[size];
    while (b < size)
    {
      if (buttonPushed(1) == 1)
      {
          if (array[b] == 1)
          {
              printString("\nJe drukte op knop 1, correct!");
          }
          else{
              printString("\nJe drukte op knop 1, fout!");
          }
      userInput[b] = 1;
      b++;
      _delay_ms(200);
      }

      else if (buttonPushed(2) == 1)
      {
          if (array[b] == 2)
          {
              printString("\nJe drukte op knop 2, correct!");
          }
          else{
              printString("\nJe drukte op knop 2, fout!");
          }
      userInput[b] = 2;
      b++;
      _delay_ms(200);
      }

      else if (buttonPushed(3) == 1)
      {
          if (array[b] == 3)
          {
              printString("\nJe drukte op knop 3, correct!");
          }
          else{
              printString("\nJe drukte op knop 3, fout!");
          }
      userInput[b] = 3;
      b++;
      _delay_ms(200);
      }

    }

    int counter = 0;
    for (int i = 0; i < size; i++)
    {
        if (array[i] == userInput[i])
        {
            counter++;
        }
        else{
            counter+=0;
        }
        
    }

    if (counter == size)
    {
        return 1;
    }
    else{
        return 0;
    }
    

    return counter;
    
}

    
        
    
ISR(PCINT1_vect){
    initUSART();
    if (bit_is_clear(PINC, PC1)) {
        button_pushed = 1;
    }
}

int main(void){
    initUSART();
    disableAllLeds();
    enableLed(4);
    PCICR |= _BV(PCIE1);
    PCMSK1 |= _BV(PC1);
    sei();
    uint8_t randomNumbers[10];
    printString("\nDruk op knop1 om het spel te starten");
    while (button_pushed < 1)
    {
        lightUpLed(4);
        _delay_ms(100);
        lightDownLed(4);
        _delay_ms(100);
        teller++;
    }

    for (int z = 1; z < 11; z++)
    {
        gereratePuzzle(randomNumbers, z);
        playPuzzle(randomNumbers, z);
        uitkomst = readInput(randomNumbers, z);
        if (uitkomst == 1)
        {
            enableLed(4);
            for (int j = 0; j < 4; j++)
            {
                lightUpLed(4);
                _delay_ms(100);
                lightDownLed(4);
                _delay_ms(100);
            }
            printf("\nCorrect, we gaan naar level %d",z+1);
        }
        else{
            printPuzzle(randomNumbers, z);
            enableAllLeds();
            lightUpAllLeds();
            movingLedAnimation(5,20);
            return;
        }
        
        _delay_ms(DELAY);
    }

    printString("\nProficiat, je bent de Simon Master!");
    
}