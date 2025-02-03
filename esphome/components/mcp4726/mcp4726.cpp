#include "mcp4726.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mcp4726 {

static const char *const TAG = "mcp4726";
static const uint8_t DAC_REGISTER = 0x40;
  uint8_t array[3];  // Create 3-byte array


void mcp4726::setup() {
  ESP_LOGCONFIG(TAG, "Setting up mcp4726 (0x%02X)...", this->address_);
 Wire.begin();
 // auto err = this->write(nullptr, 0);
  //if (err != i2c::ERROR_OK) {
  //  this->error_code_ = COMMUNICATION_FAILED;
   // this->mark_failed();
 //   return;
 // }
}

void mcp4726::dump_config() {
  LOG_I2C_DEVICE(this);

  if (this->error_code_ == COMMUNICATION_FAILED) {
    ESP_LOGE(TAG, "Communication with mcp4726 failed!");
  }
}

// https://learn.sparkfun.com/tutorials/mcp4726-digital-to-analog-converter-hookup-guide?_ga=2.176055202.1402343014.1607953301-893095255.1606753886
void mcp4726::write_state(float state) {
  // ESP_LOGD("state", "The state is: %.5f", state);
//const uint16_t value = (uint16_t) round(state * (pow(2, mcp4726_RES) - 1));
//ESP_LOGD("state", "The dim vaue is: %f", value);
 // uint16_t output = (uint16_t) remap((1024-value), 0, 1024, 2100, 3350);
// const uint16_t value = (uint16_t) round(state * (pow(2, mcp4726_RES) - 1));
 uint16_t value = (uint16_t) round(state * 4095);
 Wire.beginTransmission(mcp4726_ADDR); //address of DAC
    Wire.write(0x40); //write data to DAC
   // Wire.write(value >> 4);                   // Upper data bits          (D11.D10.D9.D8.D7.D6.D5.D4)
    //Wire.write((value & 15) << 4);            // Lower data bits          (D3.D2.D1.D0.x.x.x.x)
     Wire.write((uint8_t) ((value >> 8) & 0x0F));   // MSB: (D11, D10, D9, D8) 
  Wire.write((uint8_t) (value));  // LSB: (D7, D6, D5, D4, D3, D2, D1, D0)
    Wire.endTransmission();}

 //constexpr uint8_t ADDR_REGISTER_1 = 0x40;
//i2c::I2CRegister reg_1 = this->reg(ADDR_REGISTER_1); // declare

//  uint16_t value = state * 4095;
  // ESP_LOGD("value", "The vaue is: %d", value);
 
   // uint16_t number = 0x0ABC;  // Example 12-bit number (0x0ABC = 2748 decimal)
// First byte is fixed 0x40
 //   array[0] = 0x40;

    // Extract high 8 bits for second byte (right shift by 4)
   // array[1] = (value >> 4) & 0xFF;

    // Extract low 4 bits for third byte (mask with 0x0F and pad with zeros)
    //array[2] = (value & 0x0F)<< 4;
    

  
    //Map to 2100-3350, values by trial and error, may depend on used light. I am using LEDs. 
 //   uint16_t output = (uint16_t) remap((1024-value), 0, 1024, 2100, 3350);
 //   this->write_byte_16(DAC_REGISTER, value << 4);}
    //this->write(array, 3); }
  //  this->write_byte(0x0, array[0]);

 //  this->write_byte_16(DAC_REGISTER, ((value << 4) | ((value & 15) << 4)));}
   // this->write_byte_16(DAC_REGISTER, (value << 4));} 

 //   this->write_byte_16(DAC_REGISTER, ((output << 4) | ((output & 15) << 4)));}

 // Function to create the array from a 12-bit number

    

}  // namespace mcp4726
}  // namespace esphome