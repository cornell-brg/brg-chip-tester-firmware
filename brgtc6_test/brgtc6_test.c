#include "brgtc6_test.h"

const uint32_t brgtc6_single_config_loopback_test_0[][2] = {
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_FACTOR, 2), CHIP_0}, // Set chip 0 clock divider factor to 2
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_SKEW, 0), CHIP_0},   // Set chip 0 clock divider skew to 0
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_MODE, 0), CHIP_0}, // Set chip 0 pattern mode to pattern 1
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PAT_BYPASS, 0), CHIP_0}, // Set chip 0 to not bypass pattern gen
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_UP_REPAIR_SEL, 8), CHIP_0}, // Set chip 0 up repair select to bit 8 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_DOWN_REPAIR_SEL, 2), CHIP_0}, // Set chip 0 down repair select to bit 2 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_GO, 1), CHIP_0}, // Set chip 0 to go
};

const uint32_t brgtc6_single_config_loopback_test_1[][2] = {
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_FACTOR, 2), CHIP_1}, // Set chip 1 clock divider factor to 2
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_CLK_DIV_SKEW, 0), CHIP_1},   // Set chip 1 clock divider skew to 0
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PATTERN_MODE, 0), CHIP_1}, // Set chip 1 pattern mode to pattern 1
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_PAT_BYPASS, 0), CHIP_1}, // Set chip 1 to not bypass pattern gen
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_UP_REPAIR_SEL, 8), CHIP_1}, // Set chip 1 up repair select to bit 8 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_DOWN_REPAIR_SEL, 2), CHIP_1}, // Set chip 1 down repair select to bit 2 of interface
  {BRGTC6_MK_CNFG_MSG(CFG_ADDR_GO, 1), CHIP_1}, // Set chip 1 to go
};

