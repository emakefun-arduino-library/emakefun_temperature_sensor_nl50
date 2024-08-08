#pragma once

#ifndef EMAKEFUN_TEMPERATURE_SENSOR_NL50_H_
#define EMAKEFUN_TEMPERATURE_SENSOR_NL50_H_

#include <WString.h>
#include <stdint.h>

namespace emakefun {
class TemperatureSensorNl50 {
 public:
  static constexpr uint32_t kVersionMajor = 1;
  static constexpr uint32_t kVersionMinor = 0;
  static constexpr uint32_t kVersionPatch = 0;

  static String Version() {
    return String(kVersionMajor) + '.' + kVersionMinor + '.' + kVersionPatch;
  }

  explicit TemperatureSensorNl50(const uint8_t pin);

  void Initialize();

  float Read() const;

 private:
  TemperatureSensorNl50(const TemperatureSensorNl50&) = delete;
  TemperatureSensorNl50& operator=(const TemperatureSensorNl50&) = delete;

  const uint8_t pin_ = 0;
};
}  // namespace emakefun
#endif