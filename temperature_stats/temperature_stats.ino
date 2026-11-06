#include <vector>
#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

constexpr uint32_t measurementDelayMs{2000};
constexpr uint32_t numberOfMeasurements{10};

std::vector<float> temps;

void manageMeasurements(std::vector<float>& t, float m) {
  t.push_back(m);
  if(t.size() > numberOfMeasurements) t.erase(t.begin());
}

float determineMaxTemp(const std::vector<float>& t) {
  float maxT = t[0];
  for(float temp : t) {
    if(temp > maxT) maxT = temp;
  }
  return maxT;
}

float calculateAvgTemp(const std::vector<float>& t) {
  float sum{0};
  for(float temp : t) {
    sum += temp;
  }
  const float avgT = sum / t.size();
  return avgT;
}

void setup() {
 Serial.begin(115200);

   if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
    Serial.println("The sensor has not been found... Check connection...");
    while (1) delay(10);
  }
}

void loop() {

  const float measurement{bmp.readTemperature()};
  manageMeasurements(temps, measurement);
  const float maxTemp = determineMaxTemp(temps);
  const float averageTemp = calculateAvgTemp(temps);

  Serial.print(measurement);
  Serial.print(" ");
  Serial.print(maxTemp);
  Serial.print(" ");
  Serial.print(averageTemp);
  Serial.print(" ");
  Serial.println(temps.size());
  delay(measurementDelayMs);
}
