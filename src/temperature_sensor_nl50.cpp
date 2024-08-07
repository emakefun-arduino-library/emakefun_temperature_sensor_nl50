#include "temperature_sensor_nl50.h"

#include <Arduino.h>

#ifdef ARDUINO_ARCH_AVR
extern uint8_t analog_reference;
#endif

namespace emakefun {

namespace {
#ifdef ARDUINO_ARCH_AVR
// https://www.arduino.cc/reference/en/language/functions/analog-io/analogreference/
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
constexpr float kReferenceMillivolts = 1100.0;
constexpr uint8_t kAnalogReference = INTERNAL;
#elif defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega8__)
constexpr float kReferenceMillivolts = 2560.0;
constexpr uint8_t kAnalogReference = INTERNAL;
#else
constexpr float kReferenceMillivolts = 2560.0;
constexpr uint8_t kAnalogReference = INTERNAL2V56;
#endif
#endif
}  // namespace

TemperatureSensorNl50::TemperatureSensorNl50(const uint8_t pin) : pin_(pin) {
}

void TemperatureSensorNl50::Initialize() {
}

float TemperatureSensorNl50::Read() const {
#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP32S3)
  const float millivolts = analogReadMilliVolts(pin_);
#elif defined(ARDUINO_ARCH_AVR)
  const uint8_t previous_analog_reference = analog_reference;
  analog_reference = kAnalogReference;
  const float millivolts = analogRead(pin_) * kReferenceMillivolts / 1023.0;
  analog_reference = previous_analog_reference;
#else
#error "unsupported arch"
#endif
  // Serial.println(String("millivolts: ") + millivolts + "mv");
  return millivolts / 10.0 - 50.0;
}

}  // namespace emakefun