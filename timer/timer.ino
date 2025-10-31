const int a = 7;
const int b = 6;
const int c = 11;
const int d = 12;
const int e = 13;
const int f = 8;
const int g = 9;
const int dp = 10;
const int anode = 5;

int DELAY = 0;        // so it happens only 3 times

void setup() {
  int i;
  for (i = 5;i<=13;i++) {
    pinMode(i, OUTPUT);
  }
}

void loop(){
  digitalWrite(anode, HIGH);
  digitalWrite(a, HIGH);

}



