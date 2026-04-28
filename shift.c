#include <stdio.h>
#include <math.h>

unsigned char shift(unsigned char x, int p, int n, unsigned char y) {
	printf("%x\n", (unsigned char) y << (8 - n - p));
	printf("%x\n", ~0 << (8 - n - p));		
	printf("%x\n", ~0 << (8 - n - p)) >> (8 - n - p);	
	printf("%x\n", y << (8 - n - p));
	return (x & (~(((~0) << (8 - p - n)) >> (8 - p - n)))) | ((~0 <<(8 - n - p))	& (y << (8 - n - p)));
}

int main() {
	unsigned char x = shift(19, 2, 3, 111);
	printf("%x\n", x);
	return 0;
}

