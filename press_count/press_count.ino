#define LED 2
#define BUTTON 4

int record = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
}

void blinkTimes(int n) {
  for (int i = 0; i < n; ++i) {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
}

int countPresses(unsigned long durationMs) {
  delay(30);
  while (digitalRead(BUTTON) == LOW) {}
  delay(30);
  unsigned long countWindowStart = millis(); 
  int presses = 0;
  bool singleTapFlag = false;
  digitalWrite(LED, HIGH);
  while (millis() - countWindowStart < durationMs) {
    if (digitalRead(BUTTON) == LOW and singleTapFlag == false) {
      ++presses;
      singleTapFlag = true;
    }
    delay(30);
    if (digitalRead(BUTTON) == HIGH) {
      singleTapFlag = false;
    }
    delay(30);
  }
  digitalWrite(LED, LOW);
  delay(300);

  return presses;
}

void loop() {
  while (digitalRead(BUTTON) == HIGH) {}
  delay(30);
  int presses = countPresses(5000);

  if (presses > record) {
    record = presses;
    Serial.println("NEW RECORD");
  }
  Serial.println(presses);
  blinkTimes(presses);
}
