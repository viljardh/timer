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

// init for mix
const uint8_t sampleWindow = 50;
const uint8_t ampPin = A0;
uint16_t sample;
const uint8_t micTreshold = 200;

// tracking shooting stats
uint8_t counter = 0;
uint16_t splitSecs[42];
uint16_t  splitTenths[42];

// init screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// handy to have!
unsigned long randInt = 0UL;
uint8_t i;

void setup() {

  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  pinMode(buzzPin, OUTPUT);
  pinMode(buttStart, INPUT_PULLUP);
  pinMode(buttOpt, INPUT_PULLUP);
  
  // setup screen
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

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
  // higher values get shorter range, so assign 9 and 10 to 9
  // stupid fix for stupid problem
  uint16_t potV = analogRead(potPin);
  uint8_t pos = map(potV, 0, 1024, 0, 10);
  if (pos == 10) {
    pos = 9;
  }
  
  displayProg(pos);

  // Button for options (set timer in seconds)
  if (digitalRead(buttOpt) == LOW) {
    opt = pos;
  }

}

// *** PROGRAMS ***

// display and select program
void displayProg(uint8_t no) {
  switch(no) {
    case 0:
      displayProgText(no);
      // If startbutton is pressed, start program
      if (digitalRead(buttStart) == LOW) {
        drawTimer(opt);
      }
      break;
    case 1:
      displayProgText(no);
      if (digitalRead(buttStart) == LOW) {
        drawTimerTimed(opt);
      }
      break;
    case 2:
      displayProgText(no);
      if (digitalRead(buttStart) == LOW) {
        shotTimer();
      }
      break;
    case 3:
      displayProgText(no);
      break;
    case 4:
      //insert
      break;
    case 5:
      //insert
      break;
    case 6:
      //insert
      break;
    case 7:
      //insert
      break;
    case 8:
      //insert
      break;
    case 9:
      displayProgText(no);
      if (digitalRead(buttStart) == LOW) {
        display.invertDisplay(true);
        resetAll();
      }
      display.invertDisplay(false);
      break;
    
  }
}

// Simple draw timer - Simulates random beep going off during contest
// Addition: Opt position now denotes how many shots you want to do in series
// So I don't have to reset every flippin time
void drawTimer(uint8_t no) {
  beep();
  display.invertDisplay(true);
  for (i = 0; i < no; i++) {
    randInt = random(2000UL, 5000UL);
    delay(randInt);
  beep();
  }
  display.invertDisplay(false);
}

// First programmable program - Extension of draw timer, but you can set
// amount of seconds before next beep goes off, giving yoursel f x seconds
// to achieve objective
void drawTimerTimed(uint8_t no) {
  randInt = random(2000UL, 5000UL);
  drawTimer(1);
  display.invertDisplay(true);
  delay(no*1000);
  beep();
  display.invertDisplay(false);
}

// Shot timer - Starts with regular draw, times and tracks shots. 
void shotTimer() {

  drawTimer(1);

  display.invertDisplay(true);
  uint32_t startMillis = millis();
  while (digitalRead(buttOpt) == HIGH) {
    uint16_t out = mic();
    if (out > micTreshold) {
      uint32_t currentMillis = millis() - startMillis;
      splitSecs[counter] = (uint16_t)(currentMillis/1000UL);
      splitTenths[counter] = (uint16_t)(currentMillis % 1000UL);
      counter ++;

      display.clearDisplay();
      display.setTextSize(3);
      display.setCursor(50, 6);
      display.println(counter);
      display.setCursor(50, 30);
      display.print(splitSecs[counter-1]);
      display.print('.');
      display.print(splitTenths[counter-1]);
      display.display();
      delay(10); 
    }
  }
  printAllSplits();
  display.invertDisplay(false);
}

// cpp moment
void resetAll() {
  for (i = 0; i < counter; i++) {
    splitSecs[i] = 0;
    splitTenths[i] = 0;
  }
  counter = 0;
  Serial.println("Reset");
}

void printAllSplits() {
  i = 0;
  while (i < counter) {
    Serial.print(splitSecs[i]);
    Serial.print('.');
    Serial.print(splitTenths[i]);
    Serial.println();
    i++;
  }
}

// Initializes microphone
uint16_t mic() {
  uint32_t startMillis = millis(); // Start of sample window
  uint16_t peakToPeak = 0;   // peak-to-peak level
  uint16_t signalMax = 0;
  uint16_t signalMin = 1024;

  // collect data for 50 ms and then plot data
  while (millis() - startMillis < sampleWindow)
  {
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
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  return peakToPeak;
}

// buzzer beep
void beep() {
  digitalWrite(buzzPin, HIGH);
  delay(100);
  digitalWrite(buzzPin, LOW);
}

// displays program and option
void displayProgText(uint8_t pos) {
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(50, 6);
  display.print('P');
  display.println(pos);
  display.setCursor(50, 30);
  display.print('O');
  display.println(opt);
  display.display();
  delay(10); 
}