#ifndef MCP4562_H
#define MCP4562_H

#define MIN_VOLT 0.8
#define MAX_VOLT 3.4
#define MIN_TAP 0
#define MAX_TAP 255

#include "common.h"
#include "i2c_custom.h"

void set_voltage(int channel, float voltage, uint8_t prog);

#endif