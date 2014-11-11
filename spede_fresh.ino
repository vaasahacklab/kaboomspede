// Kaboom Science Center Spede Speed Game for Arduino
// a Vaasa Hacklab project
// 
// Project group
// mikeful
// kengu2
// olmari (testing)
//
// based on ideas from Spede Pasanen, Petri Häkkinen and others
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

#include <EEPROM.h>

#include <MaxMatrix.h>
#include <avr/pgmspace.h>

#include <PinChangeInt.h>


PROGMEM const prog_uchar CH[] = {
3, 8, B0000000, B0000000, B0000000, B0000000, B0000000, // space
1, 8, B1011111, B0000000, B0000000, B0000000, B0000000, // !
3, 8, B0000011, B0000000, B0000011, B0000000, B0000000, // "
5, 8, B0010100, B0111110, B0010100, B0111110, B0010100, // #
4, 8, B0100100, B1101010, B0101011, B0010010, B0000000, // $
5, 8, B1100011, B0010011, B0001000, B1100100, B1100011, // %
5, 8, B0110110, B1001001, B1010110, B0100000, B1010000, // &
1, 8, B0000011, B0000000, B0000000, B0000000, B0000000, // '
3, 8, B0011100, B0100010, B1000001, B0000000, B0000000, // (
3, 8, B1000001, B0100010, B0011100, B0000000, B0000000, // )
5, 8, B0101000, B0011000, B0001110, B0011000, B0101000, // *
5, 8, B0001000, B0001000, B0111110, B0001000, B0001000, // +
2, 8, B10110000, B1110000, B0000000, B0000000, B0000000, // ,
4, 8, B0001000, B0001000, B0001000, B0001000, B0000000, // -
2, 8, B1100000, B1100000, B0000000, B0000000, B0000000, // .
4, 8, B1100000, B0011000, B0000110, B0000001, B0000000, // /
4, 8, B0111110, B1000001, B1000001, B0111110, B0000000, // 0
3, 8, B1000010, B1111111, B1000000, B0000000, B0000000, // 1
4, 8, B1100010, B1010001, B1001001, B1000110, B0000000, // 2
4, 8, B0100010, B1000001, B1001001, B0110110, B0000000, // 3
4, 8, B0011000, B0010100, B0010010, B1111111, B0000000, // 4
4, 8, B0100111, B1000101, B1000101, B0111001, B0000000, // 5
4, 8, B0111110, B1001001, B1001001, B0110000, B0000000, // 6
4, 8, B1100001, B0010001, B0001001, B0000111, B0000000, // 7
4, 8, B0110110, B1001001, B1001001, B0110110, B0000000, // 8
4, 8, B0000110, B1001001, B1001001, B0111110, B0000000, // 9
2, 8, B01010000, B0000000, B0000000, B0000000, B0000000, // :
2, 8, B10000000, B01010000, B0000000, B0000000, B0000000, // ;
3, 8, B0010000, B0101000, B1000100, B0000000, B0000000, // <
3, 8, B0010100, B0010100, B0010100, B0000000, B0000000, // =
3, 8, B1000100, B0101000, B0010000, B0000000, B0000000, // >
4, 8, B0000010, B1011001, B0001001, B0000110, B0000000, // ?
5, 8, B0111110, B1001001, B1010101, B1011101, B0001110, // @
4, 8, B1111110, B0010001, B0010001, B1111110, B0000000, // A
4, 8, B1111111, B1001001, B1001001, B0110110, B0000000, // B
4, 8, B0111110, B1000001, B1000001, B0100010, B0000000, // C
4, 8, B1111111, B1000001, B1000001, B0111110, B0000000, // D
4, 8, B1111111, B1001001, B1001001, B1000001, B0000000, // E
4, 8, B1111111, B0001001, B0001001, B0000001, B0000000, // F
4, 8, B0111110, B1000001, B1001001, B1111010, B0000000, // G
4, 8, B1111111, B0001000, B0001000, B1111111, B0000000, // H
3, 8, B1000001, B1111111, B1000001, B0000000, B0000000, // I
4, 8, B0110000, B1000000, B1000001, B0111111, B0000000, // J
4, 8, B1111111, B0001000, B0010100, B1100011, B0000000, // K
4, 8, B1111111, B1000000, B1000000, B1000000, B0000000, // L
5, 8, B1111111, B0000010, B0001100, B0000010, B1111111, // M
5, 8, B1111111, B0000100, B0001000, B0010000, B1111111, // N
4, 8, B0111110, B1000001, B1000001, B0111110, B0000000, // O
4, 8, B1111111, B0001001, B0001001, B0000110, B0000000, // P
4, 8, B0111110, B1000001, B1000001, B10111110, B0000000, // Q
4, 8, B1111111, B0001001, B0001001, B1110110, B0000000, // R
4, 8, B1000110, B1001001, B1001001, B0110010, B0000000, // S
5, 8, B0000001, B0000001, B1111111, B0000001, B0000001, // T
4, 8, B0111111, B1000000, B1000000, B0111111, B0000000, // U
5, 8, B0001111, B0110000, B1000000, B0110000, B0001111, // V
5, 8, B0111111, B1000000, B0111000, B1000000, B0111111, // W
5, 8, B1100011, B0010100, B0001000, B0010100, B1100011, // X
5, 8, B0000111, B0001000, B1110000, B0001000, B0000111, // Y
4, 8, B1100001, B1010001, B1001001, B1000111, B0000000, // Z
2, 8, B1111111, B1000001, B0000000, B0000000, B0000000, // [
4, 8, B0000001, B0000110, B0011000, B1100000, B0000000, // backslash
2, 8, B1000001, B1111111, B0000000, B0000000, B0000000, // ]
3, 8, B0000010, B0000001, B0000010, B0000000, B0000000, // hat
4, 8, B1000000, B1000000, B1000000, B1000000, B0000000, // _
2, 8, B0000001, B0000010, B0000000, B0000000, B0000000, // `
4, 8, B0100000, B1010100, B1010100, B1111000, B0000000, // a
4, 8, B1111111, B1000100, B1000100, B0111000, B0000000, // b
4, 8, B0111000, B1000100, B1000100, B0101000, B0000000, // c
4, 8, B0111000, B1000100, B1000100, B1111111, B0000000, // d
4, 8, B0111000, B1010100, B1010100, B0011000, B0000000, // e
3, 8, B0000100, B1111110, B0000101, B0000000, B0000000, // f
4, 8, B10011000, B10100100, B10100100, B01111000, B0000000, // g
4, 8, B1111111, B0000100, B0000100, B1111000, B0000000, // h
3, 8, B1000100, B1111101, B1000000, B0000000, B0000000, // i
4, 8, B1000000, B10000000, B10000100, B1111101, B0000000, // j
4, 8, B1111111, B0010000, B0101000, B1000100, B0000000, // k
3, 8, B1000001, B1111111, B1000000, B0000000, B0000000, // l
5, 8, B1111100, B0000100, B1111100, B0000100, B1111000, // m
4, 8, B1111100, B0000100, B0000100, B1111000, B0000000, // n
4, 8, B0111000, B1000100, B1000100, B0111000, B0000000, // o
4, 8, B11111100, B0100100, B0100100, B0011000, B0000000, // p
4, 8, B0011000, B0100100, B0100100, B11111100, B0000000, // q
4, 8, B1111100, B0001000, B0000100, B0000100, B0000000, // r
4, 8, B1001000, B1010100, B1010100, B0100100, B0000000, // s
3, 8, B0000100, B0111111, B1000100, B0000000, B0000000, // t
4, 8, B0111100, B1000000, B1000000, B1111100, B0000000, // u
5, 8, B0011100, B0100000, B1000000, B0100000, B0011100, // v
5, 8, B0111100, B1000000, B0111100, B1000000, B0111100, // w
5, 8, B1000100, B0101000, B0010000, B0101000, B1000100, // x
4, 8, B10011100, B10100000, B10100000, B1111100, B0000000, // y
3, 8, B1100100, B1010100, B1001100, B0000000, B0000000, // z
3, 8, B0001000, B0110110, B1000001, B0000000, B0000000, // {
1, 8, B1111111, B0000000, B0000000, B0000000, B0000000, // |
3, 8, B1000001, B0110110, B0001000, B0000000, B0000000, // }
4, 8, B0001000, B0000100, B0001000, B0000100, B0000000, // ~
};

