#include "mcp4726.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mcp4726 {

static const char *const TAG = "mcp4726";
uint8_t DAC_REGISTER = 0x40;
uint16_t dac = 0;
static const uint8_t DAC4726_REG_INPUT = 0x40;


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
 // const uint16_t value = (uint16_t) round(state * (pow(2, mcp4726_RES) - 1));
 // uint16_t output = (uint16_t) remap((1024-value), 0, 1024, 2100, 3350);

  int value = state * 1024;
    //Map to 2100-3350, values by trial and error, may depend on used light. I am using LEDs. 
    uint16_t output = (uint16_t) remap((1024-value), 0, 1024, 2100, 3350);
    this->write_byte_16(DAC4726_REG_INPUT, output << 4);
  


}  // namespace mcp4726
}  // namespace esphome

/*  void write_state(float state) override {
    //first check if the general output should be enables
    if (state == 0.0) {
        digitalWrite(16, 0);
    }
    else {
        digitalWrite(16, 1);
    }
    // state is the amount this output should be on, from 0.0 to 1.0
    // we need to convert it to an integer first
    int value = state * 1024;
    //Map to 2100-3350, values by trial and error, may depend on used light. I am using LEDs. 
    uint16_t output = (uint16_t) map((1024-value), 0, 1024, 2100, 3350);
  
    Wire.beginTransmission(0x60); //address of DAC
    Wire.write(0x40); //write data to DAC
    Wire.write(output >> 4);                   // Upper data bits          (D11.D10.D9.D8.D7.D6.D5.D4)
    Wire.write((output & 15) << 4);            // Lower data bits          (D3.D2.D1.D0.x.x.x.x)
    Wire.endTransmission();

  }*/
