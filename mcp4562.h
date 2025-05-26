#ifndef MCP4562_H
#define MCP4562_H

#include "common.h"

#define CORE_LDO_ADDR 0x2C
#define IO_LDO_ADDR   0x2E
#define MIN_VOLT      0.8
#define MAX_VOLT      3.4
#define MIN_TAP       0
#define MAX_TAP       255

void set_voltage(int channel, float voltage, uint8_t prog);

#endif