int data = 12;
int load = 11;
int clock = 13;
int maxInUse = 2;    //change this variable to set how many MAX7219's you'll use
MaxMatrix m(data, load, clock, maxInUse);
byte buffer[10];
char msg[] = "Kab";
char scorea[10];


// Arduino pins connected to latch, clock and data pins of the 74HC595 chip
const int latchPin = 17;
const int clockPin = 18;
const int dataPin = 19;

// Arduino pin connected to the speaker
const int tonePin = 10;

// Arduino pins connected to transistors controlling the digits
const int enableDigits[] = { 
  14,14,14,14 };

// Arduino pins connected to leds
const int leds[] = { 
  3,5,7,9 };

// Arduino pins connected to buttons
const int buttons[] = { 
  2,4,6,8 };


// Frequencies of tones played when buttons are pressed
const int toneFreq[] = { 
  277, 311, 370, 415 };  // CS4, DS4, FS4, GS4

// Segment bits for numbers 0-9
int digits[10] = {
  B1111101, // 0  ABCDEF-
  B1000001, // 1  -BC----
  B1011110, // 2  AB-DE-G
  B1010111, // 3  ABCD--G  
  B1100011, // 4  -BC--FG
  B0110111, // 5  A-CD-EF
  B0111111, // 6  A-BCDEF
  B1010001, // 7  ABC----
  B1111111, // 8  ABCDEFG
  B1110111, // 9  ABCD-FG
};

