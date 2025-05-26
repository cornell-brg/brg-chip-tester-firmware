#include "ina220.h"

void init_ina220s() {
  uint8_t cfg_data[3] = {INA220_CONFIG_REG, 0x01, 0x9F};
  i2c_write_blocking(I2C_CHAN, CORE_SENS_ADDR, cfg_data, 3, false);
  i2c_write_blocking(I2C_CHAN, IO_SENS_ADDR, cfg_data, 3, false);

  uint8_t cal_data[3] = {INA220_CAL_REG, 0x83, 0x12};
  i2c_write_blocking(I2C_CHAN, CORE_SENS_ADDR, cal_data, 3, false);
  i2c_write_blocking(I2C_CHAN, IO_SENS_ADDR, cal_data, 3, false);
}

float read_voltage(int channel) {
  uint8_t reg = INA220_VOLT_REG;
  uint8_t data[2];
  uint16_t raw_data;

  i2c_write_blocking(I2C_CHAN, channel == CORE ? CORE_SENS_ADDR : IO_SENS_ADDR, &reg, 1, true);
  i2c_read_blocking(I2C_CHAN, channel == CORE ? CORE_SENS_ADDR : IO_SENS_ADDR, data, 2, false);

  raw_data = (data[0] << 8) | data[1];
  raw_data = raw_data >> 3;
  return raw_data * 0.004;
}

float read_current(int channel) {
  uint8_t reg = INA220_CURR_REG;
  uint8_t data[2];
  uint16_t raw_data;

  i2c_write_blocking(I2C_CHAN, channel == CORE ? CORE_SENS_ADDR : IO_SENS_ADDR, &reg, 1, true);
  i2c_read_blocking(I2C_CHAN, channel == CORE ? CORE_SENS_ADDR : IO_SENS_ADDR, data, 2, false);

  raw_data = (data[0] << 8) | data[1];
  if (raw_data >> 15) raw_data = 0;
  else raw_data &= 0x7FFF;
  return raw_data * (3.05e-5);
}

float read_power(int channel) {
  uint8_t reg = INA220_POWER_REG;
  uint8_t data[2];
  uint16_t raw_data;

  i2c_write_blocking(I2C_CHAN, channel == CORE ? CORE_SENS_ADDR : IO_SENS_ADDR, &reg, 1, true);
  i2c_read_blocking(I2C_CHAN, channel == CORE ? CORE_SENS_ADDR : IO_SENS_ADDR, data, 2, false);

  raw_data = (data[0] << 8) | data[1];
  return raw_data * (6.1e-4);
}