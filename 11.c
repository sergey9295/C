#include <stdio.h>

#define IN 1
#define OUT 0 

int main() {
    int ASCII[128];
    int length[30];
    int c;
    int len = 0;
    int i = OUT;

    for (int i = 0; i < 128; i++) {
        ASCII[i] = 0;
    }

    for (int i = 0; i < 30; i++) {
        length[i] = 0;
    }
    
    while ((c = getchar()) != EOF) {
        ASCII[c]++;
        if (c == ' ' || c == '\t' || c == '\n') {
            if (i == IN) {
                i = OUT;
                length[len]++;
                len = 0;
            }
        }
        else {
            i = IN;
            len++;
        }
    }

    for (int i = 0; i < 128; i++) {
        printf("%c %3d %3d\n", i, i, ASCII[i]);
    }

    for (int i = 97; i < 123; i++) {
        printf("%c   ", i);
        for (int j = 0; j < ASCII[i]; j++) {
            putchar('-');
        }
        putchar('\n');
    }

    for (int i = 0; i < 30; i++) {
        printf("%2d   ", i);
        for (int j = 0; j < length[i]; j++) {
            putchar('-');
        }
        putchar('\n');
    }
}