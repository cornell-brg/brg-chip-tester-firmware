#include "si5351.h"

uint8_t init_seq[][2] = {
  {2, 0x53},
  {3, 0x00},
  {4, 0x20},
  {7, 0x00},
  {15, 0x00},
  {16, 0x0F},
  {17, 0x0F},
  {18, 0x8C},
  {19, 0x8C},
  {20, 0x8C},
  {21, 0x8C},
  {22, 0x8C},
  {23, 0x8C},
  {26, 0x00},
  {27, 0x01},
  {28, 0x00},
  {29, 0x10},
  {30, 0x00},
  {31, 0x00},
  {32, 0x00},
  {33, 0x00},
  {42, 0x00},
  {43, 0x01},
  {44, 0x00},
  {45, 0x02}, // index=24
  {46, 0x80},
  {47, 0x00},
  {48, 0x00},
  {49, 0x00},
  {50, 0x00},
  {51, 0x01},
  {52, 0x00},
  {53, 0x02}, // index=32
  {54, 0x80},
  {55, 0x00},
  {56, 0x00},
  {57, 0x00},
  {90, 0x00},
  {91, 0x00},
  {149, 0x00},
  {150, 0x00},
  {151, 0x00},
  {152, 0x00},
  {153, 0x00},
  {154, 0x00},
  {155, 0x00},
  {162, 0x00},
  {163, 0x00},
  {164, 0x00},
  {165, 0x00},
  {166, 0x00},
  {183, 0x92}
};

// The SI5351 can come up holding SDA low and lock up the whole I2C bus. The
// ECE6745 tester recovers by power-cycling it, but its VDD is hard-wired here,
// so instead clock the bus free and retry. All SI5351 transfers use timeouts so
// a stuck bus can never hang the firmware.

// SDA and SCL both read high when no device is holding the bus.
bool i2c_bus_free() {
  return gpio_get(SDA_PIN) && gpio_get(SCL_PIN);
}

// Standard I2C bus recovery: take over the pins as open-drain GPIOs (output-low
// drives 0, input releases to the pull-up) and pulse SCL until the stuck device
// finishes its byte and releases SDA, then send a STOP and reset the I2C block.
// Cannot help if a device is holding SCL low.
void i2c_bus_recover() {
  gpio_init(SDA_PIN);
  gpio_init(SCL_PIN);
  gpio_pull_up(SDA_PIN);
  gpio_pull_up(SCL_PIN);
  sleep_us(5);

  for (int i = 0; i < 9 && !gpio_get(SDA_PIN); i++) {
    gpio_set_dir(SCL_PIN, GPIO_OUT); sleep_us(5);
    gpio_set_dir(SCL_PIN, GPIO_IN);  sleep_us(5);
  }

  // STOP condition: SDA rises while SCL is high
  gpio_set_dir(SCL_PIN, GPIO_OUT); sleep_us(5);
  gpio_set_dir(SDA_PIN, GPIO_OUT); sleep_us(5);
  gpio_set_dir(SCL_PIN, GPIO_IN);  sleep_us(5);
  gpio_set_dir(SDA_PIN, GPIO_IN);  sleep_us(5);

  i2c_init(I2C_CHAN, I2C_BAUD_RATE);
  gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
}

// Returns the device status register (reg 0), or 0xFF if the read failed
static uint8_t si5351_read_status() {
  uint8_t reg = 0;
  uint8_t data = 0xFF;
  if (i2c_write_timeout_us(I2C_CHAN, CLK_GEN_ADDR, &reg, 1, true, SI5351_I2C_TIMEOUT_US) != 1) return 0xFF;
  if (i2c_read_timeout_us(I2C_CHAN, CLK_GEN_ADDR, &data, 1, false, SI5351_I2C_TIMEOUT_US) != 1) return 0xFF;
  return data;
}

// Writes the full register sequence and checks that the SI5351 let go of the
// bus afterwards and reports the PLL locked
static bool si5351_write_seq() {
  for (int i = 0; i < sizeof(init_seq) / sizeof(init_seq[0]); i++)
    if (i2c_write_timeout_us(I2C_CHAN, CLK_GEN_ADDR, init_seq[i], 2, false, SI5351_I2C_TIMEOUT_US) != 2)
      return false;
  sleep_ms(20); // allow PLL to lock before sampling status
  return i2c_bus_free() && (si5351_read_status() & SI5351_STATUS_FAULT_MASK) == 0;
}

// Writes the register sequence, recovering the bus and retrying on failure
static bool si5351_write_seq_with_retry() {
  for (int attempt = 0; attempt < SI5351_RETRIES; attempt++) {
    if (!i2c_bus_free()) i2c_bus_recover();
    if (si5351_write_seq()) return true;
    i2c_bus_recover();
    sleep_ms(10);
  }
  return false;
}

bool init_si5351() {
  // Wait for the SI5351 to finish its own power-up initialization
  for (int i = 0; i < 50 && (si5351_read_status() & SI5351_STATUS_SYS_INIT); i++) {
    if (!i2c_bus_free()) i2c_bus_recover();
    sleep_ms(2);
  }
  return si5351_write_seq_with_retry();
}

void set_clock(int channel, int freq, int* clk0_freq, int* clk1_freq) {
  switch(channel){
    case 0:
      switch(freq) {
        case 10:
          init_seq[22][1] = 0x04;
          init_seq[23][1] = 0x62;
          init_seq[24][1] = 0xBD;
          init_seq[25][1] = 0x20;
          break;
        case 10000:
          init_seq[22][1] = 0x01;
          init_seq[23][1] = 0x00;
          init_seq[24][1] = 0x2B;
          init_seq[25][1] = 0x00;
          break;
        case 50000:
          init_seq[22][1] = 0x01;
          init_seq[23][1] = 0x00;
          init_seq[24][1] = 0x07;
          init_seq[25][1] = 0x00;
          break;
        case 100000:
          init_seq[22][1] = 0x01;
          init_seq[23][1] = 0x00;
          init_seq[24][1] = 0x02;
          init_seq[25][1] = 0x80;
          break;
        default:
          return;
      }
      *clk0_freq = freq;
      break;
    case 1:
      switch(freq) {
        case 10:
          init_seq[30][1] = 0x04;
          init_seq[31][1] = 0x62;
          init_seq[32][1] = 0xBD;
          init_seq[33][1] = 0x20;
          break;
        case 10000:
          init_seq[30][1] = 0x01;
          init_seq[31][1] = 0x00;
          init_seq[32][1] = 0x2B;
          init_seq[33][1] = 0x00;
          break;
        case 50000:
          init_seq[30][1] = 0x01;
          init_seq[31][1] = 0x00;
          init_seq[32][1] = 0x07;
          init_seq[33][1] = 0x00;
          break;
        case 100000:
          init_seq[30][1] = 0x01;
          init_seq[31][1] = 0x00;
          init_seq[32][1] = 0x02;
          init_seq[33][1] = 0x80;
          break;
        default:
          return;
      }
      *clk1_freq = freq;
      break;
    default:
      return;
  }

  si5351_write_seq_with_retry();
}
