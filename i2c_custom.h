#ifndef I2C_CUSTOM_H
#define I2C_CUSTOM_H

#include "common.h"

void i2c_write_blocking_err_check(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src, size_t len, bool nostop);

#endif