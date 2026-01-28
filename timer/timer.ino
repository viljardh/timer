#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// init buzzer
const uint8_t buzzPin = 3;

// init buttons and options "menu"
const uint8_t buttStart = 2;
const uint8_t buttOpt = 4;
uint8_t opt = 1;

// init potmeter
const uint8_t potPin = A1;
//const uint8_t maxPos = 9;

// init for mic
const uint8_t sampleWindow = 50;
const uint8_t ampPin = A0;
uint16_t sample;
const uint8_t micTreshold = 100; //REALLY LOW, GONNA MAX  TO OL' 1023

// tracking shooting stats
// May increase if necessary, but SRAM is insanely limited
uint8_t counter = 0;
const uint8_t maxSplits = 42;
uint16_t splitSecs[maxSplits];
uint8_t  splitTenths[maxSplits];

// init screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// handy to have!
unsigned long randInt = 0UL;

// flags
bool delayed = true;
bool dry = true;

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
  
  pinMode(buzzPin, OUTPUT);
  pinMode(buttStart, INPUT_PULLUP);
  pinMode(buttOpt, INPUT_PULLUP);
  
  // setup screen
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // display friendly welcome message
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(14, 12);
  display.setTextSize(2);
  display.println(F("Go fast"));
  display.println(F("Don't suck"));
  display.display();
  delay(2000); 
}

void loop(){

  // Read potmeter and assign number
  uint16_t potV = analogRead(potPin);
  uint8_t pos = map(potV, 0, 1024, 0, 11);
  //if (pos > maxPos) pos = maxPos;

  
  displayProg(pos);

  // Button for options (set timer in seconds)
  // This is really hacky for memory reasons abstracted
  // away by Arduino IDE
  if (digitalRead(buttOpt) == LOW) {
    opt = pos;
  }

}

// *** PROGRAMS ***

// display and select program
// Start button checks in here because abovementioned
// No I don't know why
void displayProg(uint8_t no) {
  switch(no) {
    case 0:
      displayProgText(no);
      // If startbutton is pressed, start program
      if (digitalRead(buttStart) == LOW) {
        dryDraw(opt);
      }
      break;
    case 1:
      displayProgText(no);
      if (digitalRead(buttStart) == LOW) {
        dryDrawTimed(opt);
      }
      break;
    case 2:
      displayProgText(no);
      if (digitalRead(buttStart) == LOW) {
        shotTimer();
      }
      break;
    case 7:
      displayOpt('S', 'P', 'T');
      if (digitalRead(buttStart) == LOW) {
        readSplits();
      }
      break;
    case 8:
      displayOpt('D', 'R', 'Y');
      if (digitalRead(buttStart) == LOW) {
        dry = !dry;
      }
      delay(250);
      break;
    case 9:
      displayOpt('D', 'L', 'Y');
      if (digitalRead(buttStart) == LOW) {
        delayed = !delayed;
      }
      delay(250);
      break;
    case 10:
      displayOpt('R', 'S', 'T');
      if (digitalRead(buttStart) == LOW) {
        display.invertDisplay(true);
        delay(250);
        resetAll();
      }
      display.invertDisplay(false);
      break;
    default:
      displayBigNumber(no);
      break;
  }
}

// Simple draw timer - Simulates random beep going off during contest
// Addition: Opt position now denotes how many shots you want to do in series
// So I don't have to reset every flippin time
void dryDraw(uint8_t no) {
  beep();
  display.invertDisplay(true);
  for (uint8_t i = 0; i < no; i++) {
    randInt = random(2000UL, 5000UL);
    delay(randInt);
  beep();
  }
  display.invertDisplay(false);
}

// First programmable program - Extension of draw timer, but you can set
// amount of seconds before next beep goes off, giving yourself x seconds
// to achieve objective
void dryDrawTimed(uint8_t no) {
  randInt = random(2000UL, 5000UL);
  dryDraw(1);
  // Invert display to light up, signify activity
  display.invertDisplay(true);
  delay(no*1000);
  beep();
  display.invertDisplay(false);
}

