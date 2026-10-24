constexpr int ledPin = 2;
constexpr int buttonPin = 4;
constexpr unsigned long debounceDelay = 30;
constexpr int numberOfTries = 3;
constexpr unsigned long targetMs = 1000;

unsigned long record = ULONG_MAX;

unsigned long measureHold() {
  while(digitalRead(buttonPin) == HIGH) {}
  delay(debounceDelay);
  const unsigned long buttonPressMoment = millis();
  unsigned long resut = millis();
  
  while(digitalRead(buttonPin) == LOW) {
    digitalWrite(ledPin, HIGH);
    delay(debounceDelay);
    resut = millis();
  }
  delay(debounceDelay);
  digitalWrite(ledPin, LOW);
  return resut - buttonPressMoment;
}

unsigned long deviation(unsigned long holdMs, unsigned long targetMs) {
  if (holdMs > targetMs) {
    return holdMs - targetMs;
  }
  return targetMs - holdMs;
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  unsigned long sumOfDeviations = 0;
  for(int i=0; i<numberOfTries; ++i) {
    const unsigned long playerResult = measureHold();
    const unsigned long currentDeviation = deviation(playerResult, targetMs);
    
    Serial.println(playerResult);
    
    if(currentDeviation < record) {
      Serial.print("NEW DEVIATION RECORD ");
      record = currentDeviation;
    } else {
      Serial.print("DEVIATION ");
    }
    Serial.println(currentDeviation);
    
    sumOfDeviations += currentDeviation;
  }
  Serial.print("AVERAGE DEVIATION IS ");
  Serial.println(sumOfDeviations/numberOfTries);
  Serial.println("-------------------------------");
}
