#include "tca6408a.h"

int get_button_num() {
  uint8_t input_port_reg = 0x00;
  i2c_write_blocking_err_check(I2C_CHAN, IO_EXP_ADDR, &input_port_reg, 1, true);
  i2c_read_blocking(I2C_CHAN, IO_EXP_ADDR, &input_port_reg, 1, false);
  input_port_reg = ~input_port_reg;
  return input_port_reg == 0 ? 0 : (__builtin_ctz(input_port_reg) + 1);
}