const int a = 7;
const int b = 6;
const int c = 11;
const int d = 12;
const int e = 13;
const int f = 8;
const int g = 9;
const int dp = 10;
const int anode = 5;
const int piezoOut = 3;

const int buttStart = 2;
const int buttOpt = 4;
int opt;

const int potPin = A5;
int potV;
int pos;

const int sampleWindow = 50;
const int ampPin = A0;
unsigned int sample;
const int micTreshold = 200;

int counter = 0;
long splitSecs[50];
long splitTenths[50];

long randInt;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  int i;
  for (i = 5;i<=13;i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  pinMode(buttStart, INPUT_PULLUP);
  pinMode(buttOpt, INPUT_PULLUP);

  digitalWrite(anode, HIGH);

  sayHi();
  clearDisplay();
}

void loop(){
  // Read potmeter and assign number
  // higher values get shorter range, so assign 9 and 10 to 9
  potV = analogRead(potPin);
  pos = map(potV, 0, 1024, 0, 10);
  if (pos == 10) {
    pos = 9;
  }
  
  displayNumber(pos);

  // If startbutton is pressed, start program
  if (digitalRead(buttStart) == LOW) {
    runProg(pos);
  }

  // Button for options (set timer in seconds)
  if (digitalRead(buttOpt) == LOW) {
    tone(piezoOut, 100, 100);
    opt = pos;
  }

}

// *** PROGRAMS ***

// Simple draw timer - Simulates random beep going off during contest
void drawTimer() {
  tone(piezoOut, 240, 100);
  randInt = random(2000, 5000);
  delay(randInt);
  tone(piezoOut, 240, 100);
}

// First programmable program - Extension of draw timer, but you can set
// amount of seconds before next beep goes off, giving yoursel f x seconds
// to achieve objective
void drawTimerTimed(int pos) {
  randInt = random(2000, 5000);
  drawTimer();
  delay(pos*1000);
  tone(piezoOut, 240, 100);
}

// Working on getting a split timer
void splitsTest() {
  long startMillis = millis();
  while (digitalRead(buttOpt) == HIGH) {
    int out = mic();
    //Serial.println(out);
    if (out > micTreshold) {
      long currentMillis = millis() - startMillis;
      splitSecs[counter] = currentMillis/1000;
      splitTenths[counter] = currentMillis % 1000;
      counter ++;
    }
    Serial.println(counter);
    displayNumber(counter);
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
  letterA();
  switch (pos) {
    case 0:
      drawTimer();
      break;
    case 1:
      drawTimerTimed(opt);
      break;
    case 2:
      splitsTest();
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
    case 10:
      resetAll();
      break;
  }
}

// Numbers displays

void displayNumber(int no) {
  if (no > 9) {
    no = no % 10;
  }
  switch (no) {
    case 0:
      numberZero();
    case 1:
      numberOne();
      break;
    case 2:
      numberTwo();
      break;
    case 3:
      numberThree();
      break;
    case 4:
      numberFour();
      break;
    case 5:
      numberFive();
      break;
    case 6:
      numberSix();
      break;
    case 7:
      numberSeven();
      break;
    case 8:
      numberEight();
      break;
    case 9:
      numberNine();
      break;
    case 10:
      numberNine();
      break;
  }
}

// Print print functions
void sayHi() {
  letterH();
  delay(333);
  letterE();
  delay(333);
  letterI();
  delay(333);
}

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

// *** NUMBERS ***

void numberOne() {
  clearDisplay();
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
}

void numberTwo() {
  clearDisplay();
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(g, LOW);
  digitalWrite(e, LOW);
  digitalWrite(d, LOW);
}

void numberThree() {
  clearDisplay();
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(g, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
}

void numberFour() {
  clearDisplay();
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
}

void numberFive() {
  clearDisplay();
  digitalWrite(a, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
}

void numberSix() {
  clearDisplay();
  digitalWrite(a, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(e, LOW);
  digitalWrite(d, LOW);
  digitalWrite(c, LOW);
}

void numberSeven() {
  clearDisplay();
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
}

void numberEight() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void numberNine() {
  clearDisplay();
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void numberZero() {
  clearDisplay();
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
}

void dot() {
  clearDisplay();
  digitalWrite(dp, LOW);
}

// *** LETTERS ***

void letterA() {
  clearDisplay();
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void letterH() {
  clearDisplay();
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
void letterE() {
  clearDisplay();
  digitalWrite(a, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
void letterI() {
  clearDisplay();
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
}

void clearDisplay() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, HIGH);
}

