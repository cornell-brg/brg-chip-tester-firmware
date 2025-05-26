#ifndef TCA6408A_H
#define TCA6408A_H

#include "common.h"

#define IO_EXP_ADDR           0x20
#define TCA6408A_INPUT_REG    0x00
#define TCA6408A_OUTPUT_REG   0x01
#define TCA6408A_CONFIG_REG   0x03
#define OLED_RST_PIN          7

void init_tca6408a();
int get_button_num();
void set_output(uint8_t out_pin, uint8_t out_val);

#endif