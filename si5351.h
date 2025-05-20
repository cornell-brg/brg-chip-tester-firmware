#ifndef SI5351_H
#define SI5351_H

#include "common.h"
#include "i2c_custom.h"

#define CLK0 0
#define CLK1 1

void init_si5351();
void set_clock(int channel, int freq, int* clk0_freq, int* clk1_freq);

#endif