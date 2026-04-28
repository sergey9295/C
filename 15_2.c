#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void copy(char str1[], char str2[]) {
    int i = 0;
    while ((str2[i] = str1[i]) != '\0')
        i++;
}

// Fixed: Loop runs the full length 'len'
void reverse(char in[], char out[], int len) {
    int i;
    for (i = 0; i < len; i++) {
        out[i] = in[len - i - 1];
    }
    out[len] = '\0'; // Null terminator at the very end
}

int main() {
    char str1[MAX_LENGTH] = "hello";
    char str3[MAX_LENGTH];

    // No need to copy if reverse covers all indices
    reverse(str1, str3, strlen(str1));

    printf("Original: %s\n", str1);
    printf("Reversed: %s\n", str3);

    return 0;
}
