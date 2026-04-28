#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *data;
    size_t length;
} stringView;


stringView sv(char *cs) {
    return (stringView) {cs, strlen(cs)};
}


void chopRight(stringView *s, int n) {
    if (s->length < n) s->length = n;
    s->length -= n;
}

void chopLeft(stringView *s, int n) {
    if (s->length < n) s->length = n;
    s->data += n;
    s->length -= n;
}

stringView chopDeli(stringView *s, char c) {
    int i = 0;
    while (i < s->length && s->data[i] != c) {
        i++;
    }    
    if (i < s->length) {
        stringView result = {
            .data = s->data,
            .length = i
        };
        chopLeft(s, i + 1);
        return result;
    }
    else {
        stringView result = *s;
        chopLeft(s, s->length);
        return result;
    }
}


void trimLeft(stringView *s) {
    while (s->length > 0 && isspace(s->data[0])) {
        chopLeft(s, 1);
    }
}

void trimRight(stringView *s) {
    while (s->length > 0 && isspace(s->data[s->length - 1])) {
        chopRight(s, 1);
    }
}


void trim(stringView *s) {
    trimLeft(s);
    trimRight(s);
}


int main(){
    FILE *f = fopen(__FILE__, "rb");
    size_t capacity = 1048576;
    char *buffer = malloc(capacity);
    size_t size = fread(buffer, 1, capacity, f);

    stringView s = sv(buffer);

    while (s.length > 0){
        stringView temp = chopDeli(&s, '\n');
        trim(&temp);
        printf("%.*s\n", temp.length, temp.data);
    }
    printf("%.*s\n", s.length, s.data);
}