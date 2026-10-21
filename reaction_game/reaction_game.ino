constexpr int ledPin = 2;
constexpr int buttonPin = 4;
constexpr unsigned long debounceDelay = 40;
constexpr int numberOfRounds = 5;
constexpr unsigned long minWaitMs = 2000;
constexpr unsigned long maxWaitMs = 5000;

unsigned long recordTime = ULONG_MAX; // починаємо з максимального значення типу, щоб уникнути ситуації коли гравець заснув під час гри і його reactionTime якимось чином буде більший за рекорд

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
}

void waitForButtonToSettle() {
  delay(debounceDelay); // перечікування дрижання кнопки на натисканні, яке відбулось при попередньому виклику функції, яка чекає поки кнопку не натисли і вертає значення тільки після натискання
  while (digitalRead(buttonPin) == LOW) {}
  delay(debounceDelay); // перечікування дрижання кнопки на відпусканні
}

unsigned long playRound() {
  waitForButtonToSettle();

  unsigned long waitTime = random(minWaitMs, maxWaitMs + 1);

  unsigned long roundStart = millis();

  while (millis() - roundStart < waitTime) {
    if (digitalRead(buttonPin) == LOW) {
      Serial.println("FALSE START ");
      return 0; // дозволяє відтрекати фальшстарт і не враховувати його в грі
    }
  }

  digitalWrite(ledPin, HIGH);
  unsigned long timeWhenLitUp = millis();

  while (digitalRead(buttonPin) == HIGH) {}
  unsigned long timeWhenPressed = millis();
  digitalWrite(ledPin, LOW);

  return timeWhenPressed - timeWhenLitUp;
}

void checkForRecordAndOutputResult (unsigned long reaction) {
  if (reaction < recordTime) {
      recordTime = reaction;
      Serial.print(recordTime);
      Serial.println(" NEW BEST SCORE!");
    } else {
      Serial.println(reaction);
    }
}

void loop() {
  unsigned long reactionTimeSum = 0;
  
  for (int i=0; i<numberOfRounds; ++i) {
    unsigned long reactionTime = playRound();
    
    while (reactionTime == 0) {
      reactionTime = playRound();
    }
    checkForRecordAndOutputResult(reactionTime);
    reactionTimeSum += reactionTime;
  }
  unsigned long averageReactionTime = reactionTimeSum / numberOfRounds;
  Serial.print(averageReactionTime);
  Serial.println(" AVERAGE");
  Serial.println("-------------------------------");
}
