#define bool fuelOk;
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

int currentSpeed = 100; //  snelheid - m/s  (meter per seconde)
float gravity = 1.622;  // versnelling – m/s² (
int distance = 500;     // afstand tot het maanoppervlak in meter – m
int fuelReserve = 375;  // liter
int burst = 0;
int counter = 0;
bool fuelOk = true;

void initTimer()
{
  TCCR0A |= _BV(WGM00) | _BV(WGM01); // Fast PWM Mode
  TCCR0B |= _BV(CS02) | _BV(CS00);   // prescalerfactor is nu 1024
  TIMSK0 |= _BV(TOIE0);              // overflow interrupt enablen
  TIMSK0 |= _BV(OCIE0A);             // OCRA interrupt enablen
  OCR0A = 128;
  sei();
}

// deze ISR runt telkens wanneer TCNT0 gelijk is aan de waarde in het OCRA-register
ISR(TIMER0_COMPA_vect)
{
}

// deze ISR runt telkens wanneer TCNT0 gelijk is aan de waarde TOP-waarde (255)
ISR(TIMER0_OVF_vect)
{
  counter++;
  if (buttonPushed(2) == 1)
  {
    burst++;
  }
}

void checkFuel()
{
  if (fuelReserve <= 0)
  {
    printf("\n------------------------------------");
    printf("\n\nSpaceX HLS 1.0 has ran out of fuel");
    printf("\n------------------------------------");
    fuelOk = false;
  }
  else if (fuelReserve <= 375)
  {
    initBuzzer();
    playTone(100, 1);
  }

  return;
}

void showParameters()
{
  writeNumber(distance);
  if (fuelReserve > 750 && fuelReserve < 1125)
  {
    lightDownLed(1);
  }
  else if (fuelReserve > 375 && fuelReserve < 750)
  {
    lightDownLed(2);
  }
  else if (fuelReserve > 0 && fuelReserve < 375)
  {
    lightDownLed(3);
  }
  else if (fuelReserve < 0)
  {
    lightDownLed(4);
  }

  if (burst >= 50)
  {
    burst = 50;
  }
}

void checkSafeLanding()
{
  if (distance <= 3 && currentSpeed <= 5)
  {
    initBuzzer();
    playTone(500, 200);
    delay(200);
    playTone(500, 200);
    delay(200);
    playTone(500, 200);
    delay(200);
    playTone(800, 150);
    delay(150);
    playTone(500, 500);
    delay(500);
    playTone(600, 1000);
    delay(1000);

    printf("\n------------------------------------------");
    printf("\n\nSpaceX HLS 1.0 landed safely on the moon");
    printf("\n------------------------------------------");
  }
  else
  {

    initBuzzer();
    playTone(500, 200);
    delay(200);
    playTone(500, 200);
    delay(200);
    playTone(500, 200);
    delay(200);
    playTone(800, 150);
    delay(150);
    playTone(500, 500);
    delay(500);
    playTone(600, 1000);
    delay(1000);

    printf("\n------------------------");
    printf("\n\nSpaceX HLS 1.0 crashed");
    printf("\n------------------------");
  }
}

struct SecondData
{
  int currentSpeedData;
  int distanceData;
  int burstData;
  int fuelReserveData;
};

int main(void)
{
  initDisplay();
  enableAllLeds();
  lightUpAllLeds();
  initUSART();
  initTimer();

  // controleren van de brandstof

  while (distance > 0)
  {
    showParameters();
    if (counter % 61 == 0)
    {
      checkFuel();
      currentSpeed += gravity - burst / 5;
      distance -= currentSpeed;
      fuelReserve -= burst;
      printf("\n\n\nSpaceX HLS 1.0");
      printf("\nSecond %d", (counter / 61));
      printf("\n--------------");
      printf("\nCurrent Speed: %d\nDistance: %d\nFuel reserve: %d\nBurst: %d", currentSpeed, distance, fuelReserve, burst);
      burst = 0;
    }
  }
  checkSafeLanding();
}