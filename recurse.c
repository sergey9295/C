#include <stdio.h>
#include <string.h>

char s[100];
int i = 0;

void itoa(int n)
{
    if (n < 0) {
        s[i++] = '-';
        n=-n;
    }
    if (n / 10)
        itoa(n / 10);
    s[i++] = n % 10 + '0';
}

void reverse(char s[], int length) {
    if (length < 2)
        return;
    s[0] ^= s[length];
    s[length] ^= s[0];
    s[0] ^= s[length];
    reverse(&s[i], length - 2);
}

int main(){
    itoa(121);
    printf("%s\n", s);
    reverse(s, strlen(s) - 1);
    printf("%s\n", s);
}