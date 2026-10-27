#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

constexpr unsigned long resultsOutputDelay = 2000;
constexpr float pressureDivider = 100;

float overallMinTemp = 0;
float overallMaxTemp = 0;

struct Measurement {
  float temperature;
  float pressure;
  unsigned long timeMs;
};

Measurement measurePrameters () {
  const Measurement m {bmp.readTemperature(), bmp.readPressure()/pressureDivider, millis()};
  return m;
}

void printMeasurement (Measurement m) {
  Serial.print("Current temperature is = ");
  Serial.print(m.temperature);
  Serial.println(" *C");

  Serial.print("Current pressure is = ");
  Serial.print(m.pressure);
  Serial.println(" hPa");

  Serial.print("Time is = ");
  Serial.print(m.timeMs);
  Serial.println(" ms");
}

void setup() {
  Serial.begin(115200);

  if(!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
    Serial.println("The sensor has not been found... Check connection...");
    while (1) delay(10);
  }

  const Measurement m = measurePrameters();
  overallMaxTemp = overallMinTemp = m.temperature;
}

void loop() {
  
  const Measurement m = measurePrameters();

  if(m.temperature > overallMaxTemp) {
    overallMaxTemp = m.temperature;
  } else if (m.temperature < overallMinTemp) {
    overallMinTemp = m.temperature;
  }

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
