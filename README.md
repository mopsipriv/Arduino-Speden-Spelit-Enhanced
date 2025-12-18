# Speden Spelit - Advanced Arduino Implementation 🕹️

This project is an enhanced version of the "Speden Spelit" speed and memory game.

The implementation features multiple game modes, a custom audio engine, and low-level hardware control.

## 🌟 Enhanced Features
We went beyond the standard requirements by implementing:
* **Two Distinct Game Modes**: 
    * `Muistipeli` (Memory Game): A sequence-repeat challenge.
    * `Reaktiopeli` (Reaction Game): A classic speed test with 20% acceleration every 10 points.
* **Intelligent UI**:
    * **I2C LCD (16x2)**: Features a custom scrolling text engine for displaying the Top-3 Highscores.
    * **Dual 7-Segment Displays**: Driven via two `74HC595` shift registers using a custom bit-banging implementation.
* **Audio & Visuals**:
    * **Custom Sound Engine**: Menu music and unique feedback tones for each button using `pitches.h`.
    * **LED Animations**: Binary counting and accelerating sequences for game transitions.
* **High-Performance Input**: 
    * Hardware-level button handling using `Pin Change Interrupts` (PCINT2) with a 200ms software debounce.

## 🛠️ Hardware Mapping
* **Buttons**: Digital Pins 2, 3, 4, 5 (Game) and Pin 6 (Start/Mode).
* **LEDs**: Analog Pins A2, A3, A4, A5.
* **7-Segment (Shift Registers)**: Pins 8 (Data), 9 (OE), 10 (Latch), 11 (Shift), 12 (Reset).
* **LCD**: I2C (Address 0x27).

## 🕹️ Game Mechanics & Scoring
* **Objective**: Reach the maximum score of **100 points** to win the game.
* **Scoring**: Points are awarded for each correct button press in the sequence.
* **Display Constraints**: 
    * The **LCD** handles the full score and victory messages.
    * The dual **7-segment displays** show real-time scores up to **99**. If the player reaches 100, the display stays at 99 due to hardware limits.
* **Winning**: Achieving 100 points triggers the `lcdYouWon()` sequence and plays a victory animation.

## 📂 Project Structure
* `SpedenSpelit.ino`: Main state machine and game loop.
* `buttons.cpp/h`: Interrupt-driven input handling.
* `display.cpp/h`: Low-level 7-segment shift register logic.
* `lcd.cpp`: LCD menu and scrolling highscore engine.
* `leds.cpp/h`: LED animations and binary display.
* `spedenpelitmusiikki.cpp`: Musical sequences and sound effects.

## 📺 Project Demonstration
https://youtube.com/shorts/h9VYuUSVIP8?feature=share
