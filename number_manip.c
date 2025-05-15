#include "number_manip.h"

int get_int(char* src, int offset, int len) {
  int num = 0;
  int is_negative = 0;

  if (src[offset] == '-') {
    is_negative = 1;
    offset++;
  }

  while (src[offset] >= '0' && src[offset] <= '9' && offset < len) {
    num = num * 10 + (src[offset] - '0');
    offset++;
  }

  return is_negative ? -num : num;
}

float get_float(char* src, int offset, int len) {
  float num = 0.0f;
  float divisor = 10.0f;
  int is_negative = 0;

  if (src[offset] == '-') {
    is_negative = 1;
    offset++;
  }

  // Parse integer part
  while (src[offset] >= '0' && src[offset] <= '9' && offset < len) {
    num = num * 10.0f + (src[offset] - '0');
    offset++;
  }

  // Parse fractional part
  if (src[offset] == '.') {
    offset++;
    while (src[offset] >= '0' && src[offset] <= '9' && offset < len) {
      num += (src[offset] - '0') / divisor;
      divisor *= 10.0f;
      offset++;
    }
  }

  // Round to two significant digits
  num = (int)(num * 100 + 0.5f) / 100.0f;
  return is_negative ? -num : num;
}

void make_bits(char* src, bit* dest, int src_len, int src_offset, int spi_bits) {
  uint8_t byte;
  int next_dest_idx;
  for (int i = src_len-1; i >= src_offset; i--) {
    byte = src[i] >= '0' && src[i] <= '9' ? src[i] - '0' : (src[i] - 'A') + 0xA;
    for (int j = 0; j < 4; j++) {
      next_dest_idx = (i-src_offset) * 4 + j - ((src_len-src_offset)*4 - spi_bits);
      if (next_dest_idx >= 0) 
        dest[next_dest_idx] = (byte >> (3 - j)) & 0x01;
    }
  }
}

void make_hex(bit* src, char* dest, int dest_len, int spi_bits) {
  int next_src_idx;
  for (int i = dest_len-1; i >= 0; i--) {
    dest[i] = 0;
    for (int j = 0; j < 4; j++) {
      next_src_idx = i * 4 + j - (dest_len * 4 - spi_bits);
      dest[i] = (dest[i] << 1) | (next_src_idx < 0 ? 0 : src[next_src_idx]);
    }
    if (dest[i] < 0xA) dest[i] += '0';
    else dest[i] += 'A' - 0xA;
  }
}

void uint_to_bits(uint32_t num, bit* bits, int len) {
  for (int i = 0; i < len; i++) {
    bits[i] = (num >> (len - 1 - i)) & 0x01;
  }
}

void bits_to_uint(bit* bits, uint32_t* num, int len) {
  *num = 0;
  for (int i = 0; i < len; i++) {
    *num = (*num << 1) | bits[i];
  }
}

int check_bits(bit* dut, bit* ref, int len) {
  int i;
  for (i = 0; i < len; i++) {
      if (dut[i] != ref[i]) return 0;
  }
  return 1;
}