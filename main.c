#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "histogram.h"

float gen() {
    return rand() / (float) RAND_MAX;
}

float expo() {
    float uni = rand() / (float) RAND_MAX;
    return -log(1 - uni) / 8;
}


int main() {
    struct Histogram1D a;

    hist1d_init(&a, 40, -15, 20);

    hist1d_reset(&a);

    hist1d_generate_and_fill(&a, 5000, expo);

    hist1d_print(&a);

    hist1d_free(&a);

    return 0;
}

