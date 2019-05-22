#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <io.h>
#include <print.h>

typedef struct Color {
	unsigned short foregroundColor;
	unsigned short backgroundColor;
} Color;

typedef struct Position {
	unsigned short x;
	unsigned short y;
} Position;

typedef struct Screen {
	static const unsigned short COLUMNS = 80;
	static const unsigned short ROWS = 25;
	Color current_color;
	Position cursor_position;
} Screen;

Screen screen;


void print_mem(size_t x, size_t y, uint16_t* buffer, size_t length, size_t offset = 0)
{
	char* string = 0;
	unsigned int c = 0;

	for (int i = 0; i < length; i++) {
		string[c] = buffer[i + offset];
		c++;
	}

	string[c] = 0;

	print(x, y, string);

}

extern "C"
{
	void kernel_main(void)
	{
		set_color(14,0);

		print_mem(0,0, (uint16_t*) 0x00000, 4000);

		print(70,21, "Key status");

		set_color(2,0);
		while (1) {
			unsigned char key = inb(0x60);

			print_binary(72, 22, key);
			print_decimal(73, 23, key, true);
			print_hex(76, 24, key, true);

		}
	}
}