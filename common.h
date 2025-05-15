#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// SPI Rd/Wr modes
#define RD    0
#define WRT   1
#define RDWRT 2

// Power channel numbers
#define IO 0
#define CORE 1

// Bit data type
typedef uint8_t bit;

// SPI configurations
#define PIN_SCK_0  2
#define PIN_MOSI_0 3
#define PIN_MISO_0 4
#define PIN_CS_0   5

#define PIN_SCK_1  10
#define PIN_MOSI_1 11
#define PIN_MISO_1 12
#define PIN_CS_1   13

// I2C configurations and addresses
#define I2C_CHAN i2c0
#define SDA_PIN 0
#define SCL_PIN 1
#define I2C_BAUD_RATE 400000 // 400kHz
#define OLED_ADDR   0x3C
#define IO_EXP_ADDR 0x20
#define CORE_LDO    0x2C
#define IO_LDO      0x2E
#define CORE_SENS   0x44
#define IO_SENS     0x45
#define CLK_GEN     0x60

#endif