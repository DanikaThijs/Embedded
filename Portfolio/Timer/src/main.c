#include <util/delay.h>
#include <display.h>
#include <leds.h>
#include <Potentiometer.h>
#include <usart.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <button.h>
#include <Buzzer.h>
#include <stdbool.h>

#define delay 1

int seconden;
int secondenT;
int minuten;
int minutenT;

int minutenTReset;
int minutenReset;
int secondenTReset;
int secondenReset;

bool bevestigd;

void setTimer()
{
  initUSART();
  initDisplay();

  printf("\n\nDruk op knop 1 om de seconden te verhogen.");
  printf("\nDruk op knop 2 om de seconden te verlagen.");
  printf("\nDruk op knop 3 om de seconden te bevestigen.");
  bevestigd = false;
  do
  {

    projectTimer();
    if (buttonPushed(1) == 1)
    {
      for (int i = 0; i < 200; i++)
      {
        projectTimer();
        _delay_ms(delay);
      }

      seconden++;

      if (seconden >= 10)
      {
        secondenT++;
        seconden = 0;
      }

      if (secondenT >= 6 && secondenT >= 0)
      {
        secondenT = 0;
        seconden = 0;
      }

      projectTimer();
    }
    if (buttonPushed(2) == 1)
    {
      for (int i = 0; i < 200; i++)
      {
        projectTimer();
        _delay_ms(delay);
      }
      if (seconden > 0)
      {
        seconden--;
      }

      else if (seconden == 0 && secondenT > 0)
      {
        secondenT--;
        seconden = 9;
      }

      else if (seconden == 0 && secondenT == 0)
      {
        seconden = 9;
        secondenT = 5;
      }

      projectTimer();
    }
    if (buttonPushed(3) == 1)
    {

      while (!buttonReleased(3))
      {
        bevestigd = true;
      }
    }

    projectTimer();

  } while (!bevestigd);

  printf("\n\nDruk op knop 1 om de minuten te verhogen.");
  printf("\nDruk op knop 2 om de minuten te verlagen.");
  printf("\nDruk op knop 3 om de minuten te bevestigen.");
  bevestigd = false;
  do
  {
    projectTimer();
    if (buttonPushed(1) == 1)
    {
      for (int i = 0; i < 200; i++)
      {
        projectTimer();
        _delay_ms(delay);
      }

      minuten++;

      if (minutenT == 9 && minuten == 10)
      {
        minutenT = 0;
        minuten = 0;
      }

      else if (minuten >= 10)
      {
        minutenT++;
        minuten = 0;
      }
      projectTimer();
    }
    else if (buttonPushed(2) == 1)
    {
      for (int i = 0; i < 200; i++)
      {
        projectTimer();
        _delay_ms(delay);
      }
      if (minuten > 0)
      {
        minuten--;
      }
      else if (minuten == 0 && minutenT > 0)
      {
        minutenT--;
        minuten = 9;
      }
      else if (minuten == 0 && minutenT == 0)
      {
        minuten = 9;
        minutenT = 9;
      }
      projectTimer();
    }
    else if (buttonPushed(3) == 1)
    {
      while (!buttonReleased(3))
      {
        projectTimer();
        bevestigd = true;
      }
    }

    projectTimer();

  } while (!bevestigd);

  if (seconden + secondenT + minuten + minutenT == 0)
  {
    printf("\n\nGelieve een timer in te stellen.");
    projectTimer();
    setTimer();
  }

  printf("\n\nDruk op knop 1 om de timer te opnieuw in te stellen.");
  printf("\nDruk op knop 2 om terug naar start te gaan.");
  printf("\nDruk op knop 3 om de timer te starten.");
  bevestigd = false;

  do
  {
    projectTimer();
    if (buttonPushed(1) == 1)
    {
      for (int i = 0; i < 200; i++)
      {
        projectTimer();
        _delay_ms(delay);
      }
      seconden = 0;
      secondenT = 0;
      minuten = 0;
      minutenT = 0;
      setTimer();
    }
    else if (buttonPushed(2) == 1)
    {
      projectTimer();
      startScreen();
    }
    else if (buttonPushed(3) == 1)
    {
      minutenTReset = minutenT;
      minutenReset = minuten;
      secondenTReset = secondenT;
      secondenReset = seconden;
      for (int i = 0; i < 200; i++)
      {
        projectTimer();
        _delay_ms(delay);
      }
      startTimer();
    }
  } while (!bevestigd);
}

void projectTimer()
{
  initDisplay();

  writeNumberToSegment(0, minutenT);
  writeNumberToSegment(1, minuten);
  writeNumberToSegment(2, secondenT);
  writeNumberToSegment(3, seconden);

  if (minutenT > 0)
  {
    enableLed(1);
    enableLed(2);
    enableLed(3);
    enableLed(4);
  }
  if (minuten > 0)
  {
    disableLed(1);
    enableLed(2);
    enableLed(3);
    enableLed(4);
  }

  if (secondenT > 0)
  {
    disableLed(1);
    disableLed(2);
    enableLed(3);
    enableLed(4);
  }
  if (seconden > 0)
  {
    disableLed(1);
    disableLed(2);
    disableLed(3);
    enableLed(4);
  }
  if (minutenT == 0 && minutenT == 0 && minutenT == 0 && minutenT == 0)
  {
    disableLed(1);
    disableLed(2);
    disableLed(3);
    disableLed(4);
  }
}

