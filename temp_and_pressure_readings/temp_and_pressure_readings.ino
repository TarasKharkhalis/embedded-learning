#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

constexpr unsigned long resultsOutputDelay = 2000;
constexpr float pressureDivider = 100;

float overallMinTemp = 0;
float overallMaxTemp = 0;

void setup() {
  Serial.begin(115200);

  if(!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
    Serial.println("The sensor has not been found... Check connection...");
    while (1) delay(10);
  }

  const float firstMeasurement = bmp.readTemperature();
  overallMaxTemp = overallMinTemp = firstMeasurement;
}

void loop() {
  
  const float currentTempReading = bmp.readTemperature();
  const float pressureReading = bmp.readPressure();

  if(currentTempReading > overallMaxTemp) {
    overallMaxTemp = currentTempReading;
  } else if (currentTempReading < overallMinTemp) {
    overallMinTemp = currentTempReading;
  }

  Serial.print("Current temperature is = ");
  Serial.print(currentTempReading);
  Serial.println(" *C");

  Serial.print("Max temperature overall is = ");
  Serial.print(overallMaxTemp);
  Serial.println(" *C");

  Serial.print("Min temperature overall is = ");
  Serial.print(overallMinTemp);
  Serial.println(" *C");

  Serial.print("Current pressure is = ");
  Serial.print(pressureReading/pressureDivider);
  Serial.println(" hPa");

  Serial.println();
  delay(resultsOutputDelay);
}
