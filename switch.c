#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
    srand(time(NULL));
    int r = rand();
    
    switch (r % 4) {
        case 0:
            puts("0");
            break;
        case 1:
            puts("1");
            break;
        case 2:
            puts("2");
            break;
        case 3:
            puts("3");
            break;
    }
    return 0;
}