// Shot timer - Starts with regular draw, times and tracks shots. 
void shotTimer() {
  if(delayed) {
    displayBigNumber(3);
    delay(1000);
    displayBigNumber(2);
    delay(1000);
    displayBigNumber(1);
    delay(1000);
  } 
  display.invertDisplay(true);
  displayBigNumber(0);
  beep();
  // Starts timer
  uint32_t startMillis = millis();
  while (digitalRead(buttOpt) == HIGH) {
    uint16_t out = mic();
    // If noise is substantial enough
    if (out > micTreshold) {
      // Do a checkpoint and store splits
      unsigned long cur = millis() - startMillis;
      uint16_t s = (uint16_t)(cur / 1000UL);
      uint8_t cs = (uint8_t)((cur % 1000UL) / 10UL); // centiseconds 0..99
      splitSecs[counter] = s;
      splitTenths[counter] = cs;
      counter ++;

      // No leakage!!!
      if (counter >= maxSplits) counter = maxSplits;

      // There's no prettier way of doing this
      display.clearDisplay();
      display.setTextSize(3);
      display.setCursor(50, 6);
      display.println(counter);
      display.setCursor(20, 30);
      if (splitSecs[counter - 1] < 10) display.print('0'); 
      display.print(splitSecs[counter-1]);
      display.print('.');
      if (splitTenths[counter - 1] < 10) display.print('0'); 
      display.print(splitTenths[counter-1]);
      display.display();
      delay(10); 
    }
  }
  delay(250);
  display.invertDisplay(false);
}

// reading stored splits after action
void readSplits() {
  while (digitalRead(buttOpt) == HIGH) {

    // Same logic as picking program
    uint16_t potV = analogRead(potPin);
    uint8_t pos = map(potV, 0, 1024, 0, counter);
    
    // Avert thine gaze
    display.clearDisplay();
    display.setTextSize(3);
    display.setCursor(55, 6); 
    display.print(pos+1);
    display.setCursor(20, 36);
    if (splitSecs[pos] < 10) display.print('0');
    display.print(splitSecs[pos]);
    display.print('.');
    if (splitTenths[pos] < 10) display.print('0'); 
    display.print(splitTenths[pos]);
    display.println();
    display.display();
    delay(10); 
  }
}

// cpp moment
void resetAll() {
  for (uint8_t i = 0; i < counter; i++) {
    splitSecs[i] = 0;
    splitTenths[i] = 0;
  }
  counter = 0;
  Serial.println("Reset");
}

// Initializes microphone
uint16_t mic() {
  uint32_t startMillis = millis(); // Start of sample window
  uint16_t signalMax = 0;
  uint16_t signalMin = 1024;

  // collect data for 50 ms 
  while (millis() - startMillis < sampleWindow) {
    sample = analogRead(ampPin);
    if (sample < 1024) {
      if (sample > signalMax) {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin) {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  return signalMax - signalMin;  // peak amplitude
}

// buzzer beep
void beep() {
  digitalWrite(buzzPin, HIGH);
  delay(100);
  digitalWrite(buzzPin, LOW);
}

void displayBigNumber(uint8_t pos) {
  display.clearDisplay();
  display.setCursor(44, 4);
  display.setTextSize(8);
  display.println(pos);
  display.display();
}

// displays program and option
void displayProgText(uint8_t pos) {
  display.clearDisplay();
  displayDelay();
  displayDryLive();
  display.setTextSize(3);
  display.setCursor(50, 10);
  display.print('P');
  display.println(pos);
  if(opt == 10) {
    display.setCursor(40, 34);
  } else {
    display.setCursor(50, 34);
  }
  display.print('O');
  display.println(opt);
  display.display();
  delay(10);
}
// displays program and option
void displayOpt(char a, char b, char c) {
  display.clearDisplay();
  displayDelay();
  displayDryLive();
  display.setTextSize(3);
  display.setCursor(40, 10);
  display.print(a);
  display.print(b);
  display.println(c);
  if(opt == 10) {
    display.setCursor(40, 34);
  } else {
    display.setCursor(50, 34);
  }
  display.print('O');
  display.println(opt);
  display.display();
  delay(10);
}

// suggested by others, leaving for now
void displayDelay() {
  if (delayed) {
    display.setCursor(0,0);
    display.setTextSize(1);
    display.print('D');
    display.print('L');
    display.println('Y');
  }
}

// dry/live fire
void displayDryLive() {
  display.setCursor(0, 57);
  display.setTextSize(1);
  if (dry) {
    display.print('D');
    display.print('R');
    display.println('Y');
  } else {
    display.print('L');
    display.print('I');
    display.print('V');
    display.println('E');
  }
}

void addDelay() {
  if (delayed) delay(3000);
}
