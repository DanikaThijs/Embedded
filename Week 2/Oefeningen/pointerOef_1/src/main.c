#include <usart.h>

#define MAX 5
#define ZEVENVOUD 7

void printArray(int * array){
  printString("\nInhoud van de array:");
  for (int i = 0; i < MAX; i++)
  {
    printf("\n\tOp adres: %p zit de waarde: %d",&array[i],array[i]);
  }
}

void maakArray(int * array){
  for (int i = 0; i < MAX; i++)
  {
    array[i]+=i*ZEVENVOUD;
  }
  
}

int main(void){
  initUSART();
  int array[MAX] = {0,0,0,0,0}; 
  printArray(array);
  maakArray(array);
  printArray(array);
}