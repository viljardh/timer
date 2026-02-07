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

// init for mic
const uint8_t sampleWindow = 50;
const uint8_t ampPin = A0;
uint16_t sample;
const uint8_t micTreshold = 500; //REALLY LOW, GONNA MAX  TO OL' 1023

// tracking shooting stats
// May increase if necessary, but SRAM is insanely limited
uint8_t counter = 0;
const uint8_t maxSplits = 20;
uint16_t P2P[maxSplits];

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
      displayOpt('T', 'S', 'T', no);
      // If startbutton is pressed, start program
      if (digitalRead(buttStart) == LOW) {
        micTest();
      }
      break;
    case 9:
      displayOpt('S', 'P', 'T', no);
      if (digitalRead(buttStart) == LOW) {
        readSplits();
      }
      break;
    case 10:
      displayOpt('R', 'S', 'T', no);
      if (digitalRead(buttStart) == LOW) {
        display.invertDisplay(true);
        delay(250);
        resetAll();
      }
      display.invertDisplay(false);
      break;
    default:
      displayOpt('-', '-', '-', no);
      break;
  }
}

void micTest() {
  display.invertDisplay(true);
  displayBigNumber(0);
  beep();
  // Starts timer
  uint32_t startMillis = millis();
  while (digitalRead(buttOpt) == HIGH) {
    uint16_t out = mic();
    // If noise is substantial enough
    if (out > micTreshold) {
      Serial.print("P2P: ");
      Serial.println(out);
      // Do a checkpoint and store splits
      uint16_t s = out;
      P2P[counter] = s;
      counter ++;

      // No leakage!!!
      if (counter >= maxSplits) counter = maxSplits;

      // There's no prettier way of doing this
      display.clearDisplay();r
      display.setTextSize(3);
      if (counter > 9) {
        display.setCursor(49, 6);
      } else {
        display.setCursor(56, 6);
      }
      display.println(counter);

      if (P2P[counter-1] < 1000) {
        display.setCursor(38, 30);
      } else {
        display.setCursor(29, 30);
      }
      
      display.print(P2P[counter-1]);
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
    if (P2P[pos] < 10) display.print('0');
    display.print(P2P[pos]);
    display.display();
    delay(10); 
  }
}

// cpp moment
void resetAll() {
  for (uint8_t i = 0; i < counter; i++) {
    P2P[i] = 0;
  }
  counter = 0;
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

//displays program and option
// probably won't need this, but keeping for now
void displayProgText(uint8_t pos) {
  display.clearDisplay();
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
void displayOpt(char a, char b, char c, uint8_t pos) {
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(40, 20);
  display.print(a);
  display.print(b);
  display.println(c);
  display.display();
  delay(10);
}

