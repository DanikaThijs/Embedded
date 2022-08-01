#include <usart.h>
#include <string.h>
#include <stdio.h>

#define MAX 7

void drukEersteLetters(char (*array)[10]){
    for (int i = 0; i < MAX; i++)
    {
        printf("%c", *(*(array + i)));
    }
}

void drukLaatsteLetters(char (*array)[10]){
    printf("\n");
    char end_char = *array[strlen(*array)-1];
    printf("%c\n", end_char);
    for (int i = 0; i < MAX; i++)
    {
        printf("%c", *(*(array + i)+10-(*array[strlen(*array)])));
    }
}

int main(void){
  initUSART();
  char namen[MAX][10]={"Robbyn","Joppe","Sam","Max","Emma","Robbe","Wouter"};
  drukEersteLetters(namen);
  drukLaatsteLetters(namen);
}