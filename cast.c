#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

union FloatInt {
    float f;
    unsigned int i;
};

int main() {
    union FloatInt data;
    data.f = 3.0f;
    printf("Hex: %x\n", data.i);
    printf("Hex: %f\n", data.f);
    printf("Hex: %d\n", data.i);
    return 0;
}
