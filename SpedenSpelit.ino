#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

volatile int buttonNumber = -1;
volatile bool newTimerInterrupt = false;



byte randomarray[100]; 
byte gameRound = 0; 
byte playerStep = 0; 
byte peliAlkoi = 0;
byte memorygame=0;
byte speedgame=0;

void setup()
{
  randomSeed(analogRead(A0));
  Serial.begin(9600);
  initButtonsAndButtonInterrupts();
  initializeLeds();
}

void loop()
{
  // --- STATE 1: GAME IS NOT RUNNING (Menu Mode) ---
  if(peliAlkoi == 0)
  {
    // ONLY check for menu buttons here
    int buttonPressed = whatButtonPressed();

    if(buttonPressed == 2) {
       memorygame = 1;
       speedgame = 0;
       Serial.println("Mode: Memory Game");
    }
    if(buttonPressed == 3) {
       memorygame = 0;
       speedgame = 1;
       Serial.println("Mode: Speed Game");
    }

    // Start Button (Button 6)
    if(buttonPressed == 6) {
      if(memorygame == 1 || speedgame == 1) {
         startTheGame();
      } else {
         Serial.println("Select mode first (Btn 2 or 3)");
      }
    }
  }

  // --- STATE 2: GAME IS RUNNING ---
  else // (peliAlkoi == 1)
  {
    // We do NOT call whatButtonPressed() here. 
    // We let the specific game functions handle their own inputs.
    
    if(memorygame == 1) {
      memoryGame();
    }
    // if(speedgame == 1) { speedGame(); }
  }
}

void initializeTimer(void)
{
  // see requirements for the function from SpedenSpelit.h
}
ISR(TIMER1_COMPA_vect)
{
  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */
  
}


void checkGame(byte nbrOfButtonPush)
{
  // see requirements for the function from SpedenSpelit.h
}


void initializeGame()
{
  // see requirements for the function from SpedenSpelit.h
}

void startTheGame()
{
   Serial.println("NEW GAME STARTED");
   peliAlkoi = 1;
   gameRound = 1;     
   playerStep = 0;    
   
   // Generate the FULL random sequence once at the start
   for(int j = 0; j < 100; j++)
   {
      randomarray[j] = random(2, 6); // Random pins 2, 3, 4, 5
   }

   showSequence();
}

void showSequence()
{
   Serial.print("WATCH: ");
   
   for(int i = 0; i < gameRound; i++)
   {
      Serial.print(randomarray[i]);
      Serial.print(" ");
      
      // Example LED logic:
      setLed(randomarray[i]);
      delay(500);
      clearAllLeds();
      delay(200);
   }
   Serial.println();
   Serial.println("YOUR TURN!");
   
   // *** CRITICAL FIX FOR YOUR BUTTONS.CPP ***
   // Because you use interrupts, we must clear any button presses 
   // that happened while the LEDs were flashing.
   int junk = whatButtonPressed(); 
}

void memoryGame()
{
  int buttonPressed = whatButtonPressed();

  // If 0, no button was pressed, so we do nothing and exit function
  if(buttonPressed == 0) return; 

  // If a game button (2-5) was pressed:
  if(buttonPressed >= 2 && buttonPressed <= 5)
  {
      Serial.print("Player pressed: ");
      Serial.println(buttonPressed);

      // Check if correct
      if(buttonPressed == randomarray[playerStep])
      {
         playerStep++; // Correct! Move to next number

         // Check if round is finished
         if(playerStep == gameRound)
         {
            Serial.println("Correct! Next round...");
            //delay(1000); 
            
            gameRound++;    
            playerStep = 0; 
            
            showSequence(); // Show new sequence
         }
      }
      else
      {
         // WRONG
         Serial.println("WRONG! Game Over.");
         peliAlkoi = 0; // Stop the game
         gameRound = 0;
      }
  }
}