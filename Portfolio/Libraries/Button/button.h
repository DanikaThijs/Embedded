#include <avr/io.h>

void enableButton(int); // het meest linkse knopje op je shield = button 1
void disableButton(int);
void enableMultipleButtons(uint8_t);
void enableAllButtons ();
void disableAllButtons ();
int buttonPushed(int); // het meest linkse knopje op je shield = button 1
int multipleButtonsPushed (uint8_t);
int allButtonsPushed ();
int buttonReleased(int); // het meest linkse knopje op je shield = button 1
int multipleButtonsReleased (uint8_t);
int allButtonsReleased ();