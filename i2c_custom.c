#include "i2c_custom.h"

void i2c_write_blocking_err_check(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src, size_t len, bool nostop) {
  int i2c_write_code;
  do {
    i2c_write_code = i2c_write_blocking(i2c, addr, src, len, nostop);
  } while (i2c_write_code != len);
}