#define __DELAY_BACKWARD_COMPATIBLE__
#include "display.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* Segment byte maps for numbers 0 to 9 */
const uint8_t SEGMENT_MAP[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99,
                               0x92, 0x82, 0xF8, 0X80, 0X90};

const uint8_t ALPHABET_MAP[] = {0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 0xC2, 0x89, 0xCF, 0xE1, 0x8A, 0xC7,
                                0xEA, 0xC8, 0xC0, 0x8C, 0x4A, 0xCC, 0x92, 0x87, 0xC1, 0xC1, 0xD5, 0x89, 0x91, 0xA4};

const uint8_t LOOP[] = {0xFE, 0xFE, 0xFE, 0xFE, 0xFD, 0xFB, 0xF7, 0xF7, 0xF7, 0xF7, 0xEF,
                        0xDF};

const uint8_t LOOP_SEGMENTS[] = {0xF1, 0xF2, 0xF4, 0xF8, 0xF8, 0xF8, 0xF8, 0xF4, 0xF2, 0xF1, 0xF1, 0xF1};

const uint8_t SPACE = 0xFF;
const uint8_t LINE = 0xBF;

/* Byte maps to select digit 1 to 4 */
const uint8_t SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};

void initDisplay()
{
  sbi(DDRD, LATCH_DIO);
  sbi(DDRD, CLK_DIO);
  sbi(DDRB, DATA_DIO);
}

// loop through seven segments of LED display and shift the correct bits in the
// data register
void shift(uint8_t val, uint8_t bitorder)
{
  uint8_t bit;

  for (uint8_t i = 0; i < NUMBER_OF_SEGMENTS; i++)
  {
    if (bitorder == LSBFIRST)
    {
      bit = !!(val & (1 << i));
    }
    else
    {
      bit = !!(val & (1 << (7 - i)));
    }
    // write bit to register
    if (bit == HIGH)
      sbi(PORTB, DATA_DIO);
    else
      cbi(PORTB, DATA_DIO);

    // Trigger the clock pin so the display updates
    sbi(PORTD, CLK_DIO);
    cbi(PORTD, CLK_DIO);
  }
}

// Schrijft cijfer naar bepaald segment. Segment 0 is meest linkse.
void writeNumberToSegment(uint8_t segment, uint8_t value)
{
  cbi(PORTD, LATCH_DIO);
  shift(SEGMENT_MAP[value], MSBFIRST);
  shift(SEGMENT_SELECT[segment], MSBFIRST);
  sbi(PORTD, LATCH_DIO);
}

// Schrijft getal tussen 0 en 9999 naar de display. Te gebruiken in een lus...
void writeNumber(int number)
{
  if (number < 0 || number > 9999)
    return;
  writeNumberToSegment(0, number / 1000);
  writeNumberToSegment(1, (number / 100) % 10);
  writeNumberToSegment(2, (number / 10) % 10);
  writeNumberToSegment(3, number % 10);
}

// Schrijft getal tussen 0 en 9999 naar de display en zorgt dat het er een bepaald aantal milliseconden blijft staan.
// Opgelet: de timing is "ongeveer", er wordt geen rekening gehouden met de tijd writeNumberToSegment in beslag neemt...
void writeNumberAndWait(int number, int delay)
{
  if (number < 0 || number > 9999)
    return;
  for (int i = 0; i < delay / 20; i++)
  {
    writeNumberToSegment(0, number / 1000);
    _delay_ms(5);
    writeNumberToSegment(1, (number / 100) % 10);
    _delay_ms(5);
    writeNumberToSegment(2, (number / 10) % 10);
    _delay_ms(5);
    writeNumberToSegment(3, number % 10);
    _delay_ms(5);
  }
}

void writeNumberToSegmentAndWait(int number, uint8_t segment, int delay)
{
  if (number < 0 || number > 10)
    return;
  for (int i = 0; i < delay / 5; i++)
  {
    writeNumberToSegment(segment, number);
    _delay_ms(5);
  }
}

