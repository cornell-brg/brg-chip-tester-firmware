#ifndef INA220_H
#define INA220_H

#include "common.h"
#include "i2c_custom.h"

void init_ina220s();
float read_voltage(int channel);
float read_current(int channel);
float read_power(int channel);

#endif