#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool isPalindrome(const char *str) {
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        // Move left index if not a letter/digit? (optional)
        // For now, we compare all characters, only ignoring case

        char c1 = tolower((unsigned char)str[left]);
        char c2 = tolower((unsigned char)str[right]);

        if (c1 != c2) {
            return false;
        }

        left++;
        right--;
    }

    return true;
}

#include <stdio.h>

int main() {
    printf("%d\n", isPalindrome("Racecar"));  // 1 (true)
    printf("%d\n", isPalindrome("hello"));    // 0 (false)
    return 0;
}
