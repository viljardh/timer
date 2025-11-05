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
  // higher values get shorter range, so assign 8 and 9 to 9
  potV = analogRead(potPin);
  pos = map(potV, 0, 1023, 0, 10);
  
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
// amount of seconds before next beep goes off
void drawTimerTimed(int pos) {
  randInt = random(2000, 5000);
  drawTimer();
  delay(pos*1000);
  tone(piezoOut, 240, 100);
}

void runProg(int pos) {
  switch (pos) {
    case 0:
      numberZero();
      drawTimer();
      break;
    case 1:
      numberOne();
      drawTimerTimed(opt);
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

void displayNumber(int no) {
  switch (pos) {
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

// *** LETTERS ***

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

