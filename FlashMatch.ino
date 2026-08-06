#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16, 2);
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

byte peacefulChar[] = {
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

byte skull[] = {
  B01110,
  B10101,
  B11011,
  B01110,
  B01110,
  B01110,
  B00000,
  B00000
};
// Change this to make the song slower or faster
int tempo = 195;

// change this to whichever pin you want to use
// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] =
{
  REST, 2, NOTE_D4, 4,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_C5, -2, 
  NOTE_A4, -2,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_F4, 2, NOTE_GS4, 4,
  NOTE_D4, -1, 
  NOTE_D4, 4,

  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4, //10
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_B4, 4,
  NOTE_G4, -1,
  NOTE_AS4, 4,
     
  NOTE_D5, 2, NOTE_AS4, 4,//18
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_DS5, 2, NOTE_D5, 4,
  NOTE_CS5, 2, NOTE_A4, 4,
  NOTE_AS4, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_D4, 4,
  NOTE_D5, -1, 
  REST,4, NOTE_AS4,4,  

  NOTE_D5, 2, NOTE_AS4, 4,//26
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_AS4, 4,
  NOTE_G4, -1, 
};


// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

int game_on = 2;      // Game will run when game_on = 2
int wait = 0;
int currentlevel = 1; // The level of the easy game
long rand_num = 0;    // Initialize long variable for random number from 0-100.
int rando = 0;        // Initialize random integer for loopgame_on. Will be from 1-4 later.
int butwait = 500;    // Amount of time to wait for next button input (ghetto de-bounce)
int ledtime = 500;    // Amount of time each LED flashes for when button is pressed
int n_levels = 11;    // Number of levels until the game is won
int pinandtone = 0;   // This integer is used when the sequence is displayed
int right = 0;        // This variable must be 1 in order to go to the next level
int speedfactor = 5;  // This is the speed of the lights and sounds for the game.
int leddelay = 200;   // Initializing time for LED. This will decrease as the level increases
int possibilities = 30; //
int score = 0;        // Calculate the score
int score1 = 0;       // Calculate the top five score
int score2= 0;
int score3 = 0;
int score4 = 0;
int score5 = 0;

int time = 350;
int game_difficulty;  // This variable decided game is easy or hard
int true_level = 1;   // The level of the hard game



// Constants
const int button1 = 2;          // 1st button controls Blue LED
const int button2 = 3;          // 2nd button controls Yellow LED
const int button3 = 4;          // 3rd button controls Green LED
const int button4 = 5;          // 4th button controls Red LED
const int led1 = 7;             // Blue LED
const int led2 = 8;             // Green LED
const int led3 = 9;             // Yellow LED
const int led4 = 10;            // Red LED
const int buzzer = 12;          // Buzzer Output
const int tones[] = {1915, 1700, 1519, 1432, 2700}; // tones when you press the LED's - the last one is when you fail.



// Variables
int buttonState[] = {0,0,0,0};         // Current state of the button
int lastButtonState[] = {0,0,0,0};     // Previous state of the button
int buttonPushCounter[] = {0,0,0,0};

// Function to make buzzer produce a sound
void playTone(int tone, int duration)
{
  for (long i = 0; i < duration * 1000L; i += tone * 2)
  {
    digitalWrite(buzzer, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzer, LOW);
    delayMicroseconds(tone);
  }
}

// Prototype
void welcome_screen(); // Print welcome in the LCD display
void print_options();  // Print prompt for player to choose option
void opening_song();   // Song will play before the game start
void game_over();      // Function display game over in the LCD display
void blink_func();     // Blink the LCD display

void setup()
{
  Serial.begin(9600);
  // Initialize inputs
  randomSeed(analogRead(0));
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  // Initialize outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.init(); // Turn on LCD display
  lcd.createChar(0,peacefulChar);
  lcd.createChar(1,skull);
  lcd.backlight();
  lcd.clear();


  game_on = 2;
}

void loop()
{
    if (game_on == 2)
    {
      game_difficulty = 0; // Reset the difficulty to 0 before choosing Mode
      print_options(); // Print the prompt for player to choose options

      // Wait until player press the button
      while(digitalRead(2) == 0 || digitalRead(3) == 0 || digitalRead(4) == 0|| digitalRead(5) == 0)
      {
      if (digitalRead(2)==1)        // Press Blue button to play Easy Mode
      {
        opening_song();             // Play the opening song
        welcome_screen();           // Display welcome to LCD Display
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Peaceful Mode!");
        lcd.setCursor(0,0);
        lcd.write(0);
        lcd.setCursor(15,0);
        lcd.write(0);
        blink_func();               // Blink the LCD Display
        game_difficulty = 1;
        game_on = 0; // Will start game in next loop iteration
        break;
      }
      else if (digitalRead(3) == 1) // Press Green button to show top scores
      {
        // Serial Monitor
        Serial.print("Score 1:");
        Serial.println(score1);
        Serial.print("Score 2:");
        Serial.println(score2);
        Serial.print("Score 3:");
        Serial.println(score3);
        Serial.print("Score 4:");
        Serial.println(score4);
        Serial.print("Score 5:");
        Serial.println(score5);
        Serial.println();
        Serial.println();

        // LCD Display
        lcd.print("S1:");
        lcd.print(score1);
        lcd.setCursor(8, 0);
        lcd.print("S2:");
        lcd.print(score2);
        lcd.setCursor(0, 1);
        lcd.print("S3:");
        lcd.print(score3);
        lcd.setCursor(8, 1);
        lcd.print("S4:");
        lcd.print(score4);

        blink_func();     // Blink the LCD Display

        print_options();
      }
      else if (digitalRead(4) == 1)    // Press Yellow button to reset the top scores
      {
        score = 0;
        score1 = 0;
        score2 = 0;
        score3 = 0;
        score4 = 0;
        score5 = 0;
        Serial.println("Your score is resetted to 0");

        // LCD Display
        lcd.setCursor(1,0);
        lcd.print("The Scores've");
        lcd.setCursor(1,1);
        lcd.print("Been Reseted!!");

        blink_func();  // Blink the LCD Display

        print_options();
      }
      else if (digitalRead(5)==1)  // Press Red button to play Hard Mode
      {
        opening_song();
        welcome_screen();
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Nightmare Mode");
        lcd.setCursor(0,0);
        lcd.write(1);
        lcd.setCursor(15,0);
        lcd.write(1);
        blink_func();
        game_difficulty = 2;
        game_on = 0;
        break;
      }
    }

  }

  // Easy Mode
  if (game_difficulty == 1)
  {
    // Game logic (only runs when game_on is 0 or 1)
    int n_array[n_levels];
    int u_array[n_levels];
    int i;

    //clears arrays both "n_array" and "u_array" and starts a new game
    // Start game

    if (game_on == 0)
    {
      score = 0; // Reset score to 0
      for(i = 0; i < n_levels; i++)
      {
        n_array[i] = 0;
        u_array[i] = 0;
        rand_num = random(1,200);

        // Random the LED sequences
        if (rand_num <= 50)
        {
          rando = 0;
        }
        else if (rand_num > 50 && rand_num <= 100)
        {
          rando = 1;
        }
        else if (rand_num > 100 && rand_num <= 150)
        {
          rando = 2;
        }
        else if (rand_num <= 200)
        {
          rando = 3;
        }
        // Saves a random number in our n_array
        n_array[i] = rando;
      }
    game_on = 1;
    }

    // Shows the user the current sequence
    if (wait == 0)
    {

      delay (200);
      i = 0;

      // LCD Display to see the current level
      for (i = 0; i < currentlevel; i++)
      {
        lcd.clear();
        lcd.print("Level: ");
        lcd.println(i);
        lcd.setCursor(6,1);
        lcd.print("Score:");
        lcd.print(score);
      }

      for (i = 0; i < currentlevel; i++)
      {
        // Display the sequences of LED
        leddelay = ledtime/(1+(speedfactor/n_levels)*(currentlevel - 1));
        pinandtone = n_array[i];
        digitalWrite(pinandtone+7, HIGH);
        playTone(tones[pinandtone], leddelay);
        digitalWrite(pinandtone+7, LOW);
        delay(100/speedfactor);
      }
    wait = 1;
    }

    // Reset all variables
    i = 0;
    int buttonchange = 0;
    int j = 0; // This is the current position in the sequence

    // Read the input of the player
    while (j < currentlevel)
    {
      while (buttonchange == 0)
      {
        for (i = 0; i < 4; i++)
        {
          buttonState[i] = digitalRead(i+2);
          buttonchange = buttonchange + buttonState[i];
        }
      }

      // Show the LED when push the push button
      for (i = 0; i < 4; i = i + 1)
      {
        if (buttonState[i] == HIGH)
        {
          digitalWrite(i+7, HIGH);
          playTone(tones[i], ledtime);
          digitalWrite(i+7, LOW);
          wait = 0;
          u_array[j]=i;
          buttonState[i] = LOW;
          buttonchange = 0;
        }
      }

      // Compare our sequences with the game given
      if (u_array[j] == n_array[j])
      {
          j++;
          right = 1;
      }
      else
      {
          right = 0;
          i = 4;
          j = currentlevel;
          wait = 0;
      }
    }

    // Game over when getting the false input
    if (right == 0)
    {
      delay(300);
      currentlevel = 1;

      // Flash LEDs and play failure tone
      for (i = 0; i < 4; i++)
      {
        digitalWrite(i+7, HIGH);
      }
      playTone(tones[4], ledtime);
      for (i = 0; i < 4; i++)
      {
        digitalWrite(i+7, LOW);
      }
      delay(200);
      for (i = 0; i < 4; i++)
      {
        digitalWrite(i+7, HIGH);
      }
      playTone(tones[4], ledtime);
      for (i = 0; i < 4; i++)
      {
        digitalWrite(i+7, LOW);
      }
      delay(500);

      game_over(); // Display the game over on the LCD display

      game_on = 2; // Return to menu state to start again
    }

    // Current level will increase when getting the true input
    if (right == 1)
    {
      currentlevel++;
      score += 100;
      wait = 0;
    }

    // If game won
    if (currentlevel == n_levels)
    {
      delay(500);
      // Victory sound
      int notes[] = {2, 2, 2, 2, 0, 1, 2, 1, 2};
      int note = 0;
      int tempo[] = {200, 200, 200, 400, 400, 400, 200, 200, 600};
      int breaks[] = {100, 100, 100, 200, 200, 200, 300, 100, 200};
      for (i = 0; i < 9; i++)
      {
        note = notes[i];
        digitalWrite(note+7, HIGH);
        playTone(tones[note], tempo[i]);
        digitalWrite(note+7, LOW);
        delay(breaks[i]);
      }

      // Print the comment in LCD Display
      lcd.clear();
      lcd.print("Congratulations!");
      lcd.setCursor(0,1);
      lcd.print("You passed!!!");

      blink_func();

      currentlevel = 1;   // Reset the current level
      game_on = 2;        // Return to menu state after winning

    }
  }

  // Hard Mode
  else if (game_difficulty == 2)
  {
    int n_array[possibilities];  // We increase the size of array to make it harder
    int u_array[possibilities];
    int i;

    //clears arrays both "n_array" and "u_array" and starts a new game
    // Start game

    if (game_on == 0)
    {
      score = 0; // Reset score to 0

      // Random the sequences of the LED
      for(i = 0; i < possibilities; i++)
      {
        n_array[i] = 0;
        u_array[i]=0;
        rand_num = random(1,200);

        if (rand_num <= 50)
        {
          rando = 0;
        }
        else if (rand_num > 50 && rand_num <= 100)
        {
          rando = 1;
        }
        else if (rand_num > 100 && rand_num <= 150)
        {
          rando = 2;
        }
        else if (rand_num <= 200)
        {
          rando = 3;
        }
        //saves a random number in our n_array
        n_array[i] = rando;
      }
      game_on = 1;
    }

    //shows the user the current sequence
    if (wait == 0)
    {
      delay (200);
      i = 0;

      // LCD Display to see the current level
      for (i = 0; i < true_level; i++)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Level: ");
        lcd.println(true_level);
        lcd.setCursor(6,1);
        lcd.print("Score:");
        lcd.print(score);
      }

      // Display the sequences of LED
      for (i = 0; i < currentlevel; i++)
      {
        leddelay = ledtime/(1+(speedfactor/n_levels)*(currentlevel - 1));
        pinandtone = n_array[i];
        digitalWrite(pinandtone+7, HIGH);
        playTone(tones[pinandtone], leddelay);
        digitalWrite(pinandtone+7, LOW);
        delay(100/speedfactor);
      }
      wait = 1;
    }

    // Reset all variables
    i = 0;
    int buttonchange = 0;
    int j = 0; // This is the current position in the sequence

    while (j < currentlevel)
    {
      // Take the input of player
      while (buttonchange == 0)
      {
        for (i = 0; i < 4; i++)
        {
          buttonState[i] = digitalRead(i + 2);
          buttonchange = buttonchange + buttonState[i];
        }
      }

      // Display the LED when player push the push button
      for (i = 0; i < 4; i++)
      {
        if (buttonState[i] == HIGH)
        {
          digitalWrite(i+7, HIGH);
          playTone(tones[i], ledtime);
          digitalWrite(i+7, LOW);
          wait = 0;
          u_array[j]=i;
          buttonState[i] = LOW;
          buttonchange = 0;
        }
      }

      // Compare our sequences with the game given
      if (u_array[j] == n_array[j])
      {
        j++;
        right = 1;
      }
      else
      {
        right = 0;
        i = 4;
        j = currentlevel;
        wait = 0;
      }
    }

    // Game over when getting false input
    if (right == 0)
    {
      delay(300);
      currentlevel = 1;
      true_level = 1;

      // Flash LEDs and play failure tone
      for (i = 0; i < 4; i++)
      {
        digitalWrite(i+7, HIGH);
      }
      playTone(tones[4], ledtime);
      for (i = 0; i < 4; i++)
      {
        digitalWrite(i+7, LOW);
      }
      delay(200);
      for (i = 0; i < 4; i++)
      {
        digitalWrite(i+7, HIGH);
      }
      playTone(tones[4], ledtime);
      for (i = 0; i < 4; i++)
      {
        digitalWrite(i+7, LOW);
      }
      delay(500);

      game_over();

      game_on = 2; // Return to menu state
    }

    // The level will increase when getting true input
    if (right == 1)
    {
      currentlevel += random(1,5); // Go to higher level randomly to make the
                                   // game harder instead of increase 1 level in Easy Mode
      true_level++;
      score += 100;
      wait = 0;
    }

    // If game won
    if (true_level == n_levels)
    {
      delay(500);

      // Victory sound
      int notes[] = {2, 2, 2, 2, 0, 1, 2, 1, 2};
      int note = 0;
      int tempo[] = {200, 200, 200, 400, 400, 400, 200, 200, 600};
      int breaks[] = {100, 100, 100, 200, 200, 200, 300, 100, 200};

      for (i = 0; i < 9; i++)
      {
        note = notes[i];
        digitalWrite(note+7, HIGH);
        playTone(tones[note], tempo[i]);
        digitalWrite(note+7, LOW);
        delay(breaks[i]);
      }
      lcd.clear();
      lcd.print("Congratulations!");
      lcd.setCursor(0,1);
      lcd.print("You passed!!!");

      blink_func();

      // Reset all to start new game
      currentlevel = 1;
      true_level = 1;
      game_on = 2;    // Return to menu state after winning
    }
  }
}

