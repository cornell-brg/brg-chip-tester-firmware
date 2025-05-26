#include "tca6408a.h"

void init_tca6408a() {
  uint8_t data[2] = {TCA6408A_CONFIG_REG, 0x7F}; // Bit 7 is an output, rest are inputs
  i2c_write_blocking(I2C_CHAN, IO_EXP_ADDR, data, 2, false);
}

int get_button_num() {
  uint8_t reg = TCA6408A_INPUT_REG;
  i2c_write_blocking(I2C_CHAN, IO_EXP_ADDR, &reg, 1, true);
  i2c_read_blocking(I2C_CHAN, IO_EXP_ADDR, &reg, 1, false);
  reg = ~reg;
  return reg == 0 ? 0 : (__builtin_ctz(reg) + 1);
}

void set_output(uint8_t out_pin, uint8_t out_val) {
  uint8_t reg = TCA6408A_OUTPUT_REG;
  uint8_t curr_out_val;

  // Read current output port value
  i2c_write_blocking(I2C_CHAN, IO_EXP_ADDR, &reg, 1, true);
  i2c_read_blocking(I2C_CHAN, IO_EXP_ADDR, &curr_out_val, 1, false);

  // Modify the specified bit
  if (out_val) curr_out_val |= (1 << out_pin);
  else curr_out_val &= ~(1 << out_pin);

  // Write back the new value
  uint8_t write_buf[2] = {TCA6408A_OUTPUT_REG, curr_out_val};
  i2c_write_blocking(I2C_CHAN, IO_EXP_ADDR, write_buf, 2, false);
}