#include "temperature_sensor_nl50.h"

#include <Arduino.h>

#ifdef ARDUINO_ARCH_AVR
extern uint8_t analog_reference;
#endif

namespace emakefun {

namespace {
#ifdef ARDUINO_ARCH_AVR
uint8_t& g_reference_analog = analog_reference;
// https://www.arduino.cc/reference/en/language/functions/analog-io/analogreference/
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
constexpr float kReferenceMillivolts = 1100.0;
constexpr uint8_t kReferenceAnalog = INTERNAL;
#elif defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega8__)
constexpr float kReferenceMillivolts = 2560.0;
constexpr uint8_t kReferenceAnalog = INTERNAL;
#else
constexpr float kReferenceMillivolts = 2560.0;
constexpr uint8_t kReferenceAnalog = INTERNAL2V56;
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
  const uint8_t previous_reference_analog = g_reference_analog;
  g_reference_analog = kReferenceAnalog;
  const float millivolts = analogRead(pin_) * kReferenceMillivolts / 1023.0;
  g_reference_analog = previous_reference_analog;
#else
#error "unsupported arch"
#endif
  // Serial.println(String("millivolts: ") + millivolts + "mv");
  return millivolts / 10.0 - 50.0;
}

}  // namespace emakefun