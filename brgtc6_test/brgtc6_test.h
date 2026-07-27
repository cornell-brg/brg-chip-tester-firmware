#ifndef BRGTC6_TEST_H
#define BRGTC6_TEST_H

#include "brgtc6_test_utils.h"
#include "../bitwise_spi.h"
#include "../number_manip.h"
#include "../si5351.h"
#include "../oled_m204.h"
#include "../ina220.h"

void brgtc6_reset();
void brgtc6_decode_spi_msg(bit* spi_recv_buf, int spi_bits, char* write_text);
void brgtc6_test1(bit* spi_send_buf, bit* spi_recv_buf, int spi_bits, int spi_speed, int write_screen, char* write_text);
void brgtc6_test2(bit* spi_send_buf, bit* spi_recv_buf, int spi_bits, int spi_speed, int write_screen, char* write_text, int* clk0_freq, int* clk1_freq);
void brgtc6_test3(bit* spi_send_buf, bit* spi_recv_buf, int spi_bits, int spi_speed, int write_screen, char* write_text, int* clk0_freq, int* clk1_freq);

#endif