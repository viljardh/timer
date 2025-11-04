const int a = 7;
const int b = 6;
const int c = 11;
const int d = 12;
const int e = 13;
const int f = 8;
const int g = 9;
const int dp = 10;
const int anode = 5;

const int potPin = A5;
int potV;
int pos;


void setup() {
  Serial.begin(9600);
  int i;
  for (i = 5;i<=13;i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  digitalWrite(anode, HIGH);
  sayHi();
  clearDisplay();
}

void loop(){
  potV = analogRead(potPin);
  pos = map(potV, 0, 1023, 0, 9);
  Serial.println(pos);
  
  switch (pos) {
    case 0:
      numberZero();
      break;
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
  }

}

// Print print functions
void sayHi() {
  letterH();
  delay(500);
  letterE();
  delay(500);
  letterI();
  delay(500);
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

