#include "leds.h"

const int pin[4] = {A2,A3,A4,A5};
void initializeLeds()
{

// see requirements for this function from leds.h

for (int i = 0; i < 4; i++){
pinMode(pin[i], OUTPUT);
// laittaa ledien pinmodet outputtiin että ledit voivat syttyä
// menee pääohjelman setuppiin
}
}

void setLed(byte ledNumber)
{
  
// see requirements for this function from leds.h

digitalWrite(pin[ledNumber-2], HIGH);
// sytyttää parametrissä kutsutun ledin
// -2 on tässä koska pääohjelmassa kutsutaan 2-5
}


void clearAllLeds()
{
// see requirements for this function from leds.h

 for(int i = 0; i < 4; i++ ){
 digitalWrite(pin[i], LOW);
// sammuttaa kaikki ledit
// kutsutaan kun pitää sammuttaa ledit

}
}

void setAllLeds()
{
  
// see requirements for this function from leds.h

for(int i = 0; i < 4; i++ ){
digitalWrite(pin[i], HIGH);
// sytyttää kaikki ledit
}
}


void show1()
{
  uint8_t numero = 0b0000;
  // määritellään muuttuja numero, jossa pidetään lukua 1-15
for(int i = 0; i<15; i++){
  clearAllLeds();
  //sulkee edellisen kierroksen ledit
  numero += 1;
  //joka kierroksella lisätään muuttujaan "numero" 1, laskeminen alkaa ykkösestä
  uint8_t ledi1 = (numero >> 0) & 1;  
  // siirtää kaikkia bittejä 0 kertaa oikealle, jos lsb * 1 = 1 niin palauttaa 1, muuten palauttaa 0
  uint8_t ledi2 = (numero >> 1) & 1;
    // siirtää kaikkia bittejä 1 kertaa oikealle, jos lsb * 1 = 1 niin palauttaa 1, muuten palauttaa 0
  uint8_t ledi3 = (numero >> 2) & 1;
    // siirtää kaikkia bittejä 2 kertaa oikealle, jos lsb * 1 = 1 niin palauttaa 1, muuten palauttaa 0
  uint8_t ledi4 = (numero >> 3) & 1;  
    // siirtää kaikkia bittejä 3 kertaa oikealle, jos lsb * 1 = 1 niin palauttaa 1, muuten palauttaa 0

  uint8_t ledi[4] = {ledi1, ledi2, ledi3, ledi4};
  // tallennetaan ledi1-4 tiedot taulukkoon, olis voinut tehdä alunperinkin taulukkoon mutta noh

  for(int i = 0; i < 4; i++ ){
  if (ledi[i] == 1){
  
  setLed(i+2);
  // tarkistaa kaikki ledit yksitellen, jos ledi on yhtäkuin 1 niin ledi syttyy
  }
}
  delay(1500);
  // delay jotta ledit pysyvät hetken päällä niin ehtii lukea 
  
}
// see requirements for this function from leds.h
}


void show2(int rounds)
{
  int viive = 700;
  // määritellään muuttuja "viive" 
  for(rounds > 0; rounds--;)
{
  viive -= 100;
  // joka kierroksella viivettä pienennetään jotta tahti nopeutuu
  // yksi kierros = kaikki ledit välähtäneet kerran
  for(int i = 0; i < 4; i++)
    {
    setLed(i+2);
    // sytyttää ledit vuoronperään, +2 koska ssetled vähetää -2
    delay(viive);
    clearAllLeds();
    // sammuttaa ledin
    }
}

// see requirements for this function from leds.h  
}