void welcome_screen() // Print welcome on LCD Display
{
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Welcome to our");
  lcd.setCursor(1,1);
  lcd.print("Memory Game!!!");
  blink_func();
}

void print_options() // Print the options in the Serial Monitor
{
  Serial.println("Welcome to 'The Arduino Memory Game'!! Here how to play: ");
  Serial.println("1. Press 'Blue' button:'Play Game - Peaceful Mode'");
  Serial.println("2. Press 'Green' button:'Show Scores'");
  Serial.println("3. Press 'Yellow' button:'Reset Scores'");
  Serial.println("4. Press 'Red' button:'Play Game - Nightmare Mode'");
  Serial.println();
  Serial.println();
}

void opening_song() // Playing the opening song
{
   // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}

void game_over() // Game over function
{
    game_on = 0;
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Game Over!");
    lcd.setCursor(1,1);
    lcd.print("You have lost!");

    blink_func();

    // Save the higher score to display the top scores
    if (score > score1)
    {
      score5 = score4;
      score4 = score3;
      score3 = score2;
      score2 = score1;
      score1 = score;
    }
    else if (score > score2)
    {
      score5 = score4;
      score4 = score3;
      score3 = score2;
      score2 = score;
    }
    else if (score > score3)
    {
      score5 = score4;
      score4 = score3;
      score3 = score;
    }
    else if (score > score4)
    {
      score5 = score4;
      score4 = score;
    }
    else if (score > score5)
    {
      score5 = score;
    }
}

void blink_func() // Blinking Function
{
  lcd.blink();
  lcd.blink();
  delay(time);
  lcd.noBacklight();
  delay(time);
  lcd.backlight();
  delay(time);
  lcd.noBacklight();
  delay(time);
  lcd.backlight();
  delay(time);
  lcd.noBacklight();
  delay(time);
  lcd.backlight();
  delay(time);
  lcd.noBacklight();
  delay(time);
  lcd.backlight();
  delay(time);
  lcd.noBacklight();
  delay(time);
  lcd.backlight();
  delay(time);
  lcd.noBacklight();
  delay(time);
  lcd.backlight();
  delay(time);
  lcd.noBacklight();
  delay(time);
  lcd.backlight();
  delay(time);
  lcd.noBacklight();
  delay(time);
  lcd.backlight();
  lcd.noBlink();
  lcd.clear();
}
