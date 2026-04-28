#include <stdio.h>
#include <string.h>
#include <math.h>

char s1[120] = "sdfga-f-u1-9";
char s2[5000];
char num[100];

void expand() {
    int i = 0, j = 0;
    
    while ((s1[i] != '\0') && (s1[i + 1] != '\0')) {
        if (s1[i + 1] != '-')
            s2[j++] = s1[i++];
        else {
            for (int k = s1[i]; k != s1[i + 2]; k ++) {
                s2[j++] = k;
            }
            if (s1[i + 3] == '-') {
                i += 2;
            }
            else {
                s2[j++] = s1[i + 2];
                i += 3;
            }
        }
    }
}
void reverse (char num[]) {
    int temp;
    for (int i = 0, j = strlen(num) - 1; i < j; i++, j--) {
        temp = num[j], num[j] = num[i], num[i] = temp;
    }
}

void itoa (int n) {

    int i = 0;

    do {
        num[i++] = '0' + n % 10, n /= 10;
    } while (n != 0);
}

void itob (int n, int b) {

    int i = 0;

    do {
        if (n % b > 10) {
            num[i++] = 'a' - 10 + n % b, n /= b;
        }
        else
            num[i++] = '0' + n % b, n /= b;
    } while (n != 0);
}

int main () {
    unsigned int char1 = 4000000190;
    signed int char2 = -294967106;



    printf("%08x\n", char1);
    printf("%08x\n", char2);

    printf("%08x\n", char1 >> 4);
    printf("%08x\n", char2 >> 4);


    char a[50];    
    int c;
    int k = 0;

    while ((c = getchar()) != EOF) {
        switch (c) {
        case '\n':
            a[k++] = '\\';
            a[k++] = 'n';
            break;
        case '\t':
            a[k++] = '\\';
            a[k++] = 't';
            break;
        case 'f':
            goto end;
        default:
            a[k++] = c;
        }
    }

    end:
    expand();
    itob(1234, 16);
    reverse(num);

    printf("%s\n", a);
    printf("%s\n", s2);
    printf("%s\n", num);

    return 0;
}