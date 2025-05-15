#ifndef BRGTC6_TEST_H
#define BRGTC6_TEST_H

#include "brgtc6_test_utils.h"

const uint32_t brgtc6_single_config_loopback_test[][2] = {
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_FACTOR, 2), CHIP_0}, // Set chip 0 clock divider factor to 2
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_SKEW, 0), CHIP_0},   // Set chip 0 clock divider skew to 0
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_MODE, 0), CHIP_0}, // Set chip 0 pattern mode to pattern 1
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PAT_BYPASS, 0), CHIP_0}, // Set chip 0 to not bypass pattern gen
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_UP_REPAIR_SEL, 8), CHIP_0}, // Set chip 0 up repair select to bit 8 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_DOWN_REPAIR_SEL, 2), CHIP_0}, // Set chip 0 down repair select to bit 2 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_GO, 1), CHIP_0}, // Set chip 0 to go
};

const uint32_t brgtc6_single_pattern_fixed_loopback_test[][2] = {
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_FACTOR, 1), CHIP_0}, // Set chip 0 clock divider factor to 2
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_SKEW, 0), CHIP_0},   // Set chip 0 clock divider skew to 0
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_MODE, 1), CHIP_0}, // Set chip 0 pattern mode to pattern 1
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PAT_BYPASS, 0), CHIP_0}, // Set chip 0 to not bypass pattern gen
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_UP_REPAIR_SEL, 0), CHIP_0}, // Set chip 0 up repair select to bit 0 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_DOWN_REPAIR_SEL, 0), CHIP_0}, // Set chip 0 down repair select to bit 0 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_1_UP, 0xAA), CHIP_0}, // Set chip 0 pattern 1 to 0xAA
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_2_UP, 0x55), CHIP_0}, // Set chip 0 pattern 2 to 0x55
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_GO, 1), CHIP_0}, // Set chip 0 to go
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_STATE, 2), CHIP_0}, // Pattern state should be correct
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PAT_ERR_COUNT, 0), CHIP_0}, // Pattern error count should be 0
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_1_DOWN, 0xAA), CHIP_0}, // Set chip 0 pattern 1 to 0xAA
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_2_DOWN, 0x55), CHIP_0}, // Set chip 0 pattern 2 to 0x55
};

const uint32_t brgtc6_dual_pattern_fixed_test[][2] = {
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_FACTOR, 1), CHIP_0}, // Set chip 0 clock divider factor to 1
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_FACTOR, 1), CHIP_1}, // Set chip 1 clock divider factor to 1
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_SKEW, 0), CHIP_0},   // Set chip 0 clock divider skew to 0
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_SKEW, 0), CHIP_1},   // Set chip 1 clock divider skew to 0
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_MODE, 1), CHIP_0}, // Set chip 0 pattern mode to pattern 1
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_MODE, 1), CHIP_1}, // Set chip 1 pattern mode to pattern 1
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PAT_BYPASS, 0), CHIP_0}, // Set chip 0 to not bypass pattern gen
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PAT_BYPASS, 0), CHIP_1}, // Set chip 1 to not bypass pattern gen
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_UP_REPAIR_SEL, 0), CHIP_0}, // Set chip 0 up repair select to bit 0 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_UP_REPAIR_SEL, 0), CHIP_1}, // Set chip 1 up repair select to bit 0 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_DOWN_REPAIR_SEL, 0), CHIP_0}, // Set chip 0 down repair select to bit 0 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_DOWN_REPAIR_SEL, 0), CHIP_1}, // Set chip 1 down repair select to bit 0 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_1_UP, 0xAA), CHIP_0}, // Set chip 0 pattern 1 to 0xAA
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_1_UP, 0x03), CHIP_1}, // Set chip 1 pattern 1 to 0xAA
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_2_UP, 0x55), CHIP_0}, // Set chip 0 pattern 2 to 0x55
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_2_UP, 0xFA), CHIP_1}, // Set chip 1 pattern 2 to 0x55
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_GO, 1), CHIP_0}, // Set chip 0 to go
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_GO, 1), CHIP_1}, // Set chip 1 to go
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_STATE, 2), CHIP_0}, // Pattern state should be correct
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_STATE, 2), CHIP_1}, // Pattern state should be correct
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PAT_ERR_COUNT, 0), CHIP_0}, // Pattern error count should be 0
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PAT_ERR_COUNT, 0), CHIP_1}, // Pattern error count should be 0
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_1_DOWN, 0x03), CHIP_0}, // Set chip 0 pattern 1 to 0xAA
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_1_DOWN, 0xAA), CHIP_1}, // Set chip 1 pattern 1 to 0xAA
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_2_DOWN, 0xFA), CHIP_0}, // Set chip 0 pattern 2 to 0x55
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_2_DOWN, 0x55), CHIP_1}, // Set chip 1 pattern 2 to 0x55
};

const uint32_t brgtc6_dual_pattern_lfsr_test[][2] = {
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_FACTOR, 1), CHIP_0}, // Set chip 0 clock divider factor to 1
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_FACTOR, 1), CHIP_1}, // Set chip 1 clock divider factor to 1
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_SKEW, 0), CHIP_0},   // Set chip 0 clock divider skew to 0
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_SKEW, 0), CHIP_1},   // Set chip 1 clock divider skew to 0
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_MODE, 0), CHIP_0}, // Set chip 0 pattern mode to lfsr
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_MODE, 0), CHIP_1}, // Set chip 1 pattern mode to lfsr
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PAT_BYPASS, 0), CHIP_0}, // Set chip 0 to not bypass pattern gen
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PAT_BYPASS, 0), CHIP_1}, // Set chip 1 to not bypass pattern gen
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_UP_REPAIR_SEL, 0), CHIP_0}, // Set chip 0 up repair select to bit 0 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_UP_REPAIR_SEL, 0), CHIP_1}, // Set chip 1 up repair select to bit 0 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_DOWN_REPAIR_SEL, 0), CHIP_0}, // Set chip 0 down repair select to bit 0 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_DOWN_REPAIR_SEL, 0), CHIP_1}, // Set chip 1 down repair select to bit 0 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_GO, 1), CHIP_0}, // Set chip 0 to go
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_GO, 1), CHIP_1}, // Set chip 1 to go
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_STATE, 2), CHIP_0}, // Pattern state should be correct
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_STATE, 2), CHIP_1}, // Pattern state should be correct
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PAT_ERR_COUNT, 0), CHIP_0}, // Pattern error count should be 0
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PAT_ERR_COUNT, 0), CHIP_1}, // Pattern error count should be 0
};

#endif