// General includes
#include "number_manip.h"
#include "bitwise_spi.h"
#include "oled_m204.h"
#include "tca6408a.h"
#include "mcp4562.h"
#include "ina220.h"
#include "si5351.h"
#include "pico/multicore.h"
#include "tusb.h"

// Test includes
#include "brgtc6_test/brgtc6_test.h"

// Text buffer for OLED screen
char screen_text[21];

// SPI parameters
int spi_speed = 1000; // Default SPI speed
int spi_bits  = 18;   // Default SPI bits

// SPI buffers
bit spi_send_buf[50];
bit spi_recv_buf[50];
char spi_recv_buf_hex[50];

// USB buffer
char usb_recv_buf[256];    // usb_recv_buf to store input
int  usb_recv_buf_idx = 0; // Index for storing characters in the usb_recv_buf

// Holds the frequency of the clocks
int clk0_freq = 200000;
int clk1_freq = 200000;

// Holds the last user button pressed
int last_button_num = 1;
#define USB_SCREEN 3

void core1_entry() {
  char next_c;
  while (true) {

    if (tud_cdc_available()) {
      usb_recv_buf_idx = tud_cdc_read(usb_recv_buf, sizeof(usb_recv_buf) - 1);
      usb_recv_buf[usb_recv_buf_idx] = '\0';

      for (int i = 0; i < usb_recv_buf_idx; i++) {
        usb_recv_buf[i] = toupper(usb_recv_buf[i]);
      }

      // Handle serial data
      if (usb_recv_buf[0] == 'T') {
        if (usb_recv_buf[1] == '1')
          brgtc6_test1(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, 0, screen_text);
        if (usb_recv_buf[1] == '2')
          brgtc6_test2(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, 0, screen_text, &clk0_freq, &clk1_freq);
        else if (usb_recv_buf[1] == '3')
          brgtc6_test3(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, 0, screen_text, &clk0_freq, &clk1_freq);
      } else if (usb_recv_buf[0] == 'B') {
        make_bits(usb_recv_buf, spi_send_buf, usb_recv_buf_idx, 2, spi_bits);
        int good_tx = bitwise_spi_read_write(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, usb_recv_buf[1] - '0');
        make_hex(spi_recv_buf, spi_recv_buf_hex, spi_bits / 4 + 1, spi_bits);
        spi_recv_buf_hex[spi_bits / 4 + 1] = '\0';
        if (good_tx) {
          printf("Rd/Wr Good\n");
          printf("Response -> 0x");
          printf(spi_recv_buf_hex);
        } else printf("Rd/Wr Fail");
        printf("\n"); 
      } else if (usb_recv_buf[0] == 'R') {
        int good_tx = bitwise_spi_read(spi_recv_buf, spi_bits, spi_speed, usb_recv_buf[1] - '0');
        make_hex(spi_recv_buf, spi_recv_buf_hex, spi_bits / 4 + 1, spi_bits);
        spi_recv_buf_hex[spi_bits / 4 + 1] = '\0';
        if (good_tx) {
          printf("Read Good\n");
          printf("Response -> 0x");
          printf(spi_recv_buf_hex);
        } else printf("Read Fail");
        printf("\n");
      } else if (usb_recv_buf[0] == 'W') {
        make_bits(usb_recv_buf, spi_send_buf, usb_recv_buf_idx, 2, spi_bits);
        int good_tx = bitwise_spi_write(spi_send_buf, spi_bits, spi_speed, usb_recv_buf[1] - '0');
        if (good_tx) printf("Write Good\n");
        else printf("Write Fail\n");
      } else if (usb_recv_buf[0] == 'S' && usb_recv_buf[1] == 'S') {
        int speed = get_int(usb_recv_buf, 2, usb_recv_buf_idx);
        printf("SPI speed -> %dbps\n", speed);
        spi_speed = speed;
      } else if (usb_recv_buf[0] == 'S' && usb_recv_buf[1] == 'B') {
        int bits = get_int(usb_recv_buf, 2, usb_recv_buf_idx);
        printf("SPI bits -> %d\n", bits);
        spi_bits = bits;
      } else if (usb_recv_buf[0] == 'V' && usb_recv_buf[1] == 'C') {
        float core_voltage = get_float(usb_recv_buf, usb_recv_buf[2] == 'P' ? 3 : 2, usb_recv_buf_idx);
        set_voltage(CORE, core_voltage, usb_recv_buf[2] == 'p');
        if (usb_recv_buf[2] == 'p') {
          sprintf(screen_text, "      PROGRAM       ");
          printf("Core voltage programmed -> %.2f\n", core_voltage);
        } else {
          sprintf(screen_text, "        SET         ");
          printf("Core voltage set -> %.2fV\n", core_voltage);
        }
      } else if (usb_recv_buf[0] == 'V' && usb_recv_buf[1] == 'I') {
        float io_voltage = get_float(usb_recv_buf, usb_recv_buf[2] == 'P' ?  3 : 2, usb_recv_buf_idx);
        set_voltage(IO, io_voltage, usb_recv_buf[2] == 'P');
        if (usb_recv_buf[2] == 'P') {
          sprintf(screen_text, "      PROGRAM       ");
          printf("IO voltage programmed -> %.2f\n", io_voltage);
        } else {
          sprintf(screen_text, "        SET         ");
          printf("IO voltage set -> %.2fV\n", io_voltage);
        }
      } else if (usb_recv_buf[0] == 'C' && usb_recv_buf[1] == '0') {
        set_clock(CLK0, get_int(usb_recv_buf, 2, usb_recv_buf_idx), &clk0_freq, &clk1_freq);
        printf("CLK0 set -> %dkHz\n", clk0_freq);
      } else if (usb_recv_buf[0] == 'C' && usb_recv_buf[1] == '1') {
        set_clock(CLK1, get_int(usb_recv_buf, 2, usb_recv_buf_idx), &clk0_freq, &clk1_freq);
        printf("CLK1 set -> %dKHz\n", clk1_freq);
      }
      else if (usb_recv_buf[0] == 'H') {
        printf("Help:\n");
        printf("r<data> - Read data\n");
        printf("w<data> - Write data\n");
        printf("ss<speed> - Set SPI speed\n");
        printf("sb<bits> - Set SPI bits\n");
        printf("h - Help\n");
      } else printf("Invalid command\n");

      // Reset buffer index
      usb_recv_buf_idx = 0;
    }
  }
}