enum {
  STATE_START_MENU,
  STATE_GAME,
  STATE_GAME_OVER
};

int score = 0;
int led = 0;
int prevLed = 0;
int nextTimer = 0;
int level = 0;
int hiscore = 0;
int startMenuTimer = 0;
int prevButtonState[] = { 
  HIGH, HIGH, HIGH, HIGH };
int state = STATE_START_MENU;
int ledsA[200];
int scrollSpeed = 100;

void printString(char* s)
{
  int col = 0;
  while (*s != 0)
  {
    if (*s < 32) continue;
    char c = *s - 32;
    memcpy_P(buffer, CH + 7*c, 7);
    m.writeSprite(col, 0, buffer);
    m.setColumn(col + buffer[0], 0);
    col += buffer[0] + 1;
    s++;
  }
}

void printStringWithShift(char *s, int shift_speed){
  while ( *s  != 0){
    printCharWithShift(*s, min(shift_speed,scrollSpeed));
    s++;
  }
}

void printCharWithShift(char c, int shift_speed){
  if (c < 32) return;
  c -= 32;
  memcpy_P(buffer, CH + 7*c, 7);
  m.writeSprite(32, 0, buffer);
  m.setColumn(32 + buffer[0], 0);
  
  for (int i=0; i<buffer[0]+1; i++) 
  {
    delay(shift_speed);
    m.shiftLeft(false, false);
  }
}

// Read hiscore value from EEPROM
void readHiscore() {
  hiscore = (EEPROM.read(0) << 8) + EEPROM.read(1);

  // EEPROM initial value is FFFF
  if(hiscore == 0xffff)
    hiscore = 0;
}

// Write hiscore value to EEPROM
void writeHiscore() {
  EEPROM.write(0, hiscore >> 8);
  EEPROM.write(1, hiscore & 0xff);
}

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  for(int i = 0; i < 4; i++)
    pinMode(enableDigits[i], OUTPUT);

  for(int i = 0; i < 4; i++)
    pinMode(leds[i], OUTPUT);

  // enable pull up resistors for button pins
  for(int i = 0; i < 4; i++)
    pinMode(buttons[i], INPUT_PULLUP);
  m.init();
  m.setIntensity(5);
  printString(msg);
  Serial.begin(9600);    //alustetaan sarjaportti
