#include "bitwise_spi.h"

void bitwise_spi0_init() {
  gpio_init(PIN_MISO_0);
  gpio_set_dir(PIN_MISO_0, GPIO_IN);
  gpio_pull_down(PIN_MISO_0);

  gpio_init(PIN_CS_0);
  gpio_set_dir(PIN_CS_0, GPIO_OUT);
  gpio_put(PIN_CS_0, 1);

  gpio_init(PIN_SCK_0);
  gpio_set_dir(PIN_SCK_0, GPIO_OUT);
  gpio_put(PIN_SCK_0, 0);

  gpio_init(PIN_MOSI_0);
  gpio_set_dir(PIN_MOSI_0, GPIO_OUT);
  gpio_put(PIN_MOSI_0, 0);
  sleep_us(1);
}

void bitwise_spi1_init() {
  gpio_init(PIN_MISO_1);
  gpio_set_dir(PIN_MISO_1, GPIO_IN);
  gpio_pull_down(PIN_MISO_1);

  gpio_init(PIN_CS_1);
  gpio_set_dir(PIN_CS_1, GPIO_OUT);
  gpio_put(PIN_CS_1, 1);

  gpio_init(PIN_SCK_1);
  gpio_set_dir(PIN_SCK_1, GPIO_OUT);
  gpio_put(PIN_SCK_1, 0);

  gpio_init(PIN_MOSI_1);
  gpio_set_dir(PIN_MOSI_1, GPIO_OUT);
  gpio_put(PIN_MOSI_1, 0);
}

void bitwise_spi_xfer(bit* send_buf, bit* recv_buf, bit* val, bit* rdy, int len, int rw, int spi_speed, int chan) {
  int half_cycle = 1e6 / spi_speed / 2; // Calculate the delay in microseconds

  int pin_sck, pin_mosi, pin_miso, pin_cs;

  switch(chan) {
    case 0:
      pin_sck = PIN_SCK_0;
      pin_mosi = PIN_MOSI_0;
      pin_miso = PIN_MISO_0;
      pin_cs = PIN_CS_0;
      break;
    case 1:
      pin_sck = PIN_SCK_1;
      pin_mosi = PIN_MOSI_1;
      pin_miso = PIN_MISO_1;
      pin_cs = PIN_CS_1;
      break;
    default:
      return; // Invalid channel
  }

  gpio_put(pin_cs, 0); // Enable the chip select

  for (int i = 0; i < len+2; i++) {
      
    // Send MOSI
    if (i == 0) {
      switch(rw) {
        case RD:
          gpio_put(pin_mosi, 0);
          break;
        case WRT:
          gpio_put(pin_mosi, 1);
          break;
        case RDWRT:
          gpio_put(pin_mosi, 1);
          break;
        default:
          gpio_put(pin_mosi, 0);
      }
      sleep_us(half_cycle); // Half-period delay
    } else if (i == 1) {
      switch(rw) {
        case RD:
          gpio_put(pin_mosi, 1);
          break;
        case WRT:
          gpio_put(pin_mosi, 0);
          break;
        case RDWRT:
          gpio_put(pin_mosi, 1);
          break;
        default:
          gpio_put(pin_mosi, 0);
      }
    } else if (rw == RD) {
      gpio_put(pin_mosi, 0);
    } else {
      gpio_put(pin_mosi, send_buf[i-2]);
    }

    // Clock high
    sleep_us(half_cycle); // Half-period delay
    gpio_put(pin_sck, 1);

    // Read MISO if not in write mode
    if (i == 0) {
      *val = gpio_get(pin_miso);
    } else if (i == 1) {
      *rdy = gpio_get(pin_miso);
    } else if (rw != WRT) {
      recv_buf[i-2] = gpio_get(pin_miso);
    }

    // Clock low
    sleep_us(half_cycle); // Another half-period delay
    gpio_put(pin_sck, 0);
  }

  // Disable the chip select
  gpio_put(pin_cs, 1);
}

int bitwise_spi_read_write(bit* send_buf, bit* recv_buf, int spi_bits, int spi_speed, int chan) {
  bit val, rdy;
  int tx_done = 0; 
  int rx_done = 0;
  int ctr = 0;
  int timeout = 500;

  while (!rx_done && ctr < timeout) {
    if (!tx_done && rdy) {
      bitwise_spi_xfer(send_buf, recv_buf, &val, &rdy, spi_bits, RDWRT, spi_speed, chan);
      tx_done = 1;
    } else {
      bitwise_spi_xfer(send_buf, recv_buf, &val, &rdy, spi_bits, RD, spi_speed, chan);
    }
    if (val) rx_done = 1;
    ctr++;
  }
  return rx_done && tx_done;
}

int bitwise_spi_read(bit* recv_buf, int spi_bits, int spi_speed, int chan) {
  bit val, rdy;
  int rx_done = 0;
  int ctr = 0;
  int timeout = 500;
  bit* dummy_send_buf;

  while (!rx_done && ctr < timeout) {
    bitwise_spi_xfer(dummy_send_buf, recv_buf, &val, &rdy, spi_bits, RD, spi_speed, chan);
    if (val) rx_done = 1;
    ctr++;
  }
  return rx_done;
}

int bitwise_spi_write(bit* send_buf, int spi_bits, int spi_speed, int chan) {
  bit val, rdy;
  int tx_done = 0; 
  int rx_done = 0;
  int ctr = 0;
  int timeout = 500;
  bit* dummy_recv_buf;

  while (!tx_done && ctr < timeout) {
    bitwise_spi_xfer(send_buf, dummy_recv_buf, &val, &rdy, spi_bits, WRT, spi_speed, chan);
    if (rdy) tx_done = 1;
    ctr++;
  }
  return tx_done;
}