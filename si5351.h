#ifndef SI5351_H
#define SI5351_H

#include "common.h"

#define CLK_GEN_ADDR 0x60
#define CLK0         0
#define CLK1         1

void init_si5351();
void set_clock(int channel, int freq, int* clk0_freq, int* clk1_freq);

#endif