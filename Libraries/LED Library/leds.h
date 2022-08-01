#include <avr/io.h>
#include <util/delay.h>

#define NUMBER_OF_LEDS 4

void enableLed(int ledNumber);

void enableMultipleLeds(uint8_t leds);

void enableAllLeds();



void disableLed(int ledNumber);

void disableMultipleLeds(uint8_t leds);

void disableAllLeds();


void lightUpLed(int ledNumber);

void lightUpLeds(uint8_t leds);

void lightUpAllLeds();


void lightDownLed(int ledNumber);

void lightDownLeds(uint8_t leds);

void lightDownAllLeds();


void lightInverseOneLed(int ledNumber);

void movingLedAnimation(int loops, int speed);

void dimLed(int ledNumber, int percentage, int duration);

void fadeInLed(int ledNumber, int duration);

void countdown();