#ifndef INA220_H
#define INA220_H

#include "common.h"

#define CORE_SENS_ADDR    0x44
#define IO_SENS_ADDR      0x45
#define INA220_CONFIG_REG 0x00
#define INA220_VOLT_REG   0x02
#define INA220_POWER_REG  0x03
#define INA220_CURR_REG   0x04
#define INA220_CAL_REG    0x05

void init_ina220s();
float read_voltage(int channel);
float read_current(int channel);
float read_power(int channel);

#endif