#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXFILES	500
#define MAXLINE		10000
#define BARLEN		80

static FILE *fp[MAXFILES];
static char *fn[MAXFILES];
static int nfs = 0;

int main(int argc, char *argv[]) {
    FILE *f;
    char line[MAXLINE];
    int page = 1;
    int length;
    int left, right;
    int i;

    while (--argc != 0) {
        f = fopen(argv[page], "r");
        length = strlen(argv[page]);
        left = (BARLEN - length) / 2;
        right = BARLEN / 2 + length / 2;
        if (length % 2 == 1) right--;
        i = 0;
        while (i++ < left) {
            putchar('=');
        }
        printf("%s", argv[page]);
        while (i++ < BARLEN - length) {
            putchar('=');
        }
        putchar('\n');
        while (fgets(line, MAXLINE, f)) {
            fputs(line, stdout);
        }
        fclose(f);
        putchar('\n');
        page++;
    }
    return 0;
}