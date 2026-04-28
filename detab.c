#include <stdio.h>

#define TAB_SIZE 8

int main () {
    int column = 0, c;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            putchar(c);
            column = 0;
        }
        else if (c == '\t') {
            for (int i = 0; i < TAB_SIZE - column; i++)
                putchar(' ');
            column = 0;
        }
        else {
            putchar(c);
            column++;
        }
    }
}