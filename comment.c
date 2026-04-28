#include <stdio.h>
#include <stdbool.h>

int main() { 
    int c, i, column = 0;
    bool comment1 = false;
    bool comment2 = false;
    bool first1 = false;
    bool first2 = false;

    while ((c = getchar()) != EOF) {
        if ((c == '/') && !first2 && !first1)
            first1 = true;
        else if ((c == '*') && !first2 && !first1)
            first2 = true;
        else if ((c == '/') && first1) {
            comment1 = true;
            first1 = false;
        }
        else if ((c == '*') && first1) {
            comment2 = true;
            first1 = false;
        }
        else if ((c == '/') && first2) {
            comment2 = false;
            first2 = false;
        }
        else if ((c == '\n') && !comment2) {
            putchar(c);
            first1 = false;
            first2 = false;
            comment1 = false;
        }
        else if (!comment1 && !comment2) {
            putchar(c);
            first1 = false;
            first2 = false;
        }
        else {
            first1 = false;
            first2 = false;
        }
    }
}