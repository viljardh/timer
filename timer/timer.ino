#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// init buzzer
const int buzzPin = 3;

// init buttons and options "menu"
const int buttStart = 2;
const int buttOpt = 4;
int opt;

// init potmeter
const int potPin = A1;
int potV;
int pos;

// init for mix
const int sampleWindow = 50;
const int ampPin = A0;
unsigned int sample;
const int micTreshold = 200;

// tracking shooting stats
int counter = 0;
long splitSecs[50];
long splitTenths[50];

// init screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int ballX = 64;
int ballY = 32;
int ballDX = 2;
int ballDY = 2;
int ballRadius = 3;

// handy to have!
long randInt;
int i;

void setup() {

  Serial.begin(115200);
  randomSeed(analogRead(0));
  
  pinMode(buzzPin, OUTPUT);
  pinMode(buttStart, INPUT_PULLUP);
  pinMode(buttOpt, INPUT_PULLUP);
  
  // setup screen
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 28);
  display.setTextSize(2);
  display.println("Go fast");
  display.println("Don't suck");
  display.display();
  delay(2000); 

}

void loop(){

  // Read potmeter and assign number
  // higher values get shorter range, so assign 9 and 10 to 9
  // stupid fix for stupid problem
  potV = analogRead(potPin);
  pos = map(potV, 0, 1024, 0, 10);
  if (pos == 10) {
    pos = 9;
  }
  
  // Show dynamic message
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(4, 28);
  display.print("Pot pos: ");
  display.println(pos);
  display.display();
  delay(100);  // Controls speed

  // // If startbutton is pressed, start program
  // if (digitalRead(buttStart) == LOW) {
  //   runProg(pos);
  // }

  // // Button for options (set timer in seconds)
  // if (digitalRead(buttOpt) == LOW) {
  //   beep();
  //   opt = pos;
  // }

}

// *** PROGRAMS ***

// Simple draw timer - Simulates random beep going off during contest
// Addition: Opt position now denotes how many shots you want to do in series
// So I don't have to reset every flippin time
void drawTimer() {
  beep();
  for (int i = 0; i < opt; i++) {
    randInt = random(2000, 5000);
    delay(randInt);
  beep();
  }
}

// First programmable program - Extension of draw timer, but you can set
// amount of seconds before next beep goes off, giving yoursel f x seconds
// to achieve objective
void drawTimerTimed(int pos) {
  randInt = random(2000, 5000);
  drawTimer();
  delay(pos*1000);
  beep();
}

// Shot timer - Starts with regular draw, times and tracks shots. 
void shotTimer() {
  drawTimer();
  long startMillis = millis();
  while (digitalRead(buttOpt) == HIGH) {
    // for some reason displays 1 when counter is 0, no idea why
    // pray it away when I get OLED
    //displayNumber(counter);
    int out = mic();
    //Serial.println(out);
    if (out > micTreshold) {
      Serial.println(counter);
      long currentMillis = millis() - startMillis;
      splitSecs[counter] = currentMillis/1000;
      splitTenths[counter] = currentMillis % 1000;
      counter ++;
    }
  }
  printAllSplits();
}

// cpp moment
void resetAll() {
  for (int i = 0; i < counter; i++) {
    splitSecs[i] = 0;
    splitTenths[i] = 0;
  }
  counter = 0;
  Serial.println("Reset");
}

void printAllSplits() {
  int i = 0;
  while (i < counter) {
    Serial.print(splitSecs[i]);
    Serial.print(".");
    Serial.print(splitTenths[i]);
    Serial.println();
    i++;
  }
}

// Runs program based on pot pos
void runProg(int pos) {
  //letterA();
  switch (pos) {
    case 0:
      drawTimer();
      break;
    case 1:
      drawTimerTimed(opt);
      break;
    case 2:
      shotTimer();
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      resetAll();
      break;
  }
}

// Numbers displays

// void displayNumber(int no) {
//   if (no > 9) {
//     no = no % 10;
//   }
//   switch (no) {
//     case 0:
//       numberZero();
//     case 1:
//       numberOne();
//       break;
//     case 2:
//       numberTwo();
//       break;
//     case 3:
//       numberThree();
//       break;
//     case 4:
//       numberFour();
//       break;
//     case 5:
//       numberFive();
//       break;
//     case 6:
//       numberSix();
//       break;
//     case 7:
//       numberSeven();
//       break;
//     case 8:
//       numberEight();
//       break;
//     case 9:
//       numberNine();
//       break;
//   }
// }

// Initializes microphone
int mic() {
  long startMillis = millis(); // Start of sample window
  int peakToPeak = 0;   // peak-to-peak level
  int signalMax = 0;
  int signalMin = 1024;

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
  // Serial.print("Min:0,");
  // Serial.print("Max:1023,");
  // Serial.print("Sensor:");
  // Serial.println(peakToPeak);
  return peakToPeak;
}

void beep() {
  digitalWrite(buzzPin, HIGH);
  delay(100);
  digitalWrite(buzzPin, LOW);
}

void ball() {
  display.clearDisplay();

  // Update ball position
  ballX += ballDX;
  ballY += ballDY;

  // Bounce off edges
  if (ballX <= ballRadius || ballX >= (SCREEN_WIDTH - ballRadius)) {
    ballDX = -ballDX;
  }
  if (ballY <= ballRadius || ballY >= (SCREEN_HEIGHT - ballRadius)) {
    ballDY = -ballDY;
  }

  // Draw ball
  display.fillCircle(ballX, ballY, ballRadius, SSD1306_WHITE);

  // Show dynamic message
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("X:");
  display.print(ballX);
  display.print(" Y:");
  display.print(ballY);

  display.display();
  delay(30);  // Controls speed
}