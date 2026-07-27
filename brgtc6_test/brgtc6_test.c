#include "brgtc6_test.h"

// Text buffer for printing test results
char test_res_serial_buf[100];

// Screen row holding the live IO/CORE current readout during a test
#define CURRENT_ROW 2

// Refresh period of the current readout while waiting on the pattern checkers
#define CURRENT_REFRESH_MS 200

// Reads both sense channels and repaints the current row. Skipped entirely when
// the screen is not in use so a USB-triggered test adds no I2C traffic.
static void write_current_row(int write_screen, char* screen_text) {
  if (!write_screen) return;
  sprintf(screen_text, "IO:%4dmA CR:%4dmA ",
    (int)(read_current(IO) * 1000.0 + 0.5),
    (int)(read_current(CORE) * 1000.0 + 0.5));
  oled_write_text(CURRENT_ROW, screen_text);
}

// Waits ms milliseconds, refreshing the current readout as it goes
static void dwell_with_current(int ms, int write_screen, char* screen_text) {
  for (int elapsed = 0; elapsed < ms; elapsed += CURRENT_REFRESH_MS) {
    write_current_row(write_screen, screen_text);
    sleep_ms(ms - elapsed < CURRENT_REFRESH_MS ? ms - elapsed : CURRENT_REFRESH_MS);
  }
}

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

const uint32_t brgtc6_dual_test_clock_combs[3][2] = {
  {100000, 100000},
  {10000, 100000},
  {100000, 10000}
};

void brgtc6_reset() {
  gpio_put(BRGTC6_RESET_PIN_0, 1);
  gpio_put(BRGTC6_RESET_PIN_1, 1);
  sleep_ms(1);
  gpio_put(BRGTC6_RESET_PIN_0, 0);
  gpio_put(BRGTC6_RESET_PIN_1, 0);
}

void brgtc6_decode_spi_msg(bit* spi_buf, int spi_bits, char* msg) {
  uint32_t msg_val;
  bits_to_uint(spi_buf, &msg_val, spi_bits);

  // Decode message type
  switch((msg_val & 0x30000) >> 16) {
    case 0: // Channel message
      sprintf(msg, "Channel %d", msg_val & 0xFF);
      break;
    case 2: // Config message
      switch((msg_val & 0x1F000) >> 12) {
        case 0:
          sprintf(msg, "Loopback %s (raw: 0x%x)", ((msg_val & 0xFFF) != 0) ? "Enabled" : "Disabled", msg_val & 0x3FFFF);
          break;
        case 1:
          sprintf(msg, "Pattern Bypass %s (raw: 0x%x)", ((msg_val & 0xFFF) != 0) ? "Enabled" : "Disabled", msg_val & 0x3FFFF);
          break;
        case 2:
          sprintf(msg, "Pattern Mode %s (raw: 0x%x)", ((msg_val & 0xFFF) != 0) ? "LFSR" : "Pattern 1", msg_val & 0x3FFFF);
          break;
        case 3:
          sprintf(msg, "Pattern 1 Up 0x%x (raw: 0x%x)", msg_val & 0xFFF, msg_val & 0x3FFFF);
          break;
        case 4:
          sprintf(msg, "Pattern 2 Up 0x%x (raw: 0x%x)", msg_val & 0xFFF, msg_val & 0x3FFFF);
          break;
        case 5:
          sprintf(msg, "Pattern 1 Down 0x%x (raw: 0x%x)", msg_val & 0xFFF, msg_val & 0x3FFFF);
          break;
        case 6:
          sprintf(msg, "Pattern 2 Down 0x%x (raw: 0x%x)", msg_val & 0xFFF, msg_val & 0x3FFFF);
          break;
        case 7:
          switch(msg_val & 0xFFF) {
            case 0:
              sprintf(msg, "Pattern State Idle (raw: 0x%x)", msg_val & 0x3FFFF);
              break;
            case 1:
              sprintf(msg, "Pattern State Running (raw: 0x%x)", msg_val & 0x3FFFF);
              break;
            case 2:
              sprintf(msg, "Pattern State Locked (raw: 0x%x)", msg_val & 0x3FFFF);
              break;
            case 3:
              sprintf(msg, "Pattern State Error (raw: 0x%x)", msg_val & 0x3FFFF);
              break;
            default:
              sprintf(msg, "Pattern State Unknown (raw: 0x%x)", msg_val & 0x3FFFF);
              break;
          }
          break;
        case 8:
          sprintf(msg, "Pattern Error Count %d (raw: 0x%x)", msg_val & 0xFFF, msg_val & 0x3FFFF);
          break;
        case 9:
          sprintf(msg, "Go %s (raw: 0x%x)", ((msg_val & 0xFFF) != 0) ? "Enabled" : "Disabled", msg_val & 0x3FFFF);
          break;
        case 10:
          sprintf(msg, "Clock Divider Factor %d (raw: 0x%x)", msg_val & 0xFFF, msg_val & 0x3FFFF);
          break;
        case 11:
          sprintf(msg, "Clock Divider Skew %d (raw: 0x%x)", msg_val & 0xFFF, msg_val & 0x3FFFF);
          break;
        case 12:
          sprintf(msg, "CRC Error Bit %s (raw: 0x%x)", ((msg_val & 0xFFF) != 0) ? "Enabled" : "Disabled", msg_val & 0x3FFFF);
          break;
        case 13:
          sprintf(msg, "Up Repair Select %d (raw: 0x%x)", msg_val & 0xFFF, msg_val & 0x3FFFF);
          break;
        case 14:
          sprintf(msg, "Down Repair Select %d (raw: 0x%x)", msg_val & 0xFFF, msg_val & 0x3FFFF);
          break;
        case 15:
          sprintf(msg, "Pattern Error Count %d (raw: 0x%x)", msg_val & 0xFFF, msg_val & 0x3FFFF);
          break;
        case 16:
          sprintf(msg, "Next Credit Count %d (raw: 0x%x)", msg_val & 0xFFF, msg_val & 0x3FFFF);
          break;
        case 17:
          sprintf(msg, "Credit Reset Delay %d (raw: 0x%x)", msg_val & 0xFFF, msg_val & 0x3FFFF);
          break;
        default:
          sprintf(msg, "Unknown message %x", msg_val & 0x3FFFF);
          break;
      }
  } 
}

