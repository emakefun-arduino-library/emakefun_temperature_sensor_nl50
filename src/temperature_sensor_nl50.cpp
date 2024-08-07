#include "temperature_sensor_nl50.h"

#include <Arduino.h>

namespace emakefun {

TemperatureSensorNl50::TemperatureSensorNl50(const uint8_t pin) : pin_(pin) {
}

void TemperatureSensorNl50::Initialize() {
}

float TemperatureSensorNl50::Read() const {
#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP32S3)
  const float voltage_mv = analogReadMilliVolts(pin_);
#elif defined(ARDUINO_ARCH_AVR)
  const float voltage_mv = analogRead(pin_) * 5000.0 / 1023.0;
#else
#error "unsupported arch"
#endif

  return voltage_mv / 10.0 - 50.0;
}

}  // namespace emakefun