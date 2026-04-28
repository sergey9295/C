#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv) {
    printf("%d\n", argc);
    double stack[100];
    for (int k = 0; k < 100; k++) stack[k] = 0;
    int sp = -1;
    char* s;
    while (--argc > 0) {
        s = *++argv;
        if (isdigit(*s) || ((*s == '-') && (s[1] != '\0'))) {
            stack[++sp] = atof(s);
        }
        else {
            switch (*s) {
                case '+':
                    stack[sp - 1] = stack[sp - 1] + stack[sp];
                    break;
                case '*':
                    stack[sp - 1] = stack[sp - 1] * stack[sp];
                    break;
                case '-':
                    stack[sp - 1] = stack[sp - 1] - stack[sp];
                    break;
                case '/':
                    stack[sp - 1] = stack[sp - 1] / stack[sp];
                    break;
            }
            stack[sp--] = 0;
        }
    }

    printf("%f\n", stack[0]);
    return 0;
}