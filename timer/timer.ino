const int a = 7;
const int b = 6;
const int c = 11;
const int d = 12;
const int e = 13;
const int f = 8;
const int g = 9;
const int dp = 10;
const int anode = 5;

void setup() {
  int i;

  for (i = 5;i<=13;i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

  digitalWrite(anode, HIGH);
}

void loop(){
  letterH();
  delay(500);
  letterE();
  delay(500);
  letterI();
  delay(500);
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

