#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//print block letters
void print_title(void);   
//Spin roulette
int spin_roulette(void);
 
 
int main (void)
{
//Variables    
int betmode;    
int straightbet, cashbet, parity;
int number;
int balance;
char colorbet, R, B;
 
 
//Arrays
int red[18]={1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
int black[18]={2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
     
//Welcome & Title
printf("******************************************************************\n");
printf("******************************************************************\n");
print_title();
printf("\n******************************************************************\n");
printf("******************************************************************\n");
 
 
//Instructions for game
printf("\nEntering the casino, you have $100\n");
printf("There are 3 types of bets you can make\n\n");
printf("1) Straight-up bet: Choose a single number. High risk, high payout! (35 to 1)\n\n");
printf("2) Red or black: Choose a color.(1 to 1)\n Red numbers are  1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36\n Black numbers are 2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35\n\n"); 
printf("3) Odd or even: Choose odd or even (1 to 1)");
 
 
//Select game mode
printf("\nPlease select your preferred type of bet. Enter 1, 2, or 3> ");
scanf("%d", &betmode);
balance=100;
 
 
//Loop to keep game going as long as you have cash
while (balance>0)
{
    if (betmode==1)       //Straight bets
       {
        printf("\nGoing for the big money, eh?\n Enter a number between 1-36 you'd like to bet on> ");
        scanf("%d", &straightbet);
        printf("Now how much money are you willing to risk? Payout is 35 to 1> ");
        scanf("%d", &cashbet);
        printf("\nYou have bet $%d on the number %d", cashbet, straightbet);
        printf("\nPress ENTER to spin the roulette. Keep your fingers crossed!");
        getchar();
        getchar();
        spin_roulette();
                if (number==straightbet)
                  {balance += (cashbet*35);
                   printf("Winner Winner! You now have $%d in your pocket", balance);}
                else
                   balance -= cashbet;
                   printf("Sorry. You've lost $%d. Your new balance is $%d", cashbet, balance);
       }
     else if (betmode==2)         //Red or black bets
          {
           printf("\nAlright pick a color. Choose R for RED or B for BLACK> ");
           scanf("&c", &colorbet);
           printf("\nNow how much money are you willing to risk? Payout is 1 to 1> ");
           scanf("%d", &cashbet);
           printf("\nYou have bet $%d on the color %c", cashbet, colorbet);
           printf("\nPress ENTER to spin the roulette. Keep your fingers crossed!");
           getchar();
           getchar();
           spin_roulette();
                if (colorbet==R)
                    {
                    if (number==red[17])
                      {balance += cashbet;
                       printf("Winner Winner! You now have $%d in your pocket", balance);}
                    else
                       balance -= cashbet;
                       printf("Sorry. You've lost $%d. Your new balance is $%d", cashbet, balance);
                    }                   
                else if (colorbet==B)
                    {
                    if (number==black[17])
                       balance += cashbet;
                       printf("Winner Winner! You now have $%d in your pocket", balance);}
                    else
                       balance -= cashbet;
                       printf("Sorry. You've lost $%d. Your new balance is $%d", cashbet, balance);   
                    }
     else           //Odd or even bets
         {  printf("Alright enter 1 for odd or 2 for even. Choose wisely!> ");
            scanf("%d", &parity);
            printf("\nNow how much money are you willing to risk? Payout is 1 to 1> ");
            scanf("%d", &cashbet);
                  if (parity==1)
                     printf("\nYou have bet $%d on odds", cashbet);
                  else
                      printf("\nYou have bet $%d on evens", cashbet);
            printf("\nPress ENTER to spin the roulette. Keep your fingers crossed!");
            getchar();
            getchar();
            spin_roulette();
                   if (parity==1)
                      {
                        if (number%2==1)
                          {balance += cashbet;
                           printf("Winner Winner! You now have $%d in your pocket", balance);}
                        else
                           balance -= cashbet;
                           printf("Sorry. You've lost $%d. Your new balance is $%d", cashbet, balance);
                        }
                   else
                         if (number%2==0)
                          {balance += cashbet;
                           printf("Winner Winner! You now have $%d in your pocket", balance);}
                        else
                           balance -= cashbet;
                           printf("Sorry. You've lost $%d. Your new balance is $%d", cashbet, balance);
                           }
                               
}
 
 
 
 
 
 
getchar();
getchar();
return (0);
}
 
 
void print_title(void)
{
    printf("       \n");
    printf("*******  ******   *      *  *      ****** ******* *******  ******        \n");
    printf("*     * *      *  *      *  *      *         *       *     *        \n");
    printf("******* *      *  *      *  *      *         *       *     *        \n");
    printf("*   *   *      *  *      *  *      ****      *       *     ****        \n");
    printf("*    *  *      *  *      *  *      *         *       *     *        \n");
    printf("*     *  ******    ******   ****** ******    *       *     ******        ");
    printf("                           ");
}
 
 
int spin_roulette (void)
{
    int number;
    srand(time(NULL));
    number=1+(rand()%36);
    printf("The ball has landed on %d\n", number);
    return number;
}