constexpr int ledPin = 2;
constexpr int buttonPin = 4;
constexpr unsigned long ledOnOffDurationDuringBlinker = 500;
constexpr unsigned long ledOffBeforeBlinkerStart = 300;
constexpr unsigned long debounceDelay = 30;
constexpr unsigned long roundDurationMs = 5000;

int record = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
}

void blinkTimes(int n) {
  for (int i = 0; i < n; ++i) {
    digitalWrite(ledPin, HIGH);
    delay(ledOnOffDurationDuringBlinker);
    digitalWrite(ledPin, LOW);
    delay(ledOnOffDurationDuringBlinker);
  }
}

int countPresses(unsigned long durationMs) {
  delay(debounceDelay);
  while (digitalRead(buttonPin) == LOW) {}
  delay(debounceDelay);
  unsigned long countWindowStart = millis(); 
  int presses = 0;
  bool singleTapFlag = false;
  digitalWrite(ledPin, HIGH);
  while (millis() - countWindowStart < durationMs) {
    if (digitalRead(buttonPin) == LOW and singleTapFlag == false) {
      ++presses;
      singleTapFlag = true;
    }
    delay(debounceDelay);
    if (digitalRead(buttonPin) == HIGH) {
      singleTapFlag = false;
    }
    delay(debounceDelay);
  }
  digitalWrite(ledPin, LOW);
  delay(ledOffBeforeBlinkerStart);

  return presses;
}

void loop() {
  while (digitalRead(buttonPin) == HIGH) {}
  delay(debounceDelay);
  int presses = countPresses(roundDurationMs);

  if (presses > record) {
    record = presses;
    Serial.println("NEW RECORD");
  }
  Serial.println(presses);
  blinkTimes(presses);
}
