// General includes
#include "number_manip.h"
#include "i2c_custom.h"
#include "bitwise_spi.h"
#include "oled_m204.h"
#include "tca6408a.h"
#include "mcp4562.h"
#include "ina220.h"
#include "si5351.h"
#include "pico/multicore.h"

// Test includes
#include "brgtc6_test/brgtc6_test.h"

// Text to write to the screen
char write_text[21];

// SPI parameters
int spi_speed = 1000; // Default SPI speed
int spi_bits  = 18;   // Default SPI bits

// SPI buffers
bit spi_send_buf[50];
bit spi_recv_buf[50];
char spi_recv_buf_hex[50];

// USB buffer
char usb_recv_buf[256];    // usb_recv_buf to store input
int  usb_recv_buf_idx = 0; // Index for storing characters in the usb_recv_buf

// Holds the frequency of the clocks
int clk0_freq = 50000;
int clk1_freq = 50000;

// Holds the last user button pressed
int last_button_num = 1;
#define USB_SCREEN 3

#define BRGTC6_RESET_PIN_0 6
#define BRGTC6_RESET_PIN_1 7

void core1_entry() {
    char next_c;
    while (true) {

        // Read characters until end of line
        while ((next_c = getchar()) != '\0') {
            if (usb_recv_buf_idx < sizeof(usb_recv_buf)) {
                if (usb_recv_buf_idx != 0 && (usb_recv_buf[0] == 'r' || usb_recv_buf[0] == 'w' || usb_recv_buf[0] == 'b') 
                    && next_c >= 'a' && next_c <= 'z') next_c -= 32;
                usb_recv_buf[usb_recv_buf_idx++] = next_c;
            }
        }

        // Handle serial data
        if (usb_recv_buf[0] == 't') {
            int fail = 0;   
            gpio_put(BRGTC6_RESET_PIN_0, 1); // Enter reset
            gpio_put(BRGTC6_RESET_PIN_1, 1); // Enter reset
            gpio_put(BRGTC6_RESET_PIN_0, 0); // Exit reset
            gpio_put(BRGTC6_RESET_PIN_1, 0); // Exit reset
            if (usb_recv_buf[1] == '1') { 
                printf("Running test: Single Config Loopback\n");
                for (int i = 0; i < sizeof(brgtc6_single_config_loopback_test)/sizeof(brgtc6_single_config_loopback_test[0]); i++) {
                    uint_to_bits(brgtc6_single_config_loopback_test[i][0], spi_send_buf, spi_bits);
                    printf("Sent: 0x%x, ", brgtc6_single_config_loopback_test[i][0]);
                    int good_spi = bitwise_spi_read_write(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, brgtc6_single_config_loopback_test[i][1]);
                    uint32_t spi_recv_val;
                    bits_to_uint(spi_recv_buf, &spi_recv_val, spi_bits);
                    printf("Rcvd: 0x%x\n", spi_recv_val);
                    if (!good_spi || !check_bits(spi_recv_buf, spi_send_buf, spi_bits)) {
                        fail = 1;
                    }
                }
            } else if (usb_recv_buf[1] == '2') {
                printf("Running test: Single Pattern Fixed Loopback\n");
                for (int i = 0; i < sizeof(brgtc6_single_pattern_fixed_loopback_test)/sizeof(brgtc6_single_pattern_fixed_loopback_test[0]); i++) {
                    uint_to_bits(brgtc6_single_pattern_fixed_loopback_test[i][0], spi_send_buf, spi_bits);
                    printf("Sent: 0x%x, ", brgtc6_single_pattern_fixed_loopback_test[i][0]);
                    int good_spi = bitwise_spi_read_write(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, brgtc6_single_pattern_fixed_loopback_test[i][1]);
                    uint32_t spi_recv_val;
                    bits_to_uint(spi_recv_buf, &spi_recv_val, spi_bits);
                    printf("Rcvd: 0x%x\n", spi_recv_val);
                    if (!good_spi || !check_bits(spi_recv_buf, spi_send_buf, spi_bits)) {
                        fail = 1;
                    }
                }
            } else if (usb_recv_buf[1] == '3') {
                printf("Running test: Dual Pattern Fixed\n");
                for (int i = 0; i < sizeof(brgtc6_dual_pattern_fixed_test)/sizeof(brgtc6_dual_pattern_fixed_test[0]); i++) {
                    if (i == 18) sleep_ms(10000);
                    uint_to_bits(brgtc6_dual_pattern_fixed_test[i][0], spi_send_buf, spi_bits);
                    printf("Sent: 0x%x, ", brgtc6_dual_pattern_fixed_test[i][0]);
                    int good_spi = bitwise_spi_read_write(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, brgtc6_dual_pattern_fixed_test[i][1]);
                    uint32_t spi_recv_val;
                    bits_to_uint(spi_recv_buf, &spi_recv_val, spi_bits);
                    printf("Rcvd: 0x%x\n", spi_recv_val);
                    if (!good_spi || !check_bits(spi_recv_buf, spi_send_buf, spi_bits)) {
                        fail = 1;
                    }
                }
            } else if (usb_recv_buf[1] == '4') {
                printf("Running test: Dual Pattern LFSR\n");
                for (int i = 0; i < sizeof(brgtc6_dual_pattern_lfsr_test)/sizeof(brgtc6_dual_pattern_lfsr_test[0]); i++) {
                    if (i == 14) sleep_ms(30000);
                    uint_to_bits(brgtc6_dual_pattern_lfsr_test[i][0], spi_send_buf, spi_bits);
                    printf("Sent: 0x%x, ", brgtc6_dual_pattern_lfsr_test[i][0]);
                    int good_spi = bitwise_spi_read_write(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, brgtc6_dual_pattern_lfsr_test[i][1]);
                    uint32_t spi_recv_val;
                    bits_to_uint(spi_recv_buf, &spi_recv_val, spi_bits);
                    printf("Rcvd: 0x%x\n", spi_recv_val);
                    if (!good_spi || !check_bits(spi_recv_buf, spi_send_buf, spi_bits)) {
                        fail = 1;
                    }
                }    
            }
            if (fail) {
                printf("Test Failed\n");
                if (last_button_num == USB_SCREEN) {
                    oled_clear_screen();
                    sprintf(write_text, "      TEST FAIL     ");
                    oled_write_text(1, write_text);
                }
            } else {
                printf("Test Passed\n");
                if (last_button_num == USB_SCREEN) {
                    oled_clear_screen();
                    sprintf(write_text, "      TEST PASS     ");
                    oled_write_text(1, write_text);
                }
            }
        } else if (usb_recv_buf[0] == 'b') {
            make_bits(usb_recv_buf, spi_send_buf, usb_recv_buf_idx, 1, spi_bits);
            int good_spi = bitwise_spi_read_write(spi_send_buf, spi_recv_buf, spi_bits, spi_speed, 0);
            make_hex(spi_recv_buf, spi_recv_buf_hex, spi_bits / 4 + 1, spi_bits);
            usb_recv_buf[usb_recv_buf_idx] = '\0';
            spi_recv_buf_hex[spi_bits / 4 + 1] = '\0';
            if (last_button_num == USB_SCREEN) {
                oled_clear_screen();
                if (good_spi) sprintf(write_text, "      RD/WR GOOD    ");
                else sprintf(write_text,          "      RD/WR FAIL    ");
                oled_write_text(0, write_text);
                sprintf(write_text, "     Req: 0x%s", usb_recv_buf+1);
                oled_write_text(1, write_text);
                sprintf(write_text, "     Rsp: 0x%s", spi_recv_buf_hex);
                oled_write_text(2, write_text);
            }
            if (good_spi) {
                printf("Rd/Wr Good\n");
                printf("Response -> 0x");
                printf(spi_recv_buf_hex);
            } else printf("Rd/Wr Fail");
            printf("\n"); 
        } else if (usb_recv_buf[0] == 'r') {
            int good_spi = bitwise_spi_read(spi_recv_buf, spi_bits, spi_speed, 0);
            make_hex(spi_recv_buf, spi_recv_buf_hex, spi_bits / 4 + 1, spi_bits);
            spi_recv_buf_hex[spi_bits / 4 + 1] = '\0';
            if (last_button_num == USB_SCREEN) {
                oled_clear_screen();
                if (good_spi) sprintf(write_text, "      READ GOOD     ");
                else sprintf(write_text,          "      READ FAIL     ");
                oled_write_text(1, write_text);
                sprintf(write_text, "     Rsp: 0x%s", spi_recv_buf_hex);
                oled_write_text(2, write_text);
            }
            if (good_spi) {
                printf("Read Good\n");
                printf("Response -> 0x");
                printf(spi_recv_buf_hex);
            } else printf("Read Fail");
            printf("\n");
        } else if (usb_recv_buf[0] == 'w') {
            make_bits(usb_recv_buf, spi_send_buf, usb_recv_buf_idx, 1, spi_bits);
            int good_spi = bitwise_spi_write(spi_send_buf, spi_bits, spi_speed, 0);
            usb_recv_buf[usb_recv_buf_idx] = '\0';
            if (last_button_num == USB_SCREEN) {
                oled_clear_screen();
                if (good_spi) sprintf(write_text, "      WRITE GOOD    ");
                else sprintf(write_text,          "      WRITE FAIL    ");
                oled_write_text(1, write_text);
                sprintf(write_text, "     Req: 0x%s", usb_recv_buf+1);
                oled_write_text(2, write_text);
            }
            if (good_spi) printf("Write Good\n");
            else printf("Write Fail\n");
        } else if (usb_recv_buf[0] == 's' && usb_recv_buf[1] == 's') {
            int speed = get_int(usb_recv_buf, 2, usb_recv_buf_idx);
            if (last_button_num == USB_SCREEN) {
                oled_clear_screen();
                sprintf(write_text, " SPI SPEED -> %d", speed);
                oled_write_text(1, write_text);
            }
            printf("SPI speed -> %dbps\n", speed);
            spi_speed = speed;
        } else if (usb_recv_buf[0] == 's' && usb_recv_buf[1] == 'b') {
            int bits = get_int(usb_recv_buf, 2, usb_recv_buf_idx);
            if (last_button_num == USB_SCREEN) {
                oled_clear_screen();
                sprintf(write_text, "  SPI BITS -> %d", bits);
                oled_write_text(1, write_text);
            }
            printf("SPI bits -> %d\n", bits);
            spi_bits = bits;
        } else if (usb_recv_buf[0] == 'v' && usb_recv_buf[1] == 'c') {
            float core_voltage = get_float(usb_recv_buf, usb_recv_buf[2] == 'p' ? 3 : 2, usb_recv_buf_idx);
            set_voltage(CORE, core_voltage, usb_recv_buf[2] == 'p');
            oled_clear_screen();
            if (usb_recv_buf[2] == 'p') {
                sprintf(write_text, "      PROGRAM       ");
                printf("Core voltage programmed -> %.2f\n", core_voltage);
            } else {
                sprintf(write_text, "        SET         ");
                printf("Core voltage set -> %.2fV\n", core_voltage);
            }
            if (last_button_num == USB_SCREEN) {
                oled_write_text(1, write_text);
                sprintf(write_text, "   Core V -> %.2fV", core_voltage);
                oled_write_text(2, write_text);
                sprintf(write_text, "%.2fV, %.2fA, %.2fW", read_voltage(CORE), read_current(CORE), read_power(CORE));
                oled_write_text(3, write_text);
            }
        } else if (usb_recv_buf[0] == 'v' && usb_recv_buf[1] == 'i') {
            float io_voltage = get_float(usb_recv_buf, usb_recv_buf[2] == 'p' ?  3 : 2, usb_recv_buf_idx);
            set_voltage(IO, io_voltage, usb_recv_buf[2] == 'p');
            oled_clear_screen();
            if (usb_recv_buf[2] == 'p') {
                sprintf(write_text, "      PROGRAM       ");
                printf("IO voltage programmed -> %.2f\n", io_voltage);
            } else {
                sprintf(write_text, "        SET         ");
                printf("IO voltage set -> %.2fV\n", io_voltage);
            }
            if (last_button_num == USB_SCREEN) {
                oled_write_text(1, write_text);
                sprintf(write_text, "   IO V -> %.2fV", io_voltage);
                oled_write_text(2, write_text);
                sprintf(write_text, "%.2fV, %.2fA, %.2fW", read_voltage(IO), read_current(IO), read_power(IO));
                oled_write_text(3, write_text);
            }
        } else if (usb_recv_buf[0] == 'c' && usb_recv_buf[1] == '0') {
            clk0_freq = get_int(usb_recv_buf, 2, usb_recv_buf_idx);
            set_clock(CLK0, clk0_freq);
            oled_clear_screen();
            if (last_button_num == USB_SCREEN) {
                sprintf(write_text, "        SET         ");
                oled_write_text(1, write_text);
                sprintf(write_text, "   CLK0 -> %.2fMHz", clk0_freq/1000.0);
                oled_write_text(2, write_text);
            }
            printf("CLK0 set -> %dkHz\n", clk0_freq);
        } else if (usb_recv_buf[0] == 'c' && usb_recv_buf[1] == '1') {
            clk1_freq = get_int(usb_recv_buf, 2, usb_recv_buf_idx);
            set_clock(CLK1, clk1_freq);
            oled_clear_screen();
            if (last_button_num == USB_SCREEN) {
                sprintf(write_text, "        SET         ");
                oled_write_text(1, write_text);
                sprintf(write_text, "   CLK1 -> %.2fMHz", clk1_freq/1000.0);
                oled_write_text(2, write_text);
            }
            printf("CLK1 set -> %dKHz\n", clk1_freq);
        }
        else if (usb_recv_buf[0] == 'h') {
            printf("Help:\n");
            printf("r<data> - Read data\n");
            printf("w<data> - Write data\n");
            printf("ss<speed> - Set SPI speed\n");
            printf("sb<bits> - Set SPI bits\n");
            printf("h - Help\n");
        } else {
            printf("Invalid command\n");
        }

        // Reset buffer index
        usb_recv_buf_idx = 0;
    }
}

