const int G4 = 392;
const int C5 = 523;
const int E5 = 659;
const int G5 = 784;

const int piezoOut = 10;
const int butt = 9;

void setup() {
  Serial.begin(9600);
  pinMode(butt, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(butt) == LOW) {
    playOpen();
  }
}


void playOpen() {
  tone(piezoOut, C5);
  delay(100);
  noTone(piezoOut);
  delay(100);
  tone(piezoOut, E5);
  delay(100);
  noTone(piezoOut);
  delay(100);
  tone(piezoOut, G5);
  delay(300);
  noTone(piezoOut);
  delay(100);
  tone(piezoOut, E5);
  delay(100);
  noTone(piezoOut);
  delay(100);
  tone(piezoOut, G5);
  delay(300);
  noTone(piezoOut);
}