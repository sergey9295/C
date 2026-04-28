#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    char number[100];
    double stack[100];
    for (int k = 0; k < 100; k++) number[k] = '\0';
    for (int k = 0; k < 100; k++) stack[k] = 0;
    int c, i = 0, sp = -1;
    while ((c = getchar()) != '\n') {

        if (isdigit(c) || (c == '.') || (c == '-')) {
            number[i++] = c;
        }
        else if ((c == '+') || (c == '*') || (c == '/')) {
            switch (c) {
                case '+':
                    stack[sp - 1] = stack[sp - 1] + stack[sp];
                    break;
                case '*':
                    stack[sp - 1] = stack[sp - 1] * stack[sp];
                    break;
                case '/':
                    stack[sp - 1] = stack[sp - 1] / stack[sp];
                    break;
            }
            stack[sp--] = 0;
        }
        else {
            if ((number[0] == '-') && (number[1] == '\0')) {
                stack[sp - 1] = stack[sp - 1] - stack[sp];
                stack[sp--] = 0;
                number[0] = '\0';
            }
            else if (number[0] != '\0') {
                sscanf(number, "%lf", &stack[++sp]);
                //stack[++sp] = atof(number);
                for (int k = 0; k < 100; k++) number[k] = 0;
            }
            i = 0;
        }
    }

    printf("%f\n", stack[0]);
    return 0;
}