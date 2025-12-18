#include <LiquidCrystal_I2C.h>
#include "lcd_1.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); //0x27 pinnin väylä, 16 montako merkkiä rivillä ja 2 on montako riviä näytöllä

void lcdInit() {
    lcd.init();                     //Käynnistää lcd näytön
    lcd.backlight();                //Käynnistää lcd takavalon
    lcd.clear();                    //Tyhjentää merkit näytöltä

    //Ei tarvita (todennäköisesti)
    /*lcd.setCursor(0,0);             //Valitsee kummalle riville teksti tulee, tässä tilanteessa 0,0 eli ylempään riviin
    lcd.print("Welcome");           //Ylemmän rivin teksti
    lcd.setCursor(0,1);             //valitsee kummalle riville teksti tulee, tässä tilanteessa 0,1 eli alempaan riviin
    lcd.print("Speden Spelit");     //alemman rivin teksti*/
}

void lcdShowMenu() {
    lcd.clear();                    //Tyhjentää merkit näytöltä
    lcd.setCursor(0,0);             //valitsee kumpi rivi
    lcd.print("Valitse moodi");       //rivin teksti
    lcd.setCursor(0,1);
    lcd.print("1=muisti 2=reaktio");
}

//Ei tarvi
/*void lcdScroll()    {   //Scrollaa tekstiä oikealta vasemmalle
    delay(300);         //Millä nopeudella näyttö scrollaa
    lcd.scrollDisplayleft();
}*/

void lcdShowMode(int modeName, int highscore_1st, int highscore_2nd, int highscore_3rd) {
    lcd.clear();

    //Ylärivin teksti
    lcd.setCursor(0, 0);
    if (modeName == 1) {    //JOS modeName == 1 printtaa "Muistipeli", muuten printtaa "Reaktiopeli"
        lcd.print("Muistipeli");
    } else {
        lcd.print("Reaktiopeli");
    }

    String line = "Highscore top 3: ";      //Teksti jossa on top 3 highscoret
    line += String(highscore_1st) + ", ";   //lisää tekstiin ensimmäisen highscoren sekä pilkun ja välilyönnin
    line += String(highscore_2nd) + ", ";   //lisää tekstiin toisen highscoren sekä pilkun ja välilyönnin
    line += String(highscore_3rd);          //lisää tekstiin kolmanne highscoren

    //Teksti printataan normaalisti jos teksti on pienempi tai yhtäsuuri kuin 16 koska LCD näytössä on 16 merkkiä rivillä
    if (line.length() <= 16) {
        lcd.setCursor(0, 1);
        lcd.print(line);    //printtaa tekstin normaalisti näytölle
        return; //lopettaa funktion jotta se ei ala scrollaamaan turhaan
    }

    //JOS teksti on pidempi kuin 16 merkki se alkaa scrollaamaan siten että se poistaa ensimmäisen merkin ja siirtää kaikkia muita merkkejä yhdellä vasemmalle samalla kun se lisää uuden merkin oikeaanlaitaan
    for (int scroll = 0; scroll <= line.length() - 16; scroll++) {  //scroll kertoo mistä kohtaa tekstin pitää näkyä näytöllä, line.length kertoo koodille kokonaisen tekstin koon ja -16 varmistaa että koodi ei ohita tekstiä
        lcd.setCursor(0, 1);
        lcd.print(line.substring(scroll, scroll + 16)); //näyttää 16 merkin pituisen tekstin näytöllä 
        delay(300);  // scrollausnopeus
    }
}


void lcdNewHighscore(int highscore) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Uusi Ennätys: ");    //printtaa highscoren arvon hakemalla tämän tiedon "highscore" muuttujasta
    lcd.print(highscore);           //highscore muuttuja mistä koodi saa sen arvon
    lcd.setCursor(0, 1);
    lcd.print("Paina nappi 5");
}   

void lcdShowStart(int modeName) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Peli alkaa");
    lcd.setCursor(0,1);
    if (modeName == 1)              //JOS modeName == 1 printtaa "Muistipeli", muuten printtaa "Reaktiopeli"
    {
        lcd.print("Muistipeli"); 
    }
    else
    {
        lcd.print("Reaktiopeli");
    }
}

void lcdShowGameOver() {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Womp Womp");
    lcd.setCursor(0,1);
    lcd.print("Paina nappi 5");
}

void lcdYouWon() {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sait 100 Voitit!");
    lcd.setCursor(0,1);
    lcd.print("Paina nappi 5");
}