void brgtc6_test1(bit* spi_send_buf, bit* spi_recv_buf, int spi_bits, int spi_speed, int write_screen, char* screen_text) {

  // Reset chips
  brgtc6_reset();
  printf("Running test: Single Config Loopback\n");
  if (write_screen) {
    sprintf(screen_text, "  BRGTC6 CFG LPBCK  ");
    oled_write_text(0, screen_text);
  }

  int fail = 0;

  // Test chip 0
  printf("Configuring chip 0...\n");
  if (write_screen) {
    sprintf(screen_text, " Configuring chip 0 ");
    oled_write_text(1, screen_text);
    sprintf(screen_text, "   Running 1/2...   ");
    oled_write_text(3, screen_text);
  }
  write_current_row(write_screen, screen_text);
  for (int i = 0; i < sizeof(brgtc6_single_config_loopback_test_0)/sizeof(brgtc6_single_config_loopback_test_0[0]); i++) {
    uint_to_bits(brgtc6_single_config_loopback_test_0[i][0], spi_send_buf, spi_bits);
    brgtc6_decode_spi_msg(spi_send_buf, spi_bits, test_res_serial_buf);
    printf("Chip %d - Sent: %s - ", brgtc6_single_config_loopback_test_0[i][1], test_res_serial_buf);
    int good_tx = bitwise_spi_read_write(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, brgtc6_single_config_loopback_test_0[i][1]);
    if (!good_tx || !check_bits(spi_recv_buf, spi_send_buf, spi_bits)) {
      printf("No response\n");
      fail = 1;
      break;
    }
    uint32_t spi_recv_val;
    bits_to_uint(spi_recv_buf, &spi_recv_val, spi_bits);
    brgtc6_decode_spi_msg(spi_recv_buf, spi_bits, test_res_serial_buf);
    printf("Rcvd: %s\n", test_res_serial_buf);
    write_current_row(write_screen, screen_text);
  }

  // Fail if error, stop tests
  if (fail) {
    if (write_screen) {
      sprintf(screen_text, "   TEST FAIL 1/2    ");
      oled_write_text(3, screen_text);
    }
    printf("Test Failed\n");
    return;
  }

  // Test chip 1
  printf("Configuring chip 1...\n");
  if (write_screen) {
    sprintf(screen_text, " Configuring chip 1 ");
    oled_write_text(1, screen_text);
    sprintf(screen_text, "   Running 2/2...   ");
    oled_write_text(3, screen_text);
  }
  write_current_row(write_screen, screen_text);
  for (int i = 0; i < sizeof(brgtc6_single_config_loopback_test_1)/sizeof(brgtc6_single_config_loopback_test_1[0]); i++) {
    uint_to_bits(brgtc6_single_config_loopback_test_1[i][0], spi_send_buf, spi_bits);
    brgtc6_decode_spi_msg(spi_send_buf, spi_bits, test_res_serial_buf);
    printf("Chip %d - Sent: %s - ", brgtc6_single_config_loopback_test_1[i][1], test_res_serial_buf);
    int good_tx = bitwise_spi_read_write(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, brgtc6_single_config_loopback_test_1[i][1]);
    if (!good_tx || !check_bits(spi_recv_buf, spi_send_buf, spi_bits)) {
      printf("No response\n");
      fail = 1;
      break;
    }
    uint32_t spi_recv_val;
    bits_to_uint(spi_recv_buf, &spi_recv_val, spi_bits);
    brgtc6_decode_spi_msg(spi_recv_buf, spi_bits, test_res_serial_buf);
    printf("Rcvd: %s\n", test_res_serial_buf);
    write_current_row(write_screen, screen_text);
  }

  write_current_row(write_screen, screen_text);

  // Pass or fail test
  if (fail) {
    if (write_screen) {
      sprintf(screen_text, "   TEST FAIL 2/2    ");
      oled_write_text(3, screen_text);
    }
    printf("Test Failed\n");
  } else {
    if (write_screen) {
      sprintf(screen_text, "   TEST PASS 2/2    ");
      oled_write_text(3, screen_text);
    }
    printf("Test Passed\n");
  } 
}

