#include <stdio.h>
#include <ctype.h>
#include <string.h>

int countVowels(const char *str) {
    if (str == NULL) return 0;
    
    int count = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        char c = tolower(str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    
    return count;
}

int countVowelsWithSwitch(const char *str) {
    if (str == NULL) return 0;
    
    int count = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        char c = tolower(str[i]);
        switch(c) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                count++;
                break;
            default:
                break;
        }
    }
    
    return count;
}

int countVowelsWithStrChr(const char *str) {
    if (str == NULL) return 0;
    
    int count = 0;
    const char *vowels = "aeiouAEIOU";
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (strchr(vowels, str[i]) != NULL) {
            count++;
        }
    }
    
    return count;
}

void countVowelsDetailed(const char *str, int counts[5]) {
    for (int i = 0; i < 5; i++) {
        counts[i] = 0;
    }
    
    if (str == NULL) return;
    
    for (int i = 0; str[i] != '\0'; i++) {
        char c = tolower(str[i]);
        switch(c) {
            case 'a': counts[0]++; break;
            case 'e': counts[1]++; break;
            case 'i': counts[2]++; break;
            case 'o': counts[3]++; break;
            case 'u': counts[4]++; break;
        }
    }
}