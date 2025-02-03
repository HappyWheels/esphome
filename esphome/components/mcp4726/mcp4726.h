#pragma once

#include "esphome/components/output/float_output.h"
#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include <Wire.h>

static const uint8_t mcp4726_ADDR = 0x60;
static const uint8_t mcp4726_RES = 12;

namespace esphome {
namespace mcp4726 {
class mcp4726 : public Component, public output::FloatOutput, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  void write_state(float state) override;

 protected:
  enum ErrorCode { NONE = 0, COMMUNICATION_FAILED } error_code_{NONE};
};

}  // namespace mcp4725
}  // namespace esphome
