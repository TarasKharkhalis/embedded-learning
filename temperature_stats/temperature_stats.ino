#include <vector>
#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

constexpr uint32_t measurementDelayMs{2000};

std::vector<float> temps;

void setup() {
 Serial.begin(115200);

   if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
    Serial.println("The sensor has not been found... Check connection...");
    while (1) delay(10);
  }
}

void loop() {
  const float measurement{bmp.readTemperature()};
  temps.push_back(measurement);
  if(temps.size() > 10) temps.erase(temps.begin());
  float maxTemp = temps[0];
  float sum{0};
  for(float temp : temps) {
    if(temp > maxTemp) maxTemp = temp;
    sum += temp;
  }
  const float averageTemp = sum / temps.size();
  Serial.print(measurement);
  Serial.print(" ");
  Serial.print(maxTemp);
  Serial.print(" ");
  Serial.print(averageTemp);
  Serial.print(" ");
  Serial.println(temps.size());
  delay(measurementDelayMs);
}
