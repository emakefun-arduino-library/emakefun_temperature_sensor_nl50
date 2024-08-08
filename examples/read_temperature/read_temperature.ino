/**
 * @example read_temperature.ino
 */

#include "temperature_sensor_nl50.h"

namespace {
#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP32S3)
constexpr uint8_t kPin = 34;
#elif defined(ARDUINO_ARCH_AVR)
constexpr uint8_t kPin = A0;
#endif

emakefun::TemperatureSensorNl50 g_nl50(kPin);
}  // namespace

void setup() {
  Serial.begin(115200);
  Serial.println(String(F("temperature sensor NL50 lib version: ")) + emakefun::TemperatureSensorNl50::Version());
  g_nl50.Initialize();
  Serial.println(F("setup successful"));
}

void loop() {
  Serial.println(String("temperature: ") + g_nl50.Read());
  delay(100);
}
