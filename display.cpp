#include "display.h"

void initializeDisplay(void)
{
// See requirements for this function from display.h
pinMode(n_reset, OUTPUT);     //12 reset = tyhjentää siirtorekisterin datan kun se pulssitetaan eli LOW -> HIGH
pinMode(n_shift, OUTPUT);     //11 shiftClock = kellopulssi joka siirtää yksittäisen bitin rekisteriin
pinMode(n_latch, OUTPUT);     //10 latchClock = kopio siirretyn datan näytöille
pinMode(n_enable, OUTPUT);    //9 outEnable = ohjaa näyttöjä päälle ja pois päältä  
pinMode(n_input, OUTPUT);     //8 serialInput = siirtorekisterin datalinja joka siirtää bitit yks kerrallaan

//idle moodi jossa resettiä pidetään HIGH
digitalWrite(n_reset, HIGH);
digitalWrite(n_shift, LOW);
digitalWrite(n_latch, LOW);
digitalWrite(n_enable, LOW);
digitalWrite(n_input, LOW);

//Resetoi/tyhjentää siirtorekisterin
digitalWrite(n_reset, LOW);
delay(10);
digitalWrite(n_reset, HIGH);

//pulssi LATCH:n joka näyttää tyhjennetyt luvut näytöllä
digitalWrite(n_latch, HIGH);
digitalWrite(n_latch, LOW);
}


void writeByte(uint8_t number ,bool last)
{
// See requirements for this function from display.h
//muuttaa numeron 0-9 välillä bittikoodiksi
uint8_t n_bitit;  //muuttuja johon tallennetaan numeron 7 segment bitti

    //sytyttää tietyt 7 segment näytön segmentit a, b, c, d, e, f joiden avulla näytöille tulee tietty numero
  switch (number) {
    case 0:  n_bitit = 0b00111111;  //näyttää 0
    break;
    case 1:  n_bitit = 0b00000110;  //näyttää 1
    break;
    case 2:  n_bitit = 0b01011011;  //näyttää 2
    break;
    case 3:  n_bitit = 0b01001111;  //näyttää 3
    break;
    case 4:  n_bitit = 0b01100110;  //näyttää 4
    break;
    case 5:  n_bitit = 0b01101101;  //näyttää 5
    break;
    case 6:  n_bitit = 0b01111101;  //näyttää 6
    break;
    case 7:  n_bitit = 0b00000111;  //näyttää 7
    break;
    case 8:  n_bitit = 0b01111111;  //näyttää 8 
    break;
    case 9:  n_bitit = 0b01101111;  //näyttää 9
    break;
    default: n_bitit = 0b01000000;  //jos numero ei ole mikään 0-9 sen arvoksi asetetaan keskelle viiva eli virhemerkki
    break;
  }

  //siirtää 7 segmentin bittikuvan eli numeron siirtorekisteriin bitti kerrallaan oikealle
  for (int bitti = 7; bitti >= 0; bitti--) {  //aloittaa korkeimmasta bitistä (MSB) ja menee siitä alaspäin (LSB)
    uint8_t mask = (n_bitit >> bitti) & 0x01; //käsittelee yhden bitin kerralla, siirrettään oikealle ja luetaan bitit, eli bitti = x kertoo montako kertaa pitää siirtyä oikealle ja AND operaatio lukee viimeisen merkin 0 tai 1
    digitalWrite(n_input, mask);  //laittaa bitin siirtorekisterin datalinjalle
    digitalWrite(n_shift, HIGH);  //rekisteri lukee datalinjan arvon
    digitalWrite(n_shift, LOW); //rekisteri siirtyy seuraavaan bittipaikkaan
  }

  //kun kaikki bitit on siirretty se päivittää tämän näytölle
  if (last) {
    digitalWrite(n_latch, HIGH);  //Kopio siirtorekisterin tiedon ulostuloihin
    digitalWrite(n_latch, LOW);   //menee takas LOW odottamaan
  }
}


void writeHighAndLowNumber(uint8_t tens,uint8_t ones)
{
// See requirements for this function from display.h
//Syöttää kymmenesluvut ja ykkösluvut siirtorekisteriin
writeByte(tens, false); //kirjoittaa kymmenesluvut siirtorekisteriin ilman latchia eli numerot ei päivity näytölle viellä 
writeByte(ones, true);  //kirjoittaa ykkösluvut ja latchaa ne lopuksi milloin molemmat numerot näkyvät näytöllä yhtä aikaa
}

void showResult(byte result)
{
// See requirements for this function from display.h
    //Rajoittaa pistemäärän 99 koska se on maksimi pistemäärä jonka näytöillä voi näyttää
    if (result > 99) result = 99;

    //laskee kymmenesluvut ja ykkösluvut erikseen jotta ne voi tulostaa 7-segment näytöille
    uint8_t tens = result / 10; //jakaa luvun 10 jotta voidaan erottaa kymmenesluvut kokonaisluvusta esim. 42 / 10 = 4
    uint8_t ones = result % 10; //jakojäännös jättää jäljelle vain ykkösluvut jolla ne erottuu kymmenesluvuista esim. 42 % 10 = 2

    writeHighAndLowNumber(tens, ones);  //näyttää kaksi lukua näytöillä
}