//  hiscore = 0;
//  writeHiscore();

  readHiscore();
}

// Updates display with current score.
// Flashes 4 digits quickly on the display.
// Display is turned off if enable is false.
void updateDisplay(int score, boolean enable) {
/*  int s = score;

  for(int pos = 0; pos < 4; pos++) {
    int digit = s % 10;
    s /= 10;

    // turn off all digits
    for( int i = 0; i < 4; i++ )
      digitalWrite(enableDigits[i], LOW);

    delayMicroseconds(500);

    // set latch low so digits won't change while sending bits 
    digitalWrite(latchPin, LOW);

    // shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, digits[digit]);  

    // set latch high so the LEDs will light up
    digitalWrite(latchPin, HIGH);

    delayMicroseconds(500);

    // turn on one digit
    if(enable)
      digitalWrite(enableDigits[pos], HIGH);

    delayMicroseconds(2000);
  }
*/ 
//  delayMicroseconds(3000);
}

//before start
void buttonpressed() {
  for(int i = 0; i < 4; i++)
    digitalWrite(leds[i], HIGH);
  scrollSpeed = 0;
  for(int i = 0; i < 4; i++)
    digitalWrite(leds[i], LOW);
}

// Updates the start menu. Switch between previous score and hiscore on the display.
// Start a new game when a button is pressed. Clear the hiscore is all buttons are held down for 2 seconds.
void startMenu() {
  int s = score;

  for(int i = 0; i < 4; i++)
    PCintPort::attachInterrupt(buttons[i], buttonpressed ,CHANGE);


  if (startMenuTimer % 19 == 0) {
    char string[32] = "press any button to start   ";
    printStringWithShift(string, 120);  
  } else if (startMenuTimer % 5 == 0) {
    char string[32] = "paina nappia   ";
    printStringWithShift(string, 120);  
  } else if (startMenuTimer % 1 == 0) {
    char string[32] = "Best         ";
    printStringWithShift(string, 120);  
    char scorea[10];
    itoa(hiscore, scorea, 10);
    printString(scorea);
    delay(scrollSpeed*15);
    char string2[32] = "Last         ";
    printStringWithShift(string2, 120);  
    itoa(s, scorea, 10);
    printString(scorea);
    delay(scrollSpeed*15);

  }

  

  // flick between previous score and hiscore display
  startMenuTimer = (startMenuTimer + 1) % 2000;
  if(startMenuTimer >= 1000)
    s = hiscore;

  updateDisplay(s, startMenuTimer < 975 || (startMenuTimer > 1000 && startMenuTimer < 1975));
  Serial.println(s);

  // read button state
  int buttonState = 0;
  for(int i = 0; i < 4; i++)
    if(digitalRead(buttons[i]) == LOW)
      buttonState |= 1<<i;


  if (scrollSpeed==0)
    buttonState=1;
   
  // reset hiscore if all buttons are held down for 2 seconds
  static long resetHiscoreTimer = 0;
  if(buttonState == 15) {
    if(resetHiscoreTimer == 0)
      resetHiscoreTimer = millis();
    if(millis() - resetHiscoreTimer > 2000) {
      updateDisplay(0, false);
      tone(tonePin, 500, 500);
      hiscore = 0;
      writeHiscore();
      delay(700);
      resetHiscoreTimer = 0;
    }
  } 
  else {
    resetHiscoreTimer = 0;
  }

  // start new game if a single button is pressed for 100ms
  static int startNewGameTimer = 0;
  if(buttonState == 1 || buttonState == 2 || buttonState == 4 || buttonState == 8) {
    if(startNewGameTimer == 0)
      startNewGameTimer = millis();
    if(millis() - startNewGameTimer > 50) {  
      // start new game

      for(int i = 0; i < 4; i++)
        PCintPort::detachInterrupt(buttons[i]);
      scrollSpeed=100;
      updateDisplay(score, false);
      delay(2000);
      startNewGame();
      startNewGameTimer = 0;
    }
  } 
  else {
    startNewGameTimer = 0;
  }
}

