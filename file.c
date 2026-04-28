#include <stdio.h>

int main () {
    putc(FILE *f, char c);
    getc(FILE *f);
    putchar(char c);
    getchar();

    ungetc(int c, FILE *fp)


    fgets(char *s, int length, FILE *f);
    gets(char *s, int length); //deprecated
    fputs(char *s, FILE *f);
    puts(char *s);

    printf("");
    scanf("", &x);
    sprintf(char *s, "");
    sscanf(char *s, "", &x);
    fprintf(FILE *f, "");
    fscanf(FILE *f, &x);

    fread(void *ptr, size_t size, size_t count, FILE *stream);
    fwrite(void *ptr, size_t size, size_t count, FILE *f);

    FILE *fp = fopen("test.txt", "r");
    char c;
    int i;
    char s[10];
    fgets(s, 10, stdin);
    puts(s);
    fscanf(fp, "%d\n",&i);
    printf("%d\n", i);
    while ((c = getc(fp)) != EOF) {
        putchar(c);
    }
}