#include "spedenpelitmusiikki.h"
#include "pitches.h" // noteja varten

int buzzer = 13; // määritellään muuttuja buzzer ja määritellään se pinniin 13
unsigned long nollaus = 0;
int kesto = 0;
long aaniViive = 0;

int melody2[] = {
  NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5,
  NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_C5,
  NOTE_C6, NOTE_G6, NOTE_E6, NOTE_C6, NOTE_G6, NOTE_E6,
  
  NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_B5,
  NOTE_FS5, NOTE_DS5, NOTE_DS5, NOTE_E5, NOTE_F5,
  NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_B5
};

int durations2[] = {
  16, 16, 16, 16,
  32, 16, 8, 16,
  16, 16, 16, 32, 16, 8,
  
  16, 16, 16, 16, 32,
  16, 8, 32, 32, 32,
  32, 32, 32, 32, 32, 16, 8
  
};


int notes[] = { //häviö ja voitto musiikki taajuudet
  784, 740, 698, 659, 
  587, 523,           
  466, 392   
};

int durations[] = { //häviö ja voitto musiikki kunkin taajuuden kesto
  200, 200, 200, 200,
  300, 300,
  400, 600
};


int size = sizeof(durations2) / sizeof(int); //  melodia
int length = sizeof(notes) / sizeof(int); // häviö ja voitto


void aloitus(){
pinMode(buzzer, OUTPUT); // laitetaan buzzer outputiks, kutsutaan pääohjelman setupis
}


void menuMusiikki(int whatSong) {

  if (whatSong == 2) // häviö musiikki
  {
    for (int i = 0; i < length; i++) 
    {
      tone(buzzer, notes[i]); // soitetaan nuotti, riippuen siitä mikä "i" on, idea on soittaa kaikki nuotit yksitellen
      delay(durations[i]);
      noTone(buzzer);       // lopettaa musiikin
      delay(20);    // tässä on käytetty delayta koska soi vain kerran ja on lyhyt       
    }
  }

  else if (whatSong == 3)
  {
    for (int i = length - 1; i >= 0; i--) 
    {  // tämä käyttää samoja taajuuksia ja kestoa kuin ylempi mutta vain käännettynä
      tone(buzzer, notes[i]); // Käytetään notes-taulukkoa
      delay(durations[i]);   // Käytetään durations-taulukkoa
      noTone(buzzer);       
      delay(20);            
    }
  }

  else 
  {
    // menu
    // käytetty millis ettei musiikki keskeytä koko muuta ohjelmaa
    if(millis() - nollaus >= aaniViive) // katsoo milloin seuraava nuotti soitetaan
      {
      
        
        if (kesto < size)
        {
          
          int duration = 1000 / durations2[kesto]; // durations2 ei anna kestoa suoraan millisekuntteina niin muutetaan millisekunteiksi
          aaniViive = duration * 2; // laittaa viiveen seuraavalle nuotille
          tone(buzzer, melody2[kesto], duration); // soittaa nuotin riippuen siitä montako kierrosta if lause pyörinyt

          nollaus = millis(); // "nollataan" nollaus  

          kesto ++; // lisätään kestoa jotta soittaa seuraavan nuotin
        }
          else 
          {
            kesto = 0; // biisi soitettu loppuun niin nollataan ajastin ja aloitetaan toinen if lause nollaamalla kesto
            nollaus = millis();// "nollataan" nollaus
            
          }
      }
    }
}


void nappiMusiikki(int napit){
 // nappien ääniefektit
 // soittaa eri ääniefektin riippuen parametristä
 // funktiota kutsutaan kun nappia painetaan, napeilla eri ääniefektit
switch (napit){

case 2: 
tone(buzzer, 250, 100); // jos nappia 1 painettu tämä ääniefekti soi
break;

case 3:
tone(buzzer, 350, 100); // jos nappia 2 painettu tämä ääniefekti soi
break;

case 4:
tone(buzzer, 450, 100); // jos nappia 3 painettu tämä ääniefekti soi
break;

case 5:
tone(buzzer, 550, 100); // jos nappia 4 painettu tämä ääniefekti soi
break;

default:
 // jos jotain muuta painettu niin mitään ei tapahdu
break;

}
}

