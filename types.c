#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <float.h>

#define TAB 0x13

enum months {JAN = 11, FEB, MAR};

int main () {
    char stri[] = "HEllow shit";
    char char1 = 0b10101;
    printf("%d\n", strlen(stri));
    printf("%d\n", FEB);
    const short short1 = 13000L;
    const int int1 = 13000L;
    long long1;
    long long long2;
    float float1;
    double double1;
    long double double2;
    size_t size1;

    printf("%d\n", sizeof(char1));
    printf("%d\n", sizeof(short1));
    printf("%d\n", sizeof(int1));
    printf("%d\n", sizeof(long1));
    printf("%d\n", sizeof(long2));
    printf("%d\n", sizeof(float1));
    printf("%d\n", sizeof(double1));
    printf("%d\n", sizeof(double2));
    printf("%d\n", sizeof(size1));

    short i = 0;
    while (i < 3) {
        printf("%d\n", i++);
    }
}