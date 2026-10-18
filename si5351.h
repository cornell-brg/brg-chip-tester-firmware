#ifndef SI5351_H
#define SI5351_H

#include "common.h"

#define CLK_GEN_ADDR 0x60
#define CLK0         0
#define CLK1         1

// Device status register (reg 0) bits checked after programming. CLK0 and CLK1
// both run off PLLA, so PLLB's loss-of-lock bit is ignored.
//   bit 7: SYS_INIT -- system initialization in progress
//   bit 5: LOL_A    -- PLLA loss of lock
//   bit 3: LOS_XTAL -- crystal loss of signal
#define SI5351_STATUS_SYS_INIT   0x80
#define SI5351_STATUS_FAULT_MASK 0xA8

#define SI5351_I2C_TIMEOUT_US 5000
#define SI5351_RETRIES        10

bool i2c_bus_free();
void i2c_bus_recover();
bool init_si5351();
void set_clock(int channel, int freq, int* clk0_freq, int* clk1_freq);

#endif
