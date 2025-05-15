#ifndef BITWISE_SPI_H
#define BITWISE_SPI_H

#include "common.h"

void bitwise_spi0_init();
void bitwise_spi1_init();
void bitwise_spi_xfer(bit* send_buf, bit* recv_buf, bit* val, bit* rdy, int len, int rw, int spi_speed, int chan);
int bitwise_spi_read_write(bit* send_buf, bit* recv_buf, int spi_bits, int spi_speed, int chan);
int bitwise_spi_read(bit* recv_buf, int spi_bits, int spi_speed, int chan);
int bitwise_spi_write(bit* send_buf, int spi_bits, int spi_speed, int chan);

#endif