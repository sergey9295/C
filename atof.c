#include <ctype.h>
#include <stdio.h>


double powe(float base, int exp) {
    double result = 1;
    if (exp > 0) {
        while (exp-- > 0)
            result *= base;
    }
    else {
        while (exp++ < 0)
            result /= base;
    }
    return result;
}

int getline1(char s[], int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}


int atoi (char s[]);

double atof(char s[])
{
    double val, power = 1.0;
    int i, sign;
    int tenth = 0;

    for (i = 0; isspace(s[i]); i++) 
    ;
    sign = (s[i] == '-') ? -1: 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++) 
        val = 10.0 * val + (s[i] - '0');

    if ((s[i] == 'e') || (s[i] == 'E')) {
        i++;
        tenth = atoi(&s[i]);
        goto ret;
    }

    if (s[i] == '.')
        i++;
    
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] -'0');
        power *= 10.0;
    }
    if ((s[i] == 'e') || (s[i] == 'E')) {
        i++;
        tenth = atoi(&s[i]);
    }

    ret:
    return sign * val / power * powe(10., tenth);
}


int atoi(char s[])
{
    return (int) atof(s);
}

int main () {
    double sum = 0;
    char s[100];
    while (getline1(s, 100)) 
        printf("%f\n", sum += atof(s));
    return 0;
}