void brgtc6_test2(bit* spi_send_buf, bit* spi_recv_buf, int spi_bits, int spi_speed, int write_screen, char* screen_text, int* clk0_freq, int* clk1_freq) {
  printf("Running test: Dual Pattern Fixed\n");
  if (write_screen) {
    sprintf(screen_text, "BRGTC6 DUAL PAT FIXD");
    oled_write_text(0, screen_text);
  }

  // Store previous clock frequencies
  int prev_clk0_freq = *clk0_freq;
  int prev_clk1_freq = *clk1_freq;

  // Outer loop through clock combinations
  int fail = 0;
  for (int i = 0; i < sizeof(brgtc6_dual_test_clock_combs)/sizeof(brgtc6_dual_test_clock_combs[0]); i++) {

    // Set the clocks and reset the chips
    set_clock(CLK0, brgtc6_dual_test_clock_combs[i][0], clk0_freq, clk1_freq);
    set_clock(CLK1, brgtc6_dual_test_clock_combs[i][1], clk0_freq, clk1_freq);
    brgtc6_reset();
    printf("Set clock 0: %d - Set clock 1: %d\n", brgtc6_dual_test_clock_combs[i][0], brgtc6_dual_test_clock_combs[i][1]);
    if (write_screen) {
      sprintf(screen_text, "CLK %6.2f/%6.2fMHz", (*clk0_freq)/1000.0, (*clk1_freq)/1000.0);
      oled_write_text(1, screen_text);
      sprintf(screen_text, "   Running %d/%d...   ", i+1, sizeof(brgtc6_dual_test_clock_combs)/sizeof(brgtc6_dual_test_clock_combs[0]));
      oled_write_text(3, screen_text);
    }
    write_current_row(write_screen, screen_text);

    // Send configuration commands and check for errors
    for (int j = 0; j < sizeof(brgtc6_dual_pattern_fixed_test)/sizeof(brgtc6_dual_pattern_fixed_test[0]); j++) {
      if (j == 18) dwell_with_current(10000, write_screen, screen_text);
      uint_to_bits(brgtc6_dual_pattern_fixed_test[j][0], spi_send_buf, spi_bits);
      brgtc6_decode_spi_msg(spi_send_buf, spi_bits, test_res_serial_buf);
      printf("Chip %d - Sent: %s - ", brgtc6_dual_pattern_fixed_test[j][1], test_res_serial_buf);
      int good_tx = bitwise_spi_read_write(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, brgtc6_dual_pattern_fixed_test[j][1]);
      if (!good_tx || !check_bits(spi_recv_buf, spi_send_buf, spi_bits)) {
        printf("No response\n");
        fail = 1;
        break;
      }
      uint32_t spi_recv_val;
      bits_to_uint(spi_recv_buf, &spi_recv_val, spi_bits);
      brgtc6_decode_spi_msg(spi_recv_buf, spi_bits, test_res_serial_buf);
      printf("Rcvd: %s\n", test_res_serial_buf);
      write_current_row(write_screen, screen_text);
    }

    write_current_row(write_screen, screen_text);

    // Fail if error, stop tests
    if (fail) {
      if (write_screen) {
        sprintf(screen_text, "   TEST FAIL %d/%d    ", i+1, sizeof(brgtc6_dual_test_clock_combs)/sizeof(brgtc6_dual_test_clock_combs[0]));
        oled_write_text(3, screen_text);
      }
      printf("Test Failed\n");
      break;
    }
  }

  // If no errors, test passed
  if (!fail) {
    if (write_screen) {
      sprintf(screen_text, "   TEST PASS %d/%d    ", 
        sizeof(brgtc6_dual_test_clock_combs)/sizeof(brgtc6_dual_test_clock_combs[0]), 
        sizeof(brgtc6_dual_test_clock_combs)/sizeof(brgtc6_dual_test_clock_combs[0])
      );
      oled_write_text(3, screen_text);
    }
    printf("Test Passed\n");
  }
  
  // Restore previous clock frequencies
  *clk0_freq = prev_clk0_freq;
  *clk1_freq = prev_clk1_freq;
}

