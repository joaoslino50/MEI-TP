#include <string.h>

int are_anagrams(const char *str1, const char *str2) {
    int count[256] = {0};

    while (*str1) {
        count[(unsigned char)*str1]++;
        str1++;
    }

    while (*str2) {
        count[(unsigned char)*str2]--;
        str2++;
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] != 0)
            return 0;
    }

    return 1;
}