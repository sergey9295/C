#include <stdio.h>

#define TAB_SIZE 8

void shift(char s[], int c, int column) {
    int k = 0;

    while ((s[TAB_SIZE - 1 - k] == ' ') && (k < TAB_SIZE - column))
    {
        k++;
    }

    if (k == TAB_SIZE - column) {
        putchar('\t');
        while (k != 0) {
            s[7 - k] = NULL;
            k--;
        }
    }
    else {
        putchar(s[7]);
    }

    for (int i = 7; i > 0; i--) {
        s[i] = s[i - 1];        
    }
    s[0] = c;
}

int main () {
    char buffer[TAB_SIZE];
    for (int i = 0; i < TAB_SIZE; i++){
        buffer[i] = 0;
    }
    int column = 0, c;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            shift(buffer, c, column);
            column = 0;
        }
        else if (c == '\t') {
            shift(buffer, c, column);
            column = 0;
        }
        else {
            shift(buffer, c, column);
            column++;
            if (column > 7) {
            column = 0;
            }
        }
    }
    for (int i = 1; i <= TAB_SIZE; i++)
        putchar(buffer[TAB_SIZE - i]);
}