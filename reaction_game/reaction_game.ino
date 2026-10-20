#define LED 2
#define BUTTON 4

unsigned long recordTime = ULONG_MAX; // починаємо з максимального значення типу, щоб уникнути ситуації коли гравець заснув під час гри і його reactionTime якимось чином буде більший за рекорд

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
}

void waitForButtonToSettle() {
  delay(40); // перечікування дрижання кнопки на натисканні, яке відбулось при попередньому виклику функції, яка чекає поки кнопку не натисли і вертає значення тільки після натискання
  while (digitalRead(BUTTON) == LOW) {}
  delay(40); // перечікування дрижання кнопки на відпусканні
}

unsigned long playRound() {
  waitForButtonToSettle();

  int waitTime = random(2000, 5001);

  unsigned long roundStart = millis();

  while (millis() - roundStart < waitTime) {
    if (digitalRead(BUTTON) == LOW) {
      Serial.println("FALSE START ");
      return 0; // дозволяє відтрекати фальшстарт і не враховувати його в грі
    }
  }

  digitalWrite(LED, HIGH);
  unsigned long timeWhenLitUp = millis();

  while (digitalRead(BUTTON) == HIGH) {}
  unsigned long timeWhenPressed = millis();
  digitalWrite(LED, LOW);

  return timeWhenPressed - timeWhenLitUp;
}

void loop() {
  unsigned long reactionTimeSum = 0;
  
  for (int i=0; i<5; ++i) {
    unsigned long reactionTime = playRound();
    
    while (reactionTime == 0) {
      reactionTime = playRound();
    }

    if (reactionTime < recordTime) {
      recordTime = reactionTime;
      Serial.print(recordTime);
      Serial.println(" NEW BEST SCORE!");
    } else {
      Serial.println(reactionTime);
    }
    reactionTimeSum += reactionTime;
  }
  unsigned long averageReactionTime = reactionTimeSum / 5;
  Serial.print(averageReactionTime, DEC);
  Serial.println(" AVERAGE");
  Serial.println(" ");
}
