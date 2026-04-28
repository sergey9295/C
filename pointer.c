#include <stdio.h>


void strcat(char* s1, char* s2) {
    int i, j = 0;
    for (i = 0; *(s1 + i) != '\0'; i++);
    for (j = 0; *(s2 + j) != '\0'; *(s1 + i + j) = *(s2 + j), j++);
    *(s1 + i + j) = '\0';
}


void strcat2(char* s1, char* s2) {
    while (*++s1 != '\0');
    while ((*s1++ = *s2++) != '\0');
}

void strncat(char* s1, char* s2, int n) {
    int i = 0;
    while (*++s1 != '\0');
    while (((*s1++ = *s2++) != '\0') && (++i < n));
}


int strend(char* s, char* t) {
    char* te = t;
    int flag;
    while (*++s != '\0');
    while (*t++ != '\0') s--;
    while((flag = (*s++ == *te++)) && (*s != '\0'));
    return flag;
}


void strncpy(char* s1, char* s2, int n) {
    int i = 0;
    while (((*s2++ = *s1++) != '\0') && (++i < n));
    *s2 = '\0';
}


int strncmp(char* s1, char* s2, int n) {
    int i = 0, d = *s2 - *s1;
    while ((*s2++ == *s1++) && *s1 != '\0' && *s2 != '\0' && (++i < n)) d = *s2 - *s1;
    return d;
}


int main() {
    char s1[100] = "Hello ";
    char* s2 = "World!";
    strncat(s1, s2, 3);
    printf("%s\n", s1);
    strncpy(s2, s1, 3);
    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%d\n", strncmp(s1, s2, 50));
}