#include <stdio.h>
#include <string.h>

#define MAX 100

int main() {
    FILE *f1 = fopen(__FILE_NAME__, "r");
    FILE *f2 = fopen("calc.c", "r");
    char ln1[100];
    char ln2[100];
    while (1) {
        fgets(ln1, MAX, f1);
        fgets(ln2, MAX, f2);
        if (strcmp(ln1, ln2) == 0) continue;
        else {
            fputs(ln1, stdout);
            fputs(ln2, stdout);
            break;
        }
    }
    return 0;
}