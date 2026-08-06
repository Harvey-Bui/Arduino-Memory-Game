# 🧠 FlashMatch: The Arduino Memory Challenge

FlashMatch is an interactive Arduino-based memory game that challenges players to memorize and reproduce randomly generated sequences of flashing LEDs.

The project combines an **Arduino Uno R3, four pushbuttons, four LEDs, a piezo buzzer, and a 16×2 I2C LCD** to create a complete hardware-based game with multiple difficulty modes, scoring, sound effects, visual feedback, and progressive challenges.

---

## 📸 Project Preview

### Breadboard Implementation

![FlashMatch Arduino Memory Game](https://github.com/Harvey-Bui/Arduino-Memory-Game/blob/1cf9f51d6761bb255730249c564b98ee0976b4b5/Screenshot%202026-08-05%20224221.png)

### Circuit Schematic

![FlashMatch Circuit Schematic]()

### Component List

![FlashMatch Components](https://github.com/Harvey-Bui/Arduino-Memory-Game/blob/8c08f4385efdb24efca36c970808ae23aa5ce725/Screenshot%202026-08-05%20224201.png)

---

## 🎮 Features

- 🧠 Memory-based LED sequence gameplay
- 🌿 **Peaceful Mode** for standard progression
- 💀 **Nightmare Mode** with randomized level increases
- 💡 Four colored LEDs for sequence visualization
- 🔘 Four physical pushbuttons for player input
- 📟 16×2 I2C LCD interface
- 🔊 Piezo buzzer audio feedback
- 🎵 Opening melody
- 🏆 Score system
- 🥇 Top-five score tracking
- 🔄 Score reset functionality
- 🎲 Randomly generated sequences
- ⚡ Progressive sequence speed
- ❤️ Custom LCD character for Peaceful Mode
- 💀 Custom LCD skull character for Nightmare Mode
- ❌ Game-over animation and sound
- 🎉 Victory animation and sound
- 🖥️ Serial Monitor menu and score output

---

# 🕹️ How It Works

The objective is simple:

> **Watch the sequence. Remember it. Repeat it.**

The Arduino generates a random sequence of LEDs. Each LED flashes while the buzzer plays its corresponding tone.

The player must then reproduce the exact sequence using the four physical buttons.

```text
             ┌─────────────────┐
             │    Main Menu    │
             └────────┬────────┘
                      │
       ┌──────────────┼──────────────┐
       ▼              ▼              ▼
  Peaceful Mode   Show Scores   Reset Scores
       │
       ▼
 Nightmare Mode
       │
       ▼
Generate Random Sequence
       │
       ▼
 Flash LEDs + Play Tones
       │
       ▼
 Player Repeats Sequence
       │
     ┌─┴─┐
     ▼   ▼
 Correct Wrong
     │     │
     ▼     ▼
Next Level Game Over
     │
     ▼
Increase Difficulty
```

---

# 🎯 Game Modes

## 🌿 Peaceful Mode

Peaceful Mode provides the standard version of the memory challenge.

The game starts at Level 1 and increases the level by one whenever the player correctly reproduces the sequence.

For every successful level:

- The player earns **100 points**
- The level increases
- The sequence becomes more challenging
- The LED timing progressively changes

The game is configured for **11 levels**.

---

## 💀 Nightmare Mode

Nightmare Mode is designed to be significantly more challenging.

Instead of increasing the sequence by exactly one level after a successful round, the program randomly increases the current sequence by **1–4 levels**:

```cpp
currentlevel += random(1,5);
```

This makes the difficulty unpredictable and can cause the sequence to become much longer much faster.

Nightmare Mode also uses a larger sequence capacity and tracks progression using a separate `true_level` variable.

---

# 🎮 Controls

| Button | Color | Function |
|---|---|---|
| Button 1 | 🔵 Blue | Play Peaceful Mode / Blue input |
| Button 2 | 🟡 Yellow | Reset Scores / Yellow input |
| Button 3 | 🟢 Green | Show Scores / Green input |
| Button 4 | 🔴 Red | Play Nightmare Mode / Red input |

During gameplay, each button corresponds to its matching LED.

The game menu provides the following options:

```text
🔵 Blue   → Play Peaceful Mode
🟢 Green  → Show Scores
🟡 Yellow → Reset Scores
🔴 Red    → Play Nightmare Mode
```

---

# 💡 Hardware Components

| Component | Quantity | Purpose |
|---|---:|---|
| Arduino Uno R3 | 1 | Main microcontroller |
| Pushbutton | 4 | Player input |
| 1 kΩ Resistor | 8 | Circuit resistance |
| Blue LED | 1 | Memory sequence indicator |
| Green LED | 1 | Memory sequence indicator |
| Yellow LED | 1 | Memory sequence indicator |
| Red LED | 1 | Memory sequence indicator |
| Piezo | 1 | Audio feedback |
| 16×2 I2C LCD | 1 | Game interface |
| Breadboard | 1 | Circuit prototyping |
| Jumper Wires | — | Electrical connections |

---

# 🔌 Pin Configuration

The Arduino uses the following connections in the program:

| Arduino Pin | Component | Purpose |
|---:|---|---|
| D2 | Button 1 | Blue input |
| D3 | Button 2 | Yellow input |
| D4 | Button 3 | Green input |
| D5 | Button 4 | Red input |
| D7 | Blue LED | LED 1 |
| D8 | Green LED | LED 2 |
| D9 | Yellow LED | LED 3 |
| D10 | Red LED | LED 4 |
| D12 | Piezo Buzzer | Audio output |
| I2C | 16×2 LCD | Display communication |

The LCD uses the I2C address:

```text
0x27
```

---

# 📟 LCD Interface

The project uses a **16×2 I2C LCD** to display game information.

The LCD can display:

- Welcome screen
- Current game mode
- Current level
- Player score
- Top scores
- Score reset confirmation
- Game-over messages
- Victory messages

The program also creates two custom LCD characters:

- ❤️ Peaceful Mode character
- 💀 Nightmare Mode skull

---

# 🔊 Audio System

The piezo buzzer provides audio feedback throughout the game.

Each LED has a corresponding tone, allowing the player to associate a particular sound with each color.

The buzzer is used for:

- LED sequence playback
- Player button feedback
- Opening music
- Game-over sound
- Victory sound

The project also includes an opening melody stored as a sequence of musical notes and durations.

---

# 🎲 Random Sequence Generation

The Arduino generates unpredictable sequences using its random number functionality.

During startup, the random generator is seeded using an analog input:

```cpp
randomSeed(analogRead(0));
```

The game then generates a random value between 1 and 200 and divides the range into four sections:

```text
1 – 50       → Blue LED
51 – 100     → Green LED
101 – 150    → Yellow LED
151 – 200    → Red LED
```

This determines which LED will appear at each position in the sequence.

---

# 🧠 Sequence & Input Validation

The game uses two arrays to manage gameplay:

```text
n_array[]
u_array[]
```

### `n_array[]`

Stores the sequence generated by the game.

### `u_array[]`

Stores the sequence entered by the player.

The program compares the player's input with the generated sequence:

```cpp
if (u_array[j] == n_array[j])
```

If the input matches, the player continues.

If it does not, the game ends.

---

# 📈 Scoring System

Players receive:

```text
+100 points
```

for successfully completing a level.

The score is updated with:

```cpp
score += 100;
```

The game maintains five high-score positions:

```text
Score 1
Score 2
Score 3
Score 4
Score 5
```

When a player loses, their score is compared against the existing top-five scores and inserted into the appropriate position.

---

# 🏆 High Scores

The game provides a dedicated **Show Scores** option.

High scores can be viewed through:

- The Serial Monitor
- The LCD

The program maintains five score positions and updates them when a game ends.

---

# 🔄 Reset Scores

The Yellow button can be used from the main menu to reset the high-score system.

The following values are reset:

```text
Score 1 → 0
Score 2 → 0
Score 3 → 0
Score 4 → 0
Score 5 → 0
```

The LCD displays a confirmation message after the scores have been reset.

---

# ❌ Game Over

An incorrect input causes the game to end.

The game then:

1. Resets the current level.
2. Flashes all four LEDs.
3. Plays the failure tone.
4. Displays the Game Over screen.
5. Saves the player's score to the top-five ranking.
6. Returns to the menu.

The LCD displays:

```text
Game Over!
You have lost!
```

---

# 🎉 Winning the Game

Successfully completing the required progression triggers a victory sequence.

The Arduino:

- Plays a victory LED pattern
- Plays victory tones
- Displays a congratulations message
- Blinks the LCD
- Resets the game state
- Returns to the main menu

The LCD displays:

```text
Congratulations!
You passed!!!
```

---

# 🧩 Project Architecture

The program is organized around several functions that control different parts of the game.

```text
setup()
 │
 ├── Initialize Serial Monitor
 ├── Initialize buttons
 ├── Initialize LEDs
 ├── Initialize buzzer
 ├── Initialize LCD
 └── Initialize random generator

loop()
 │
 ├── Main Menu
 │
 ├── Peaceful Mode
 │
 └── Nightmare Mode

Supporting Functions
 │
 ├── welcome_screen()
 ├── print_options()
 ├── opening_song()
 ├── game_over()
 ├── blink_func()
 └── playTone()
```

---

# 🛠️ Technologies & Programming Concepts

### Languages & Platform

- **C/C++**
- **Arduino**
- **Arduino IDE**

### Programming Concepts

- Arrays
- Loops
- Conditional statements
- Functions
- Random number generation
- State management
- Input validation
- Score tracking
- Timing and delays
- Serial communication

### Hardware Concepts

- Digital input/output
- LEDs
- Pushbuttons
- Piezo buzzer
- I2C communication
- LCD displays
- Hardware/software integration

---

# 🖥️ Circuit Design

The circuit was designed using **Tinkercad** and implemented around an Arduino Uno R3.

### Complete Schematic

![FlashMatch Circuit Schematic](images/circuit-schematic.png)

### Breadboard Layout

![FlashMatch Breadboard Layout](images/arduino-memory-game.png)

---

# 🚀 Getting Started

## 1. Clone the Repository

```bash
git clone https://github.com/YOUR-USERNAME/FlashMatch-Arduino.git
```

Then navigate into the project:

```bash
cd FlashMatch-Arduino
```

## 2. Open the Arduino Project

Open the `.ino` file using the **Arduino IDE**.

## 3. Install the LCD Library

The project requires:

```cpp
#include <LiquidCrystal_I2C.h>
```

Install the **LiquidCrystal_I2C** library through the Arduino IDE's Library Manager if it is not already installed.

## 4. Build the Circuit

Connect the Arduino, LEDs, pushbuttons, resistors, piezo buzzer, and LCD according to the included schematic.

## 5. Upload the Program

Select the correct:

- Arduino board
- Processor
- Serial port

Then upload the program.

## 6. Open Serial Monitor

Set the Serial Monitor to:

```text
9600 baud
```

The Serial Monitor provides the game menu and high-score output.

---

# 🎮 How to Play

### 1. Power On

Connect the Arduino and start the game.

### 2. Choose a Mode

Use the buttons to select:

- **Peaceful Mode**
- **Nightmare Mode**

### 3. Watch the Sequence

The LEDs flash in a random order while the buzzer produces corresponding tones.

### 4. Memorize

Remember the exact order of the LEDs.

### 5. Repeat

Press the matching buttons in the same order.

### 6. Score Points

Successfully completing a level earns:

```text
+100 points
```

### 7. Increase the Challenge

Continue correctly reproducing sequences to advance.

### 8. Avoid Mistakes

One incorrect input causes a game over.

### 9. Beat the High Score

Try to achieve a spot in the top-five score rankings.

---

# 📂 Repository Structure

```text
FlashMatch-Arduino/
│
├── README.md
├── FlashMatch.ino
│
├── images/
│   ├── arduino-memory-game.png
│   ├── circuit-schematic.png
│   └── components.png
│
└── docs/
    └── project-documentation.pdf
```

---

# 🧪 Development Challenges

### Randomized Gameplay

The game needed to generate unpredictable sequences while restricting the output to the four available LEDs.

### Input Validation

Every player input must be checked against the correct position in the generated sequence.

### Difficulty Progression

The two game modes required different progression systems:

- Peaceful Mode increases one level at a time.
- Nightmare Mode randomly increases the sequence level by 1–4.

### Hardware Synchronization

The LEDs and buzzer need to work together so each sequence step provides both visual and audio feedback.

### Score Management

The program manages five high-score positions and inserts new scores into the appropriate ranking.

### User Interface

The project combines physical controls, an LCD display, and Serial Monitor output to create a complete user interface.

---

# 📚 What I Learned

Building FlashMatch provided hands-on experience developing an interactive embedded system from both the hardware and software sides.

Through this project, I gained experience with:

- C/C++ programming
- Arduino development
- Embedded systems
- Hardware/software integration
- Digital input and output
- Button input handling
- LED control
- Buzzer and tone generation
- I2C LCD communication
- Randomized algorithms
- Arrays and sequence management
- Game state management
- Difficulty progression
- Score tracking
- Debugging hardware and software
- Designing interactive user experiences

The project demonstrated how software can directly control physical hardware while responding to real-time user interaction.

---

# 🔮 Future Improvements

Possible future improvements include:

- 💾 Save high scores permanently using EEPROM
- 🏅 Add a more advanced scoring system
- 🔥 Add combo/streak bonuses
- ⏱️ Add timed challenges
- 🎚️ Add additional difficulty levels
- 🎮 Add multiplayer functionality
- 📊 Add player statistics
- 🖥️ Improve the LCD interface
- 🎵 Add additional sound effects and music
- 🎨 Add more custom LCD characters
- 🔄 Add a dedicated restart button
- ⚡ Create more sophisticated difficulty scaling

---

# 👥 Team

This project was developed as a **group Arduino project**.

### Contributors

- **Bui Le Hoang Hai**
- Add additional team members here

---

# 📜 License

This project was created for educational purposes.

Feel free to explore the source code and use it as a reference for learning Arduino programming, embedded systems, hardware integration, and game development.
