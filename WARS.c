#include <stdio.h>

#define MAX_LENTH 50

char old[MAX_LENTH];
char newer[MAX_LENTH];

void seq(char old[], char newer[]) {
    int index1 = 1, index2 = 0, counter = 1;
    int c, char_prev = old[0];
    while ((c = old[index1]) != 0) {
        if (char_prev == c) {
            counter++;
            index1++;
        }
        else {
            newer[index2++] = counter;
            newer[index2++] = char_prev;
            counter = 0;
            char_prev = c;
        }
    }
    newer[index2++] = counter;
    newer[index2++] = old[--index1];
}

int main() {
    old[0] = 1;
    int l = 0;
    while (l < 10) {
        printf("%d: ", l);
        seq(old, newer);
        for (int i = 0; i < MAX_LENTH; i++) {
            old[i] = newer[i];
        }
        for (int i = 0; i < MAX_LENTH; i++) {
            printf("%d", old[i]);
        }
        putchar('\n');
        l++;
    }
    return 0;
}