void startTimer()
{
  printf("\n\nDruk op eender welke knop om de timer te pauzeren.");
  bevestigd = false;
  do
  {
    telAf();

    for (int j = 1; j < 860; j++)
    {
      _delay_ms(delay);
      projectTimer();
      if (buttonPushed(1) == 1 || buttonPushed(2) == 1 || buttonPushed(3) == 1)
      {
        for (int i = 0; i < 200; i++)
        {
          projectTimer();
          _delay_ms(delay);
        }
        bevestigd = true;
      }

      else if (minutenT == 0 && minuten == 0 && secondenT == 0 && seconden == 1)
      {
        bevestigd = true;
      }
    }
  } while (!bevestigd);

  if (minutenT == 0 && minuten == 0 && secondenT == 0 && seconden == 1)
  {
    telAf();
    for (int i = 0; i < 1500; i++)
    {
      projectTimer();
      _delay_ms(delay);
    }

    bevestigd = false;
    initBuzzer();
    int timer = 60;

    printf("\n\nDruk op eender welke knop om het alarm af te zetten.");
    printf("\n(na 1 minuut gaat het alarm vanzelf uit)");
    do
    {
      projectTimer();
      enableAllLeds();
      playTone(500, 550);
      for (int i = 0; i < 500; i++)
      {
        projectTimer();
        _delay_ms(delay);
      }
      disableAllLeds();

      if (buttonPushed(1) == 1 || buttonPushed(2) == 1 || buttonPushed(3) == 1 || timer <= 0)
      {
        for (int i = 0; i < 200; i++)
        {
          projectTimer();
          _delay_ms(delay);
        }
        bevestigd = true;
      }

      timer--;
      if (timer <= 0)
      {
        bevestigd = true;
      }

      projectTimer();
    } while (!bevestigd);

    printf("\n\nDruk op knop 1 om een nieuwe timer in te stellen.");
    printf("\nDruk op knop 2 om de timer opnieuw te starten.");
    printf("\nDruk op knop 3 om naar het startscherm te gaan.");
    bevestigd = false;

    do
    {
      projectTimer();
      if (buttonPushed(1) == 1)
      {
        setTimer();
      }
      else if (buttonPushed(2) == 1)
      {
        seconden = secondenReset;
        secondenT = secondenTReset;
        minuten = minutenReset;
        minutenT = minutenTReset;

        printf("\n\nDruk op eender welke knop om de timer te starten.");
        if (buttonPushed(1) == 1 || buttonPushed(2) == 1 || buttonPushed(3) == 1)
        {
          for (int i = 0; i < 200; i++)
          {
            projectTimer();
            _delay_ms(delay);
          }
          startTimer();
        }
      }
      else if (buttonPushed(3) == 1)
      {
        startScreen();
      }

    } while (!bevestigd);
  }

  else
  {
    projectTimer();
    printf("\n\nDruk op knop 1 om de timer te starten.");
    printf("\nDruk op knop 2 om de timer te resetten.");
    printf("\nDruk op knop 3 om de timer te stoppen.");

    bevestigd = false;

    do
    {
      projectTimer();
      if (buttonPushed(1) == 1)
      {
        _delay_ms(500);
        startTimer();
      }
      else if (buttonPushed(2) == 1)
      {
        for (int i = 0; i < 200; i++)
        {
          projectTimer();
          _delay_ms(delay);
        }
        minuten = minutenReset;
        minutenT = minutenTReset;
        seconden = secondenReset;
        secondenT = secondenTReset;

        printf("\n\nDruk op knop 1 om de timer te starten.");
        printf("\nDruk op knop 2 om de timer te opnieuw in te stellen.");
        bevestigd = false;

        do
        {
          projectTimer();
          if (buttonPushed(1) == 1)
          {
            for (int i = 0; i < 200; i++)
            {
              projectTimer();
              _delay_ms(delay);
            }
            startTimer();
          }

          else if (buttonPushed(2) == 1)
          {
            for (int i = 0; i < 200; i++)
            {
              projectTimer();
              _delay_ms(delay);
            }
            seconden = 1;
            secondenT = 0;
            minuten = 0;
            minutenT = 0;
            setTimer();
          }
        } while (!bevestigd);

        startTimer();
      }
      else if (buttonPushed(3) == 1)
      {
        for (int i = 0; i < 200; i++)
        {
          projectTimer();
          _delay_ms(delay);
        }
        bevestigd = true;
      }
    } while (!bevestigd);
  }
  startScreen();
}

void telAf()
{

  if (minutenT > 0 && minuten == 0 && secondenT == 0 && seconden == 0)
  {
    minutenT--;
    minuten = 9;
    secondenT = 5;
    seconden = 9;
  }

  else if (minutenT >= 0 && minuten > 0 && secondenT == 0 && seconden == 0)
  {
    minuten--;
    secondenT = 5;
    seconden = 9;
  }

  else if (minutenT >= 0 && minuten >= 0 && secondenT > 0 && seconden == 0)
  {
    secondenT--;
    seconden = 9;
  }

  else if (minutenT >= 0 && minuten >= 0 && secondenT >= 0 && seconden > 0)
  {
    seconden--;
  }
}

void startScreen()
{
  initDisplay();
  
  seconden = 0;
  secondenT = 0;
  minuten = 0;
  minutenT = 0;
  printf("\n\nHou eender welke knop ingedrukt om een timer in te stellen.");
  bevestigd = false;

  do
  {

    if (buttonPushed(1) == 0 || buttonPushed(2) == 0 || buttonPushed(3) == 0)
    {
      scrollingText("TIMER ");
    }

    if (buttonPushed(1) == 1 || buttonPushed(2) == 1 || buttonPushed(3) == 1)
    {
      bevestigd = true;
    }

  } while (!bevestigd);
  setTimer();
}

int main(void)
{
  initUSART();
  initDisplay();

  startScreen();
}