void writeCharToSegment(uint8_t segment, char character)
{
  // Controleer het character dat binnenkomt: als het een kleine letter is, converteer dan naar een hoofdletter (door er 32 af te trekken).
  if (character >= 97 && character <= 122)
  {
    character -= 32;
    cbi(PORTD, LATCH_DIO);
    shift(ALPHABET_MAP[character - 65], MSBFIRST);
    shift(SEGMENT_SELECT[segment], MSBFIRST);
    sbi(PORTD, LATCH_DIO);
  }
  // Als er nummers tussen zitten
  else if (character >= 48 && character <= 57)
  {
    writeNumberToSegment(segment, (int)(character - 48));
  }
  else if (character == 45)
  {
    cbi(PORTD, LATCH_DIO);
    shift(LINE, MSBFIRST);
    shift(SEGMENT_SELECT[segment], MSBFIRST);
    sbi(PORTD, LATCH_DIO);
  }
  else if (character < 64 || character > 122)
  {
    cbi(PORTD, LATCH_DIO);
    shift(SPACE, MSBFIRST);
    shift(SEGMENT_SELECT[segment], MSBFIRST);
    sbi(PORTD, LATCH_DIO);
  }
  else
  {
    cbi(PORTD, LATCH_DIO);
    shift(ALPHABET_MAP[character - 65], MSBFIRST);
    shift(SEGMENT_SELECT[segment], MSBFIRST);
    sbi(PORTD, LATCH_DIO);
  }
}
void writeString(char *str)
{
  int stringLenght = strlen(str);
  if (stringLenght > 4)
  {
    for (int i = 0; i < 4; i++)
    {
      writeCharToSegment(i, str[i]);
    }
  }
  else
  {
    for (int i = 0; i < strlen(str); i++)
    {
      writeCharToSegment(i, str[i]);
    }
  }
}

void writeStringAndWait(char *str, int delay)
{
  for (int i = 0; i < delay / 20; i++)
  {
    writeCharToSegment(0, str[0]);
    _delay_ms(5);
    writeCharToSegment(1, str[1]);
    _delay_ms(5);
    writeCharToSegment(2, str[2]);
    _delay_ms(5);
    writeCharToSegment(3, str[3]);
    _delay_ms(5);
  }
}

void loopAnimation(int loops)
{
  loops *= 12;
  for (int i = 0; i < loops; i++)
  {
    cbi(PORTD, LATCH_DIO);
    shift(LOOP[i % 12], MSBFIRST);
    shift(LOOP_SEGMENTS[i % 12], MSBFIRST);
    sbi(PORTD, LATCH_DIO);
    _delay_ms(50);
  }
}

void loading(int duration)
{
  int tiental = 0;
  for (int i = 0; i < duration; i++)
  {
    writeNumberToSegmentAndWait(i, 0, 50);
    _delay_ms(5);
    writeNumberToSegmentAndWait(i, 1, 50);
    _delay_ms(5);
  }
}

void scrollingText(char *str)
{
  size_t arrayLength = strlen(str);
  size_t i = 0;
  while (i < arrayLength)
  {
    int j = 0;
    while (j < 20)
    {
      writeCharToSegment(0, str[i]);
      _delay_ms(5);
      writeCharToSegment(1, str[(i + 1) % arrayLength]);
      _delay_ms(5);
      writeCharToSegment(2, str[(i + 2) % arrayLength]);
      _delay_ms(5);
      writeCharToSegment(3, str[(i + 3) % arrayLength]);
      _delay_ms(5);
      j++;
    }
    i++;
  }
}

void writeNumberToTwoSegments(int choise, int number)
{
  if (number < 0 || number > 99)
    return;
  // als de keuze 0 is gaat het het nummer op de linkse 2 dinge zetten  we gaan ook controleren of het nummer erop past
  if (choise == 0)
  {
    writeNumberToSegment(0, (number / 10) % 10);
    writeNumberToSegment(1, number % 10);
  }
  else if (choise == 1)
  {
    writeNumberToSegment(2, (number / 10) % 10);
    writeNumberToSegment(3, number % 10);
  }
}
