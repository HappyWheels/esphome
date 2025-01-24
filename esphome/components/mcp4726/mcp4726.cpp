#include "mcp4726.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mcp4726 {

static const char *const TAG = "mcp4726";
uint8_t DAC_REGISTER = 0x40;


void mcp4726::setup() {
  ESP_LOGCONFIG(TAG, "Setting up mcp4726 (0x%02X)...", this->address_);
  auto err = this->write(nullptr, 0);
  if (err != i2c::ERROR_OK) {
    this->error_code_ = COMMUNICATION_FAILED;
    this->mark_failed();
    return;
  }
}

void mcp4726::dump_config() {
  LOG_I2C_DEVICE(this);

  if (this->error_code_ == COMMUNICATION_FAILED) {
    ESP_LOGE(TAG, "Communication with mcp4726 failed!");
  }
}

// https://learn.sparkfun.com/tutorials/mcp4726-digital-to-analog-converter-hookup-guide?_ga=2.176055202.1402343014.1607953301-893095255.1606753886
void mcp4726::write_state(float state) {
  const uint16_t value = (uint16_t) round(state * (pow(2, mcp4726_RES) - 1));

  this->write_byte_16(64, value >> 4 | (value & 15) << 4);
}

}  // namespace mcp4726
}  // namespace esphome
