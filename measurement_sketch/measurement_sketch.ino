constexpr int ledPin = 2;
constexpr int buttonPin = 4;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
  digitalWrite(ledPin, HIGH);
}

void loop() {

}
