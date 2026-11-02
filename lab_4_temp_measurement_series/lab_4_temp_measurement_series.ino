#include <Wire.h>
#include <Adafruit_BMP280.h>

constexpr uint8_t ledPin = 2;
constexpr uint8_t buttonPin = 4;

uint16_t measurementNumber = 0;
int8_t temperatureDeviationRecord = 0;

Adafruit_BMP280 bmp;

struct Measurement {
  uint32_t measurementNumber,
  uint32_t seriesStart;
  int8_t minTemp;
  int8_t maxTemp;
  int8_t AverageTemp;
}

void performMeasurementSeries() {
  measurementNumber++;
  Measurement m = {}
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, OUTPUT_PULLUP);


  if(!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
    Serial.println("The sensor has not been found at this adress... Check connection...");
    while (1) delay(10);
  }
}

void loop() {

}