// Prepares game state for a new game.
void startNewGame() {
  state = STATE_GAME;
  score = 0;
  level = 0;
  led = -1;
  prevLed = -1;
  nextTimer = 0;
  Serial.begin(9600);    //alustetaan sarjaportti
  Serial.println("New game");    //tulostetaan sarjaporttiin
  char* msg = "0   ";
  printString(msg);
  
  for(int i = 0; i < 4; i++) 
    prevButtonState[i] = HIGH;

  // set random seed, so that every game has a different sequence
  randomSeed(millis());

  ledsA[0] = random(4);
  for(int i = 1; i<200; i++) {
    ledsA[i] = random(4); 
    while (ledsA[i]==ledsA[i-1]) {
      ledsA[i] = random(4);
    }
  }
}

void playGame() {
  // update time
  nextTimer--;

  //  delay(nextTimer);

  if(nextTimer < 0) {
    // game over if player is too slow
    //    if(led >= 0) {
    //      gameOver();
    //      return;
    //    }

    led = ledsA[level];

    // make consequent same leds less probable
//    if(led == prevLed)
//      led = random(4);
//    prevLed = led;

    nextTimer = max(150 * pow(1.6, -level*0.05), 10);
    Serial.println(nextTimer);
    level++;
    
    delay(nextTimer);

    tone(tonePin, toneFreq[led], nextTimer *6);
//    score = level;
  }

  // update leds
  for(int i = 0; i < 4; i++) {
//    digitalWrite(leds[i], led == i || (digitalRead(buttons[i]) == LOW && nextTimer > 5) ? HIGH : LOW);
    digitalWrite(leds[i], led == i); // || (digitalRead(buttons[i]) == LOW && nextTimer > 5) ? HIGH : LOW);
  }

//  delay(1000);
  Serial.println(level);    
  Serial.println(score);

  if (level>score+50)
    gameOver();

  char scorea[10];

  // read input   
  for(int i = 0; i < 4; i++) {
    int but = digitalRead(buttons[i]);
    if(but == LOW && prevButtonState[i] == HIGH) {
      // ignore button press if time since last press is too short
      if( led >= 0 ) { //&& millis() - lastButtonPress > 50 ) { 
        // correct button pressed?
        if( i == ledsA[score] ) {
          if (level==score+1) {
            nextTimer = -1;
            noTone(tonePin);
          }
          score++;
          itoa(score, scorea, 10);
          printString(scorea);
//          led = -1;  // turn off led
//          nextTimer = -1;
        } 
        else {
          gameOver();
        }
        //lastButtonPress = millis();
      }
    }
    prevButtonState[i] = but;
  }
}

// Game over. Play a game over sound and blink score.
void gameOver() {
  tone(tonePin, 250, 2500);

  // new hiscore?
  if(score > hiscore) {
    hiscore = score;
    writeHiscore();
  }

  // turn on leds
  for(int i = 0; i < 4; i++)
    digitalWrite(leds[i], HIGH);

  // flash display
  for(int i = 0; i < 70*5; i++) {
    if(i == 70*2)
      tone(tonePin, 200, 2000);    
    boolean enable = 1 - (i/60) & 1;
    updateDisplay(score, enable);
  }

  //char* msg = "0   ";
  //printString(msg);
          
  itoa(score, scorea, 10); 
  printString(scorea);
  delay(5000);

  // turn off leds
  for(int i = 0; i < 4; i++)
    digitalWrite(leds[i], LOW);
  updateDisplay(score, false);


  // enter menu
  //delay(1000);
  state = STATE_START_MENU;
  startMenuTimer = 0;
}

// Main loop. Update menu, game or game over depending on current state.
void loop() {
  if(state == STATE_START_MENU)
    startMenu();
  else if(state == STATE_GAME)
    playGame();
  else
    gameOver();
}


