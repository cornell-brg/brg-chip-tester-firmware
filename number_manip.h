#ifndef NUMBER_MANIP_H
#define NUMBER_MANIP_H

#include "common.h"

int get_int(char* src, int offset, int len);
float get_float(char* src, int offset, int len);
void make_bits(char* src, bit* dest, int src_len, int src_offset, int spi_bits);
void make_hex(bit* src, char* dest, int dest_len, int spi_bits);
void uint_to_bits(uint32_t num, bit* bits, int len);
void bits_to_uint(bit* bits, uint32_t* num, int len);
int check_bits(bit* dut, bit* ref, int len);

#endif