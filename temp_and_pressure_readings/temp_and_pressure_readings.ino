#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

constexpr unsigned long resultsOutputDelay = 2000;
constexpr float pressureDivider = 100;

float overallMinTemp = 0;
float overallMaxTemp = 0;

uint8_t measurementsCount = 0;

struct Measurement {
  float temperature;
  float pressure;
  uint32_t timeMs;
  uint8_t measurementNumber;
};

Measurement measurePrameters() {
  const Measurement m{ bmp.readTemperature(), bmp.readPressure() / pressureDivider, millis(), measurementsCount };
  measurementsCount = m.measurementNumber + 1;
  return m;
}

void printMeasurement(const Measurement& m) {
  Serial.print("Current temperature is = ");
  Serial.print(m.temperature);
  Serial.println(" *C");

  Serial.print("Current pressure is = ");
  Serial.print(m.pressure);
  Serial.println(" hPa");

  Serial.print("Time is = ");
  Serial.print(m.timeMs);
  Serial.println(" ms");

  Serial.print("This measurement is number = ");
  Serial.print(m.measurementNumber);
  Serial.println(" ");
}

void minMaxTempCalculations(float currentTemp, float& globalMaxTemp, float& globalMinTemp) {
  if (currentTemp > globalMaxTemp) {
    globalMaxTemp = currentTemp;
  } else if (currentTemp < globalMinTemp) {
    globalMinTemp = currentTemp;
  }
}

void setup() {
  Serial.begin(115200);

  if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
    Serial.println("The sensor has not been found... Check connection...");
    while (1) delay(10);
  }

  const Measurement m = measurePrameters();
  overallMaxTemp = overallMinTemp = m.temperature;
  Serial.println(sizeof(Measurement));
}

void loop() {

  const Measurement m = measurePrameters();

  minMaxTempCalculations(m.temperature, overallMaxTemp, overallMinTemp);

  printMeasurement(m);

  Serial.print("Max temperature overall is = ");
  Serial.print(overallMaxTemp);
  Serial.println(" *C");

  Serial.print("Min temperature overall is = ");
  Serial.print(overallMinTemp);
  Serial.println(" *C");

  Serial.println("------------------------------------");

  delay(resultsOutputDelay);
}
