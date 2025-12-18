#include "buttons.h"

int volatile painettu = 0;

// We use this to remember WHEN the last valid press happened
volatile unsigned long lastInterruptTime = 0; 
const unsigned long debounceDelay = 200; // 50ms "cooldown" between presses

void initButtonsAndButtonInterrupts(void)
{
  for(int i = firstPin; i <= lastPin; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }

  PCICR |= (1 << PCIE2);

  PCMSK2 |= (1 << PCINT18); // Pin 2
  PCMSK2 |= (1 << PCINT19); // Pin 3
  PCMSK2 |= (1 << PCINT20); // Pin 4
  PCMSK2 |= (1 << PCINT21); // Pin 5
  PCMSK2 |= (1 << PCINT22); // Pin 6
}

ISR(PCINT2_vect) {
  unsigned long interruptTime = millis();

  // Only check if enough time has passed AND if the previous button has been handled
  if (interruptTime - lastInterruptTime > debounceDelay)
  {
    for (int i = firstPin; i <= lastPin; i++)
    {
      if(digitalRead(i) == LOW)
      {
        // Only register a new press if the game has 'collected' the previous one
        // OR if you want the newest press to always win, remove the "if(painettu == 0)" check.
        if(painettu == 0) { 
            painettu = i;
            lastInterruptTime = interruptTime;
        }
        break; 
      }
    }
  }
}

int whatButtonPressed() 
{
  noInterrupts(); // Disable interrupts momentarily
  int result = painettu;
  painettu = 0;

  interrupts(); // Re-enable interrupts immediately
  return result;
}