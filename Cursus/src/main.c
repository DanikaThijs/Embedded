#include <display.h>
#include <button.h>
#include <util/delay.h>
#include <usart.h>

int main(){
    initDisplay();
    initUSART();
    enableButton(1);
    float pagina = 0;
    while (1)
    {
        if (buttonPushed(1) == 1)
        {
            pagina++;
            writeNumberAndWait(pagina,200);
        }
        writeNumber((pagina/251)*100);
    }
}