#include <stdio.h>

#define TAB 8
#define MAX_STR 12

int main() { 
    int c, i, column = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            column = 0;
            putchar(c);
        }
        else if (c == '\t') {
            column += (column % TAB);
            if (column >= MAX_STR) {
                putchar('\n');
            } 
            else {
                putchar(c);
            }
        }
        else if (c == ' ') {
            column ++;
            if (column >= MAX_STR) {
                putchar('\n');
                column = 0;
            } 
            else {
                putchar(c);
            }
        }
        else {
            column ++;
            putchar(c);
        }
    }
}