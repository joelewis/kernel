#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
int main(void) {

	int* s;
	s[1] = 0x70;
	uint8_t a = 33;
	printf("\n address of s is %p", s);
	printf("\n address of s+1 is %p\n", s+1);
	printf("\n value at %p is %d", s+1, s[1]);
	printf("\n value of a is %c", a);
	return 0;
}
