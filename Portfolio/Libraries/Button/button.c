#include <avr/io.h>

#define NUMBER_OF_BUTTONS 3

void enableButton(int button){
    if(button < 1 || button > NUMBER_OF_BUTTONS) return;
    DDRC &= ~(1<<(PC1 + (NUMBER_OF_BUTTONS-button)));
    PORTC |= (1<<(PC1 + (NUMBER_OF_BUTTONS-button)));
}

void disableButton(int button){
    if(button < 1 || button > NUMBER_OF_BUTTONS) return;
    DDRC &= ~(0<<(PC1 + (NUMBER_OF_BUTTONS-button)));
    PORTC |= (0<<(PC1 + (NUMBER_OF_BUTTONS-button)));
}

void enableMultipleButtons(uint8_t buttons){
    if(buttons / ((uint8_t) pow(2,NUMBER_OF_BUTTONS + PC1)) > 0 || buttons % ((uint8_t) pow(2,PC1)) > 0) return;
    DDRC &= buttons;
    PORTC |= ~buttons;
}

void enableAllButtons(){
    DDRC &= 0b11110001;
    PORTC |= 0b00001110;
}

void disableAllButtons (){
    DDRC &= 0b00001110;
    PORTC |= 0b11110001;
}

int buttonPushed(int button){
    if(button < 1 || button > NUMBER_OF_BUTTONS) return;
        if ((PINC & (1 << (PC1 + button - 1))) == 0 ) {
            return 1;
        } else {
            return 0;
        }
}
//int multipleButtonsPushed (uint8_t buttons){
//    if(buttons / ((uint8_t) pow (2,NUMBER_OF_BUTTONS)))

//}
int allButtonsPushed (){
    PORTC |= 0b00001110;
}
int buttonReleased(int button){
    return 1 - buttonPushed(button);
}
int multipleButtonsReleased (){
    return 1 - allButtonsPushed();
}
int allButtonsReleased (){
    PORTC = 0b00000000;
}