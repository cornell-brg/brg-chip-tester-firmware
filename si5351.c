#include "si5351.h"

uint8_t init_seq[][2] = {
  {2, 0x53},
  {3, 0x00},
  {4, 0x20},
  {7, 0x00},
  {15, 0x00},
  {16, 0x4F},
  {17, 0x4F},
  {18, 0x8C},
  {19, 0x8C},
  {20, 0x8C},
  {21, 0x8C},
  {22, 0x8C},
  {23, 0x8C},
  {26, 0x00},
  {27, 0x01},
  {28, 0x00},
  {29, 0x0E},
  {30, 0x00},
  {31, 0x00},
  {32, 0x00},
  {33, 0x00},
  {42, 0x00},
  {43, 0x01},
  {44, 0x0C},
  {45, 0x00}, // index=24
  {46, 0x00},
  {47, 0x00},
  {48, 0x00},
  {49, 0x00},
  {50, 0x00},
  {51, 0x01},
  {52, 0x0C},
  {53, 0x00}, // index=32
  {54, 0x00},
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

void init_si5351() {
  for (int i = 0; i < sizeof(init_seq) / sizeof(init_seq[0]); i++)
    i2c_write_blocking(I2C_CHAN, CLK_GEN_ADDR, init_seq[i], 2, false);
}

void set_clock(int channel, int freq, int* clk0_freq, int* clk1_freq) {
  switch(channel){
    case 0:
      switch(freq) {
        case 10000:
          init_seq[5][1]  = (*clk1_freq == 200000) ? 0x4F : 0x0F;
          init_seq[6][1]  = (*clk1_freq == 200000) ? 0x4F : 0x0F;
          init_seq[16][1] = (*clk1_freq == 200000) ? 0x0E : 0x10;
          init_seq[22][1] = 0x01;
          init_seq[23][1] = 0x00;
          init_seq[24][1] = 0x2B;
          init_seq[25][1] = 0x00;
          init_seq[33][1] = (*clk1_freq == 200000) ? 0x00 : 0x80;
          break;
        case 50000:
          init_seq[5][1]  = (*clk1_freq == 200000) ? 0x4F : 0x0F;
          init_seq[6][1]  = (*clk1_freq == 200000) ? 0x4F : 0x0F;
          init_seq[16][1] = (*clk1_freq == 200000) ? 0x0E : 0x10;
          init_seq[22][1] = 0x01;
          init_seq[23][1] = 0x00;
          init_seq[24][1] = 0x07;
          init_seq[25][1] = 0x00;
          init_seq[33][1] = (*clk1_freq == 200000) ? 0x00 : 0x80;
          break;
        case 100000:
          init_seq[5][1]  = (*clk1_freq == 200000) ? 0x4F : 0x0F;
          init_seq[6][1]  = (*clk1_freq == 200000) ? 0x4F : 0x0F;
          init_seq[16][1] = (*clk1_freq == 200000) ? 0x0E : 0x10;
          init_seq[22][1] = 0x01;
          init_seq[23][1] = 0x00;
          init_seq[24][1] = 0x02;
          init_seq[25][1] = (*clk1_freq == 200000) ? 0x00 : 0x80;
          init_seq[33][1] = (*clk1_freq == 200000) ? 0x00 : 0x80;
          break;
        case 200000:
          init_seq[5][1]  = 0x4F;
          init_seq[6][1]  = 0x4F;
          init_seq[16][1] = 0x0E;
          init_seq[22][1] = 0x01;
          init_seq[23][1] = 0x0C;
          init_seq[24][1] = 0x00;
          init_seq[25][1] = 0x00;
          init_seq[33][1] = 0x00;
          break;
        default:
          return;
      }
      *clk0_freq = freq;
      break;
    case 1:
      switch(freq) {
        case 10000:
          init_seq[5][1]  = (*clk0_freq == 200000) ? 0x4F : 0x0F;
          init_seq[6][1]  = (*clk0_freq == 200000) ? 0x4F : 0x0F;
          init_seq[16][1] = (*clk0_freq == 200000) ? 0x0E : 0x10;
          init_seq[25][1] = (*clk0_freq == 200000) ? 0x00 : 0x80;
          init_seq[30][1] = 0x01;
          init_seq[31][1] = 0x00;
          init_seq[32][1] = 0x2B;
          init_seq[33][1] = 0x00;
          break;
        case 50000:
          init_seq[5][1]  = (*clk0_freq == 200000) ? 0x4F : 0x0F;
          init_seq[6][1]  = (*clk0_freq == 200000) ? 0x4F : 0x0F;
          init_seq[16][1] = (*clk0_freq == 200000) ? 0x0E : 0x10;
          init_seq[25][1] = (*clk0_freq == 200000) ? 0x00 : 0x80;
          init_seq[30][1] = 0x01;
          init_seq[31][1] = 0x00;
          init_seq[32][1] = 0x07;
          init_seq[33][1] = 0x00;
          break;
        case 100000:
          init_seq[5][1]  = (*clk0_freq == 200000) ? 0x4F : 0x0F;
          init_seq[6][1]  = (*clk0_freq == 200000) ? 0x4F : 0x0F;
          init_seq[16][1] = (*clk0_freq == 200000) ? 0x0E : 0x10;
          init_seq[25][1] = (*clk0_freq == 200000) ? 0x00 : 0x80;
          init_seq[30][1] = 0x01;
          init_seq[31][1] = 0x00;
          init_seq[32][1] = 0x02;
          init_seq[33][1] = (*clk0_freq == 200000) ? 0x00 : 0x80;
          break;
        case 200000:
          init_seq[5][1]  = 0x4F;
          init_seq[6][1]  = 0x4F;
          init_seq[16][1] = 0x0E;
          init_seq[25][1] = 0x00;
          init_seq[30][1] = 0x01;
          init_seq[31][1] = 0x0C;
          init_seq[32][1] = 0x00;
          init_seq[33][1] = 0x00;
          break;
        default:
          return;
      }
      *clk1_freq = freq;
      break;
    default:
      return;
  }
  
  for (int i = 0; i < sizeof(init_seq) / sizeof(init_seq[0]); i++)
    i2c_write_blocking(I2C_CHAN, CLK_GEN_ADDR, init_seq[i], 2, false);
}
