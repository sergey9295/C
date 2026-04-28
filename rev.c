#include <stdio.h>
#include <string.h>

int atoi (char s[]) {
    int n = 0, i = 0;
    while (s[i] != '\0') {
        n = n * 10 + (s[i] - '0');
        i++;
    }
    return n;
}

unsigned getbits(unsigned x, int p, int n) {
    return (x >> (p+1-n)) & ~(~0 << n);
}

int itob (unsigned int n) {
    int i = 0;
    int b = 0;
    while (n != 0) {
        b <<= 1;
        b += (n % 2);
        n >>= 1;
    }
    return b;
}

int main() {
    char s[] = "123";
    int len = strlen(s);
    int temp, lim = 10, c;
    int a = 0, b = len - 1;
    int n = 60;
    for (; a < b; a++, b--) {
        temp = s[a];
        s[a] = s[b];
        s[b] = temp;
    }
    for (int i = 0; i < len; i ++) {
        putchar(s[i]);
    }
    putchar('\n');
    printf("%d\n", atoi(s));
    printf("%x\n", itob(n));
    printf("%x\n", getbits(n, 4, 3));
}