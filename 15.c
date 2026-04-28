#include <stdio.h>

#define MAX_LENGTH 100


void copy(char str1[], char str2[]){
    int i = 0;
    while ((str2[i] = str1[i]) != '\0')
        i ++;
}


void reverse (char in[], char out[], int len){
    for (int i = 0; i < len; i++) {
        out[i] = in[len - i - 1];
    }
    out[len] = '\0';
}


int getline(char str[], int limit) {
    int c, i = 0;

    for (i = 0; ((c = getchar()) != EOF) && (i < (limit - 1)) && (c != '\n'); i++){
        str[i] = c;
    }

    str[i] = '\0';
    return i;
}


int power(int x, int y) {
    int r = x;
    for (int i = 1; i < y; i++)
        r = r * x;
    return r;
}


int main() {
    int len = 0, c, max = 0;
    char str1[MAX_LENGTH] = "hello", str2[MAX_LENGTH], str3[MAX_LENGTH];


    while ((len = getline(str1, MAX_LENGTH)) > 0) {
        if (len > max) {
            max = len;
            copy(str1, str2);
        }
        if (len > 5)
            printf("%s\n", str1);
        reverse(str1, str3, len);
        printf("%s\n", str3);
    }

    printf("%s\n", str2);
}