int main() {

  // Allow voltages to stabilize
  sleep_ms(100);

  // Initialize standard I/O
  stdio_init_all();

  // Initialize bitwise SPI modules (comment out if not using that channel)
  bitwise_spi0_init();
  bitwise_spi1_init();

  // Initialize I2C module
  i2c_init(I2C_CHAN, I2C_BAUD_RATE);
  gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);

  // Initialize TCA6408A GPIO expander
  init_tca6408a();

  // Initialize OLED screen and reset
  sleep_ms(1);
  set_output(OLED_RST_PIN, 0);
  sleep_ms(1);
  set_output(OLED_RST_PIN, 1);
  init_oled();
  oled_clear_screen();

  // Initialize INA220 voltage/current sensors
  init_ina220s();

  // Initialize SI5351 clock generator
  init_si5351();

  // Reset BRGTC6 chips
  brgtc6_reset();

  // Launch USB handling core
  multicore_launch_core1(core1_entry);

  // Initialize BRGTC6 reset pins
  gpio_init(BRGTC6_RESET_PIN_0);
  gpio_set_dir(BRGTC6_RESET_PIN_0, GPIO_OUT);
  gpio_put(BRGTC6_RESET_PIN_0, 1);
  gpio_init(BRGTC6_RESET_PIN_1);
  gpio_set_dir(BRGTC6_RESET_PIN_1, GPIO_OUT);
  gpio_put(BRGTC6_RESET_PIN_1, 1);
  brgtc6_reset();

  int run_test = 1;

  last_button_num = 1;
  int curr_button_num = 0;
  while (true) {
    curr_button_num = get_button_num();
    if (curr_button_num != last_button_num && curr_button_num != 0) {
      oled_clear_screen();
      run_test = 1;
      last_button_num = curr_button_num;
    } else if (curr_button_num != 0) {
      run_test = 1;
    }
    if (last_button_num == 1) {
      sprintf(screen_text, "IO:%.2fV,%.2fA,%.2fW", read_voltage(IO), read_current(IO), read_power(IO));
      oled_write_text(0, screen_text);
      sprintf(screen_text, "CR:%.2fV,%.2fA,%.2fW", read_voltage(CORE), read_current(CORE), read_power(CORE));
      oled_write_text(1, screen_text);
      sprintf(screen_text, "  CLK0: %.2fMHz   ", clk0_freq/1000.0);
      oled_write_text(2, screen_text);
      sprintf(screen_text, "  CLK1: %.2fMHz   ", clk1_freq/1000.0);
      oled_write_text(3, screen_text);
    } else if (last_button_num == 2) {
      if (run_test) {
        brgtc6_test1(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, 1, screen_text);
        run_test = 0;
      }
    } else if (last_button_num == 3) {
      if (run_test) {
        brgtc6_test2(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, 1, screen_text, &clk0_freq, &clk1_freq);
        run_test = 0;
      }
    } else if (last_button_num == 4) {
      if (run_test) {
        brgtc6_test3(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, 1, screen_text, &clk0_freq, &clk1_freq);
        run_test = 0;
      }
    }
    sleep_ms(100);
  }

  return 0;
}