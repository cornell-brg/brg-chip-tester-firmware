#ifndef OLED_M204_H
#define OLED_M204_H

#include "common.h"

#define OLED_ADDR   0x3C

void init_oled();
void oled_clear_screen();
void oled_row_sel(int row);
void oled_write_text(int row, const char* text);
void oled_write_blank(int row);

#endif