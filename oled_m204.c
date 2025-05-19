#include "oled_m204.h"

void init_oled() {
	int i2c_resp_code;

	// Byte sequence specified in EA OLEDM204-GGA datasheet for initialization
	const uint8_t rom[] = {0x40, 0x00};
	const uint8_t init_seq[] = {
		0x3A, // FunctionSet: N=1 BE=0 RE=1 IS=0
		0x09, // 4-line mode
		0x06, // View 180 degrees (modified from provided initialization)
		0x38, // FunctionSet: N=1 BE=0 RE=0 IS=0
		0x3A, // FunctionSet: N=1 BE=0 RE=1 IS=0
		0x72, // ROM Selection 
		0x38, // FunctionSet: N=1 BE=0 RE=0 IS=0
		0x0C, // Display ON (no blink or cursor)
		0x01  // Clear Display
	};

	for (int i = 0; i < sizeof(init_seq); i++) {
		uint8_t command[] = {0x80, init_seq[i]};
		i2c_write_blocking_err_check(I2C_CHAN, OLED_ADDR, command, 2, i != sizeof(init_seq) - 1);
		sleep_ms(1);
		if (init_seq[i] == 0x72) i2c_write_blocking_err_check(I2C_CHAN, OLED_ADDR, rom, 2, true);
	}
}

void oled_clear_screen() {
	const uint8_t screen_clear[] = {0x80, 0x01};
	i2c_write_blocking(I2C_CHAN, OLED_ADDR, screen_clear, 2, false);
}

void oled_row_sel(int row) {
	uint8_t row_hex;
	if (row == 0) row_hex = 0x80;
	else if (row == 1) row_hex = 0xA0;
	else if (row == 2) row_hex = 0xC0;
	else if (row == 3) row_hex = 0xE0;
	else return;
	const uint8_t next_row[] = {0x80, row_hex};
	i2c_write_blocking_err_check(I2C_CHAN, OLED_ADDR, next_row, 2, false);
}

void oled_write_text(int row, const char* text) {
	oled_row_sel(row);
	for (int i = 0; i < strlen(text); i++) {
		const uint8_t send_data[] = {0x40, (uint8_t)(text[i])};
		i2c_write_blocking_err_check(I2C_CHAN, OLED_ADDR, send_data, 2, i != strlen(text) - 1);
	}
}

void oled_write_blank(int row) {
	oled_row_sel(row);
	char* text = "                    ";
	for (int i = 0; i < strlen(text); i++) {
		const uint8_t send_data[] = {0x40, 0x20};
		i2c_write_blocking_err_check(I2C_CHAN, OLED_ADDR, send_data, 2, i != strlen(text) - 1);
	}
}