// For single chip board only
const uint brgtc6_single_pattern_fixed_loopback_test[][2] = {
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

void brgtc6_test1(bit* spi_send_buf, bit* spi_recv_buf, int spi_bits, int spi_speed, int write_screen, char* write_text) {

  // Reset chips
  gpio_put(BRGTC6_RESET_PIN_0, 1);
  gpio_put(BRGTC6_RESET_PIN_1, 1);
  gpio_put(BRGTC6_RESET_PIN_0, 0);
  gpio_put(BRGTC6_RESET_PIN_1, 0);
  printf("Running test: Single Config Loopback\n");
  if (write_screen) {
    sprintf(write_text, "  BRGTC6 CFG LPBCK  ");
    oled_write_text(0, write_text);
  }
  int fail = 0;

  // Test chip 0
  printf("Configuring chip 0...\n");
  if (write_screen) {
    sprintf(write_text, " Configuring chip 0 ");
    oled_write_text(1, write_text);
    sprintf(write_text, "   Running 1/2...   ");
    oled_write_text(2, write_text);
    oled_write_blank(3);
  }
  for (int i = 0; i < sizeof(brgtc6_single_config_loopback_test_0)/sizeof(brgtc6_single_config_loopback_test_0[0]); i++) {
    uint_to_bits(brgtc6_single_config_loopback_test_0[i][0], spi_send_buf, spi_bits);
    printf("Sent: 0x%x on %d, ", brgtc6_single_config_loopback_test_0[i][0], brgtc6_single_config_loopback_test_0[i][1]);
    int good_tx = bitwise_spi_read_write(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, brgtc6_single_config_loopback_test_0[i][1]);
    uint32_t spi_recv_val;
    bits_to_uint(spi_recv_buf, &spi_recv_val, spi_bits);
    printf("Rcvd: 0x%x\n", spi_recv_val);
    if (!good_tx || !check_bits(spi_recv_buf, spi_send_buf, spi_bits))
      fail = 1;
  }

  // Fail if error, stop tests
  if (fail) {
    if (write_screen) {
      sprintf(write_text, "   TEST FAIL 1/2    ");
      oled_write_text(3, write_text);
    }
    printf("Test Failed\n");
    return;
  }

  // Test chip 1
  printf("Configuring chip 1...\n");
  if (write_screen) {
    sprintf(write_text, " Configuring chip 1 ");
    oled_write_text(1, write_text);
    sprintf(write_text, "   Running 2/2...   ");
    oled_write_text(2, write_text);
    oled_write_blank(3);
  }
  for (int i = 0; i < sizeof(brgtc6_single_config_loopback_test_1)/sizeof(brgtc6_single_config_loopback_test_1[0]); i++) {
    uint_to_bits(brgtc6_single_config_loopback_test_1[i][0], spi_send_buf, spi_bits);
    printf("Sent: 0x%x on %d, ", brgtc6_single_config_loopback_test_1[i][0], brgtc6_single_config_loopback_test_1[i][1]);
    int good_tx = bitwise_spi_read_write(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, brgtc6_single_config_loopback_test_1[i][1]);
    uint32_t spi_recv_val;
    bits_to_uint(spi_recv_buf, &spi_recv_val, spi_bits);
    printf("Rcvd: 0x%x\n", spi_recv_val);
    if (!good_tx || !check_bits(spi_recv_buf, spi_send_buf, spi_bits))
      fail = 1;
  }

  // Pass or fail test
  if (fail) {
    if (write_screen) {
      sprintf(write_text, "   TEST FAIL 2/2    ");
      oled_write_text(3, write_text);
    }
    printf("Test Failed\n");
  } else {
    if (write_screen) {
      sprintf(write_text, "   TEST PASS 2/2    ");
      oled_write_text(3, write_text);
    }
    printf("Test Passed\n");
  } 
}

void brgtc6_test2(bit* spi_send_buf, bit* spi_recv_buf, int spi_bits, int spi_speed, int write_screen, char* write_text, int* clk0_freq, int* clk1_freq) {
  printf("Running test: Dual Pattern Fixed\n");
  if (write_screen) {
    sprintf(write_text, "BRGTC6 DUAL PAT FIXD");
    oled_write_text(0, write_text);
  }
  int clock_combs[3][2] = {
    {100000, 100000},
    {50000, 100000},
    {100000, 50000}
  };

  // Store previous clock frequencies
  int prev_clk0_freq = *clk0_freq;
  int prev_clk1_freq = *clk1_freq;

  // Outer loop through clock combinations
  int fail = 0;
  for (int i = 0; i < sizeof(clock_combs)/sizeof(clock_combs[0]); i++) {

    // Set the clocks and reset the chips
    *clk0_freq = clock_combs[i][0];
    *clk1_freq = clock_combs[i][1];
    set_clock(CLK0, *clk0_freq);
    set_clock(CLK1, *clk1_freq);
    gpio_put(BRGTC6_RESET_PIN_0, 1);
    gpio_put(BRGTC6_RESET_PIN_1, 1);
    gpio_put(BRGTC6_RESET_PIN_0, 0);
    gpio_put(BRGTC6_RESET_PIN_1, 0);
    printf("Set clocks to %d and %d\n", clock_combs[i][0], clock_combs[i][1]);
    if (write_screen) {
      sprintf(write_text, "  CLK0: %.2fMHz   ", (*clk0_freq)/1000.0);
      oled_write_text(1, write_text);
      sprintf(write_text, "  CLK1: %.2fMHz   ", (*clk1_freq)/1000.0);
      oled_write_text(2, write_text);
      sprintf(write_text, "   Running %d/%d...   ", i+1, sizeof(clock_combs)/sizeof(clock_combs[0]));
      oled_write_text(3, write_text);
    }

    // Send configuration commands and check for errors
    for (int j = 0; j < sizeof(brgtc6_dual_pattern_fixed_test)/sizeof(brgtc6_dual_pattern_fixed_test[0]); j++) {
      if (j == 18) sleep_ms(10000);
      uint_to_bits(brgtc6_dual_pattern_fixed_test[j][0], spi_send_buf, spi_bits);
      printf("Sent: 0x%x on %d, ", brgtc6_dual_pattern_fixed_test[j][0], brgtc6_dual_pattern_fixed_test[j][1]);
      int good_tx = bitwise_spi_read_write(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, brgtc6_dual_pattern_fixed_test[j][1]);
      uint32_t spi_recv_val;
      bits_to_uint(spi_recv_buf, &spi_recv_val, spi_bits);
      printf("Rcvd: 0x%x\n", spi_recv_val);
      if (!good_tx || !check_bits(spi_recv_buf, spi_send_buf, spi_bits))
        fail = 1;
    }

    // Fail if error, stop tests
    if (fail) {
      if (write_screen) {
        sprintf(write_text, "   TEST FAIL %d/%d    ", i+1, sizeof(clock_combs)/sizeof(clock_combs[0]));
        oled_write_text(3, write_text);
      }
      printf("Test Failed\n");
      break;
    }
  }

  // If no errors, test passed
  if (!fail) {
    if (write_screen) {
      sprintf(write_text, "   TEST PASS %d/%d    ", 
        sizeof(clock_combs)/sizeof(clock_combs[0]), 
        sizeof(clock_combs)/sizeof(clock_combs[0])
      );
      oled_write_text(3, write_text);
    }
    printf("Test Passed\n");
  }
  
  // Restore previous clock frequencies
  *clk0_freq = prev_clk0_freq;
  *clk1_freq = prev_clk1_freq;
}

void brgtc6_test3(bit* spi_send_buf, bit* spi_recv_buf, int spi_bits, int spi_speed, int write_screen, char* write_text, int* clk0_freq, int* clk1_freq){
  printf("Running test: Dual Pattern LFSR\n");
  if (write_screen) {
    sprintf(write_text, "BRGTC6 DUAL PAT LFSR");
    oled_write_text(0, write_text);
  }
  int clock_combs[3][2] = {
    {100000, 100000},
    {50000, 100000},
    {100000, 50000}
  };

  // Store previous clock frequencies
  int prev_clk0_freq = *clk0_freq;
  int prev_clk1_freq = *clk1_freq;

  // Outer loop through clock combinations
  int fail = 0;
  for (int i = 0; i < sizeof(clock_combs)/sizeof(clock_combs[0]); i++) {

    // Set the clocks and reset the chips
    *clk0_freq = clock_combs[i][0];
    *clk1_freq = clock_combs[i][1];
    set_clock(CLK0, *clk0_freq);
    set_clock(CLK1, *clk1_freq);
    gpio_put(BRGTC6_RESET_PIN_0, 1);
    gpio_put(BRGTC6_RESET_PIN_1, 1);
    gpio_put(BRGTC6_RESET_PIN_0, 0);
    gpio_put(BRGTC6_RESET_PIN_1, 0);
    printf("Set clocks to %d and %d\n", clock_combs[i][0], clock_combs[i][1]);
    if (write_screen) {
      sprintf(write_text, "  CLK0: %.2fMHz   ", (*clk0_freq)/1000.0);
      oled_write_text(1, write_text);
      sprintf(write_text, "  CLK1: %.2fMHz   ", (*clk1_freq)/1000.0);
      oled_write_text(2, write_text);
      sprintf(write_text, "   Running %d/%d...   ", i+1, sizeof(clock_combs)/sizeof(clock_combs[0]));
      oled_write_text(3, write_text);
    }

    // Send configuration commands and check for errors
    for (int i = 0; i < sizeof(brgtc6_dual_pattern_lfsr_test)/sizeof(brgtc6_dual_pattern_lfsr_test[0]); i++) {
      if (i == 14) sleep_ms(10000);
      uint_to_bits(brgtc6_dual_pattern_lfsr_test[i][0], spi_send_buf, spi_bits);
      printf("Sent: 0x%x on %d, ", brgtc6_dual_pattern_lfsr_test[i][0], brgtc6_dual_pattern_lfsr_test[i][1]);
      int good_tx = bitwise_spi_read_write(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, brgtc6_dual_pattern_lfsr_test[i][1]);
      uint32_t spi_recv_val;
      bits_to_uint(spi_recv_buf, &spi_recv_val, spi_bits);
      printf("Rcvd: 0x%x\n", spi_recv_val);
      if (!good_tx || !check_bits(spi_recv_buf, spi_send_buf, spi_bits))
        fail = 1;
    }

    // Fail if error, stop tests
    if (fail) {
      if (write_screen) {
        sprintf(write_text, "   TEST FAIL %d/%d    ", i+1, sizeof(clock_combs)/sizeof(clock_combs[0]));
        oled_write_text(3, write_text);
      }
      printf("Test Failed\n");
      break;
    }
  }

  // If no errors, test passed
  if (!fail) {
    if (write_screen) {
      sprintf(write_text, "   TEST PASS %d/%d    ", 
        sizeof(clock_combs)/sizeof(clock_combs[0]), 
        sizeof(clock_combs)/sizeof(clock_combs[0])
      );
      oled_write_text(3, write_text);
    }
    printf("Test Passed\n");
  }
  
  // Restore previous clock frequencies
  *clk0_freq = prev_clk0_freq;
  *clk1_freq = prev_clk1_freq;
}