#include <avr/io.h>
#include <stdlib.h>
#include <usart.h>
#include <util/delay.h>
#include <string.h>

typedef struct {
  int waarde;
  char* kleur; //opgelet: pointer, want we willen juist genoeg reserveren
} KAART;

void vulBoek(KAART* boek) {
  char kleuren[4][10] = {"harten", "ruiten", "schoppen", "klaveren"};
  int index;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13; j++) {
      index = (i * 13) + j;
      //TODO: gebruik malloc om juist genoeg ruimte te reserveren voor de kleur
      //TODO: kopieer de kleur naar de gealloceerde ruimte
      //TODO: stel de waarde van de kaart in
    }
  }
}

// OPGELET: er komt een adres van een KAART binnen:
void toonKaart(KAART* deKaart) {
  switch (deKaart->waarde) {
    //TODO: pas onderstaande code aan:
    case 1:
      printf("%s aas", deKaart->kleur);
      break;
    case 11:
      printf("%s boer", deKaart->kleur);
      break;
    case 12:
      printf("%s dame", deKaart->kleur);
      break;
    case 13:
      printf("%s heer", deKaart->kleur);
      break;
    default:  // alle andere kaarten:
      printf("%s %d", deKaart->kleur, deKaart->waarde);
  }
}

// OPGELET: de returnwaarde is een pointer!
KAART* trekKaart(KAART boek[]) {
  int willek = rand() % 52;
  //TODO: retourneer het adres van de willekeurige kaart
  return;
}

int main() {
  initUSART();
  //TODO: Gebruik calloc om de boek kaarten aan te maken
  vulBoek(boek);

  // TODO: pas onderstaande code aan zodat ze compileert
  for (int i = 0; i < 10; i++) {
    KAART kaart = trekKaart(boek);
    toonKaart(kaart);
    printf("\n");
  }

  //TODO: geef alle dynamisch gereserveerde ruimte weer vrij:

  return 0;
}