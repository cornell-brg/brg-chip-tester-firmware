#include "mcp4562.h"

uint8_t map_range(float input, float input_min, float input_max, int output_min, int output_max) {
  return (uint8_t)((input - input_min) / (input_max - input_min) * (output_max - output_min) + output_min);
}

void set_voltage(int channel, float voltage, uint8_t prog) {
  uint8_t volt_data[2] = {prog ? 0x20 : 0x00, map_range(voltage, MIN_VOLT, MAX_VOLT, MIN_TAP, MAX_TAP)};
  i2c_write_blocking_err_check(I2C_CHAN, channel == CORE ? CORE_LDO : IO_LDO, volt_data, 2, false);
}