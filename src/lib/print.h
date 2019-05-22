#ifndef PRINT_H_
#define PRINT_H_

static const size_t SCREEN_WIDTH = 80;

uint8_t screen_color  = 7 | 0 << 4;
uint16_t* screen_buffer = (uint16_t*) 0xB8000;

size_t strlen(const char* str)
{
       size_t len = 0;
       while (str[len])
               len++;
       return len;
}

char calculate_color(char foreground, char background)
{
	return foreground | background << 4;
}

static inline uint16_t calculate_char_color(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t calculate_adr(size_t x, size_t y)
{
	return y * SCREEN_WIDTH + x;
}

void print(size_t x, size_t y, const char* data)
{
	size_t size = strlen(data);
	size_t i = calculate_adr(x, y);

	for (size_t c = 0; c < size; c++) {
		screen_buffer[i + c] = calculate_char_color((data[c]), screen_color);
	}
}

void set_color(char foreground, char background)
{
	screen_color = calculate_color(foreground, background);
}

void print_binary(size_t x, size_t y, unsigned short c)
{
	unsigned short s = 0b10000000;
	unsigned short digit;
	size_t i = 0;
	char* buffer;

	for (digit = 0; digit <=7; ++digit) {
		if ((c & s) == s) {
			buffer[i] = '1';
		} else {
			buffer[i] = '0';
		}
		++i;
		s = s >> 1;
	}

	buffer[i] = 0x00;

	print(x, y, buffer);
}

void print_decimal(size_t x, size_t y, unsigned int result, bool leading_zero = false)
{
	const unsigned digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	unsigned int divider = 1000000;
	unsigned int temp_result = 0;
	bool written = false;
	size_t i = 0;
	char* buffer;

	while (divider != 0) {
		temp_result = result / divider;
		result = result - temp_result * divider;
		divider = divider / 10;

		if (temp_result == 0 && !written && !leading_zero) {
			continue;
		}

		if (temp_result == 0 && !written && leading_zero) {
			buffer[i] = '0';
		} else {
			buffer[i] = digits[temp_result];
			written = true;
		}
		++i;

	}

	buffer[i] = 0x00;

	print(x, y, buffer);
}

void print_hex(size_t x, size_t y, unsigned int result, bool leading_zero = false)
{
	const unsigned digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	unsigned int divider = 4096;
	unsigned int temp_result = 0;
	bool written = false;
	size_t i = 0;
	char* buffer;

	while (divider != 0) {
		temp_result = result / divider;
		result = result - temp_result * divider;
		divider = divider / 16;

		if (temp_result == 0 && !written && !leading_zero) {
			continue;
		}

		if (temp_result == 0 && !written && leading_zero) {
			buffer[i] = '0';
		} else {
			buffer[i] = digits[temp_result];
			written = true;
		}
		++i;

	}

	buffer[i] = 0x00;

	print(x, y, buffer);
}

#endif