void brgtc6_test3(bit* spi_send_buf, bit* spi_recv_buf, int spi_bits, int spi_speed, int write_screen, char* screen_text, int* clk0_freq, int* clk1_freq){
  printf("Running test: Dual Pattern LFSR\n");
  if (write_screen) {
    sprintf(screen_text, "BRGTC6 DUAL PAT LFSR");
    oled_write_text(0, screen_text);
  }

  // Store previous clock frequencies
  int prev_clk0_freq = *clk0_freq;
  int prev_clk1_freq = *clk1_freq;

  // Outer loop through clock combinations
  int fail = 0;
  for (int i = 0; i < sizeof(brgtc6_dual_test_clock_combs)/sizeof(brgtc6_dual_test_clock_combs[0]); i++) {

    // Set the clocks and reset the chips
    set_clock(CLK0, brgtc6_dual_test_clock_combs[i][0], clk0_freq, clk1_freq);
    set_clock(CLK1, brgtc6_dual_test_clock_combs[i][1], clk0_freq, clk1_freq);
    brgtc6_reset();
    printf("Set clock 0: %d - Set clock 1: %d\n", brgtc6_dual_test_clock_combs[i][0], brgtc6_dual_test_clock_combs[i][1]);
    if (write_screen) {
      sprintf(screen_text, "CLK %6.2f/%6.2fMHz", (*clk0_freq)/1000.0, (*clk1_freq)/1000.0);
      oled_write_text(1, screen_text);
      sprintf(screen_text, "   Running %d/%d...   ", i+1, sizeof(brgtc6_dual_test_clock_combs)/sizeof(brgtc6_dual_test_clock_combs[0]));
      oled_write_text(3, screen_text);
    }
    write_current_row(write_screen, screen_text);

    // Send configuration commands and check for errors
    for (int j = 0; j < sizeof(brgtc6_dual_pattern_lfsr_test)/sizeof(brgtc6_dual_pattern_lfsr_test[0]); j++) {
      if (j == 14) dwell_with_current(10000, write_screen, screen_text);
      uint_to_bits(brgtc6_dual_pattern_lfsr_test[j][0], spi_send_buf, spi_bits);
      brgtc6_decode_spi_msg(spi_send_buf, spi_bits, test_res_serial_buf);
      printf("Chip %d - Sent: %s - ", brgtc6_dual_pattern_lfsr_test[j][1], test_res_serial_buf);
      int good_tx = bitwise_spi_read_write(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, brgtc6_dual_pattern_lfsr_test[j][1]);
      if (!good_tx || !check_bits(spi_recv_buf, spi_send_buf, spi_bits)) {
        printf("No response\n");
        fail = 1;
        break;
      }
      uint32_t spi_recv_val;
      bits_to_uint(spi_recv_buf, &spi_recv_val, spi_bits);
      brgtc6_decode_spi_msg(spi_recv_buf, spi_bits, test_res_serial_buf);
      printf("Rcvd: %s\n", test_res_serial_buf);
      write_current_row(write_screen, screen_text);
    }

    write_current_row(write_screen, screen_text);

    // Fail if error, stop tests
    if (fail) {
      if (write_screen) {
        sprintf(screen_text, "   TEST FAIL %d/%d    ", i+1, sizeof(brgtc6_dual_test_clock_combs)/sizeof(brgtc6_dual_test_clock_combs[0]));
        oled_write_text(3, screen_text);
      }
      printf("Test Failed\n");
      break;
    }
  }

  // If no errors, test passed
  if (!fail) {
    if (write_screen) {
      sprintf(screen_text, "   TEST PASS %d/%d    ", 
        sizeof(brgtc6_dual_test_clock_combs)/sizeof(brgtc6_dual_test_clock_combs[0]), 
        sizeof(brgtc6_dual_test_clock_combs)/sizeof(brgtc6_dual_test_clock_combs[0])
      );
      oled_write_text(3, screen_text);
    }
    printf("Test Passed\n");
  }
  
  // Restore previous clock frequencies
  *clk0_freq = prev_clk0_freq;
  *clk1_freq = prev_clk1_freq;
}