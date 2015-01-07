#include <stddef.h>
#include <stdint.h>


#if defined(__linux__)
#error "You are not using a cross compiler. Good luck with your attempt!"
#endif

#if !defined(__i386)
#error "This program needs to be compiled with a ix86-elf compiler"
#endif


// helper func
size_t strlen(const char* str) {
  size_t ret = 0;
  while ( str[ret] != 0 )
    ret++;
    return ret;
}

static const size_t VGA_WIDTH = 80; // 80 chars long
static const size_t VGA_HEIGHT = 25; // 25 chars tall

unsigned int terminal_x;
unsigned int terminal_y;
char* vga_buffer;

void terminal_init() {
  terminal_x = 0;
  terminal_y = 0;
  unsigned int index = 0;
  // terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
  vga_buffer = (char*) 0xB8000;
  while ( index < VGA_WIDTH * VGA_HEIGHT * 2 ) {
      vga_buffer[index] = ' ';
      vga_buffer[index+1] = 0x17;
      index+=2;
  }
}

void terminal_putchar(char c) {
  unsigned int index = terminal_y * VGA_WIDTH + terminal_x; // get current index
  vga_buffer[index] = c;
  vga_buffer[index+1] = 0x17;
  // increment terminal_x && terminal_y to point to new position to put the next char
  terminal_x+=2;
  if ( terminal_x == VGA_WIDTH*2 ) {
    terminal_x = 0;
    terminal_y+=2;
  }
}

void terminal_writestr(char* data) {
  for ( size_t i=0; i<strlen(data); i++ ) {
    terminal_putchar(data[i]);
  }
}

void kernel_main() {
  terminal_init();
  terminal_writestr("Hello, joe!");
}