int main() {

    // Allow voltages to stabilize
    sleep_ms(100);

    // Initialize standard I/O
    stdio_init_all();

    // Initialize bitwise SPI modules (comment out if not using that channel)
    bitwise_spi0_init();
    bitwise_spi1_init();

    // Initialize I2C module
    i2c_init(I2C_CHAN, I2C_BAUD_RATE);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);

    // Initialize OLED screen (blast initialization pls turn on properly)
    for (int i = 0; i < 10; i++) init_oled();
    oled_clear_screen();

    // Initialize INA220 voltage/current sensors
    init_ina220s();

    // Initialize SI5351 clock generator
    init_si5351();

    // Launch USB handling core
    multicore_launch_core1(core1_entry);

    // Set BRGTC6 reset pins
    gpio_init(BRGTC6_RESET_PIN_0);
    gpio_set_dir(BRGTC6_RESET_PIN_0, GPIO_OUT);
    gpio_put(BRGTC6_RESET_PIN_0, 1);

    gpio_init(BRGTC6_RESET_PIN_1);
    gpio_set_dir(BRGTC6_RESET_PIN_1, GPIO_OUT);
    gpio_put(BRGTC6_RESET_PIN_1, 1);

    last_button_num = 1;
    int curr_button_num = 0;
    while (true) {
        curr_button_num = get_button_num();
        if (curr_button_num != last_button_num && curr_button_num != 0) {
            oled_clear_screen();
            last_button_num = curr_button_num;
        }
        if (last_button_num == 1) {
            sprintf(write_text, "        BRG         ");
            oled_write_text(0, write_text);
            sprintf(write_text, "  Chip Tester v1.0  ");
            oled_write_text(1, write_text);
            sprintf(write_text, "   Parker Schless   ");
            oled_write_text(2, write_text);
            sprintf(write_text, "        2025        ");
            oled_write_text(3, write_text);
        } else if (last_button_num == 2) {
            sprintf(write_text, "IO:%.2fV,%.2fA,%.2fW", read_voltage(IO), read_current(IO), read_power(IO));
            oled_write_text(0, write_text);
            sprintf(write_text, "CR:%.2fV,%.2fA,%.2fW", read_voltage(CORE), read_current(CORE), read_power(CORE));
            oled_write_text(1, write_text);
            sprintf(write_text, " CLK0: %.2fMHz", clk0_freq/1000.0);
            oled_write_text(2, write_text);
            sprintf(write_text, " CLK1: %.2fMHz", clk1_freq/1000.0);
            oled_write_text(3, write_text);
        }
        sleep_ms(100);
    }

    return 0;
}