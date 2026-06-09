#include <ctype.h>

int count_vowels(const char *str) {
    int count = 0;

    while (*str) {
        char c = tolower((unsigned char)*str);

        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }

        str++;
    }

    return count;
}