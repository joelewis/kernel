#include<stdio.h>

int main(void) {
	
	int i = 0;
	char *char_pointer="Joe Lewis";
	/* int *int_pointer=0xffffffff; */
	printf("\n address of i is %p", &i);
	// printf("\n value at %p is %d", int_pointer, *int_pointer);
	printf("\n value at %p is: %c ", char_pointer, *char_pointer);
	printf("\n string is %c", *char_pointer);
	
	return 0;
}
