#include <stdio.h>
#include <stdbool.h>

#define MAX_TEXT_LENGTH 1000
#define MAX_WORD_LENGTH 50
#define VOWELS "aeiouAEIOU"
#define ALPHABET_SIZE 26
#define TAB_WIDTH 4
#define ASCII 32

bool is_vowel(char c);

int main() {
    int word_count = 0, vowel_count = 0, consonant_count = 0, line_count = 0, char_count = 0, longest_word = 0, i = 0, c = 0, k = 0;
    bool in_word = false;
    int chars[128];
    char text[MAX_TEXT_LENGTH];
    char word[MAX_WORD_LENGTH];
    for (int i = 0; i < 128; i++) {
        chars[i] = 0;
    }
    for (int i = 0; i < MAX_TEXT_LENGTH; i++) {
        text[i] = 0;
    }
    for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        word[i] = 0;
    }
    i = 0;
    printf("Enter text (Ctrl+D or Ctrl+Z to end input):\n");

    while ((c = getchar()) != EOF) {
        text[k] = c;
        k++;
        char_count++;
        chars[c]++;
        if (c == '\n') {
            line_count++;
            if (in_word) {
                word_count++;
                in_word = false;
                if (i > longest_word) {
                    longest_word = i;
                }
                i = 0;
            }
        }
        else if (c == ' ' || c == '\t') {
            if (in_word) {
                word_count++;
                in_word = false;
                if (i > longest_word) {
                    longest_word = i;
                }
                i = 0;
            }
        }
        else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            word[i] = c;
            in_word = true;
            i++;
            if (is_vowel(c)) {
                vowel_count++;
            }
            else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                consonant_count++;
            }
        }
        else {
            if (in_word) {
                word_count++;
                in_word = false;
                if (i > longest_word) {
                    longest_word = i;
                }
                i = 0;
            }
        }
    }
    printf("\nText Analysis:\n");
    printf("Total characters: %d\n", char_count);
    printf("Total words: %d\n", word_count);
    printf("Total lines: %d\n", line_count);
    printf("Vowels: %d\n", vowel_count);
    printf("Consonants: %d\n", consonant_count);
    printf("Longest word length: %d\n", longest_word);
    printf("Longest word : %s\n", word);
    printf("Letter frequencies:\n");

    for (int i = 0; i < 128; i++) {
        if (chars[i] > 0 && ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))) {
            printf("%c: %d, ", i, chars[i]);
        }
    }
    putchar('\n');
    putchar('\n');
    printf("Original text:\n");
    printf(text);
    putchar('\n');
    printf("Modified text:\n");

    for (int i = 0; i < MAX_TEXT_LENGTH; i++) {
        if (text[i] == '\t') {
            for (int j = 0; j < TAB_WIDTH; j++) {
                putchar(' ');
            }
        }
        else if (is_vowel(text[i])) {
            if (text[i] >= 'a' && text[i] <= 'z') {
                putchar(text[i] - ASCII);
            }
            else {
                putchar(text[i]);
            }
        }
        else if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z')) {
            if (text[i] >= 'A' && text[i] <= 'Z') {
                putchar(text[i] + ASCII);
            }
            else {
                putchar(text[i]);
            }
        }
        else if (text[i] >= '0' && text[i] <= '9') {
                putchar('*');
        }
        else {
            putchar(text[i]);
        }
    }
    return 0;
}


bool is_vowel(char c) {
    for (int i = 0; VOWELS[i] != '\0'; i++) {
        if (c == VOWELS[i]) {
            return true;
        }
    }
    return false;
}