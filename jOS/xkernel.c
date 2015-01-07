#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>


#if defined(__linux__)
#error "You are not using a cross compiler. Good luck with your attempt!"
#endif

#if !defined(__i386)
#error "This program needs to be compiled with a ix86-elf compiler"
#endif

enum vga_color {
  COLOR_BLACK = 0,
  COLOR_BLUE = 1,
  COLOR_GREEN = 2,
  COLOR_CYAN = 3,
  COLOR_RED = 4,
  COLOR_MAGENTA = 5,
  COLOR_BROWN = 6,
  COLOR_LIGHT_GREY = 7,
  COLOR_DARK_GREY = 8,
  COLOR_LIGHT_BLUE = 9,
  COLOR_LIGHT_GREEN = 10,
  COLOR_LIGHT_CYAN = 11,
  COLOR_LIGHT_RED = 12,
  COLOR_LIGHT_MAGENTA = 13,
  COLOR_LIGHT_BROWN = 14,
  COLOR_WHITE = 15,
};

uint8_t make_color(enum vga_color fg, enum vga_color bg) {

  // x x x x       x x x x
  // | | | |       | | | |
  // background    foreground

  return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color) {
  // cast char into 16 bit int
  // cast color into 16 bit int
  // return 16 bits ==> put color as first 8 bits and char as leading 8 bits
  uint16_t color16 = color;
  uint16_t char16 = c;
  return char16 | color16 << 8;
}

// helper func
size_t strlen(const char* str)
{
  size_t ret = 0;
  while ( str[ret] != 0 )
    ret++;
    return ret;
}

static const size_t VGA_WIDTH = 80; // 80 chars long
static const size_t VGA_HEIGHT = 25; // 25 chars tall

size_t terminal_x;
size_t terminal_y;
uint8_t terminal_color;
uint16_t* vga_buffer;

void terminal_init() {
  terminal_x = 0;
  terminal_y = 0;
  terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
  vga_buffer = (uint16_t*) 0xB8200;
  for ( size_t y=0; y<VGA_HEIGHT; y++ ) {
    for ( size_t x=0; x<VGA_WIDTH; x++ ) {
      const size_t index = y * VGA_WIDTH + x;
      vga_buffer[index] = make_vgaentry(' ', terminal_color);
    }
  }
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  size_t index = y * VGA_WIDTH + x;
  vga_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c) {
  terminal_putentryat(c, terminal_color, terminal_x, terminal_y);
  // increment terminal_x && terminal_y to point to new position to put the next entry
  if ( ++terminal_x == VGA_WIDTH ) {
    terminal_x = 0;
    ++terminal_y;
  }

}

void terminal_writestr(char* data) {
  for ( size_t i=0; i<strlen(data); i++ ) {
      terminal_putchar(data[i]);
  }
}


#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main() {
  terminal_init();
  terminal_writestr("Hello, joeOS!");
}
