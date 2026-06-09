#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to reverse a string in-place
void reverseString(char *str) {
    // Handle NULL or empty string
    if (str == NULL || *str == '\0') {
        return;
    }
    
    int left = 0;
    int right = strlen(str) - 1;
    
    // Swap characters from both ends
    while (left < right) {
        // Swap characters
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        
        // Move pointers
        left++;
        right--;
    }
}

// Alternative: Reverse using pointer arithmetic
void reverseStringPointer(char *str) {
    if (str == NULL || *str == '\0') {
        return;
    }
    
    char *left = str;
    char *right = str + strlen(str) - 1;
    
    while (left < right) {
        char temp = *left;
        *left = *right;
        *right = temp;
        
        left++;
        right--;
    }
}

// Reverse using XOR swap (no temporary variable)
void reverseStringXOR(char *str) {
    if (str == NULL || *str == '\0') {
        return;
    }
    
    int left = 0;
    int right = strlen(str) - 1;
    
    while (left < right) {
        // XOR swap (works only for integers, but chars are integers)
        if (str[left] != str[right]) {
            str[left] ^= str[right];
            str[right] ^= str[left];
            str[left] ^= str[right];
        }
        left++;
        right--;
    }
}

// Reverse words in a string (keep word order reversed)
void reverseWords(char *str) {
    if (str == NULL || *str == '\0') {
        return;
    }
    
    // First, reverse the entire string
    reverseString(str);
    
    // Then, reverse each word
    int start = 0;
    int i = 0;
    int len = strlen(str);
    
    while (i <= len) {
        if (str[i] == ' ' || str[i] == '\0') {
            // Reverse the word
            int end = i - 1;
            while (start < end) {
                char temp = str[start];
                str[start] = str[end];
                str[end] = temp;
                start++;
                end--;
            }
            start = i + 1;
        }
        i++;
    }
}

// Reverse only a portion of a string
void reverseSubstring(char *str, int start, int end) {
    if (str == NULL || *str == '\0') {
        return;
    }
    
    int len = strlen(str);
    if (start < 0 || end >= len || start >= end) {
        return;
    }
    
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Recursive reverse (requires caution with long strings)
void reverseRecursive(char *str, int left, int right) {
    if (left >= right) {
        return;
    }
    
    // Swap characters
    char temp = str[left];
    str[left] = str[right];
    str[right] = temp;
    
    // Recursive call
    reverseRecursive(str, left + 1, right - 1);
}

// Wrapper for recursive reverse
void reverseStringRecursive(char *str) {
    if (str == NULL || *str == '\0') {
        return;
    }
    reverseRecursive(str, 0, strlen(str) - 1);
}

// Reverse with error checking and memory safety
int safeReverseString(char *str, size_t bufferSize) {
    if (str == NULL) {
        return -1; // NULL pointer
    }
    
    size_t len = strnlen(str, bufferSize);
    if (len == 0) {
        return 0; // Empty string
    }
    
    size_t left = 0;
    size_t right = len - 1;
    
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
    
    return 1; // Success
}

// Helper function to demonstrate string reversal
void demonstrateReversal(const char *original, void (*reverseFunc)(char*), const char *funcName) {
    // Create a copy since we'll modify it
    char buffer[256];
    strcpy(buffer, original);
    
    printf("\nOriginal: \"%s\"\n", buffer);
    reverseFunc(buffer);
    printf("%s: \"%s\"\n", funcName, buffer);
}

// Function to display string with character positions
void displayStringWithPositions(const char *str) {
    printf("\nString: \"%s\"\n", str);
    printf("Index:  ");
    for (int i = 0; i < strlen(str); i++) {
        printf("%3d", i);
    }
    printf("\nChar:   ");
    for (int i = 0; i < strlen(str); i++) {
        printf("%3c", str[i]);
    }
    printf("\n");
}

int main() {
    printf("String Reversal Functions in C\n");
    printf("==============================\n");
    
    // Test case 1: Basic string reversal
    printf("\n1. Basic String Reversal:");
    char str1[] = "Hello, World!";
    demonstrateReversal(str1, reverseString, "Reversed");
    
    // Test case 2: Palindrome (reversing yields same string)
    char str2[] = "racecar";
    demonstrateReversal(str2, reverseString, "Palindrome test");
    
    // Test case 3: Single character
    char str3[] = "A";
    demonstrateReversal(str3, reverseString, "Single char");
    
    // Test case 4: Empty string
    char str4[] = "";
    demonstrateReversal(str4, reverseString, "Empty string");
    
    // Test case 5: String with spaces
    char str5[] = "The quick brown fox";
    demonstrateReversal(str5, reverseString, "With spaces");
    
    // Test different reversal methods on same string
    printf("\n\n2. Comparison of Methods:");
    char testStr[] = "Algorithm";
    char buffer1[100], buffer2[100], buffer3[100];
    
    strcpy(buffer1, testStr);
    reverseString(buffer1);
    printf("\nStandard swap: \"%s\"", buffer1);
    
    strcpy(buffer2, testStr);
    reverseStringPointer(buffer2);
    printf("\nPointer swap:  \"%s\"", buffer2);
    
    strcpy(buffer3, testStr);
    reverseStringXOR(buffer3);
    printf("\nXOR swap:      \"%s\"", buffer3);
    
    strcpy(buffer1, testStr);
    reverseStringRecursive(buffer1);
    printf("\nRecursive:     \"%s\"", buffer1);
    
    // Test reverse words
    printf("\n\n3. Reverse Words in String:");
    char words[] = "Hello World from C";
    printf("\nOriginal: \"%s\"", words);
    reverseWords(words);
    printf("\nAfter reversing words: \"%s\"", words);
    printf("\n(Reverses word order while keeping each word intact)");
    
    // Test substring reversal
    printf("\n\n4. Substring Reversal:");
    char substring[] = "abcdefghij";
    printf("\nOriginal: \"%s\"", substring);
    reverseSubstring(substring, 2, 7);
    printf("\nReverse indices 2-7: \"%s\"", substring);
    
    // Test with various edge cases
    printf("\n\n5. Edge Cases:");
    
    // Numbers and special characters
    char str6[] = "123!@#ABC";
    demonstrateReversal(str6, reverseString, "Special chars");
    
    // Mixed case
    char str7[] = "AbCdEfG";
    demonstrateReversal(str7, reverseString, "Mixed case");
    
    // Long string
    char str8[] = "The quick brown fox jumps over the lazy dog";
    demonstrateReversal(str8, reverseString, "Long string");
    
    // Visual demonstration
    printf("\n6. Step-by-Step Reversal:");
    char stepStr[] = "ABCDEF";
    int len = strlen(stepStr);
    
    printf("\nInitial: ");
    displayStringWithPositions(stepStr);
    
    int left = 0, right = len - 1;
    int step = 1;
    
    while (left < right) {
        printf("\nStep %d: Swap positions %d and %d ('%c' and '%c')",
               step++, left, right, stepStr[left], stepStr[right]);
        
        char temp = stepStr[left];
        stepStr[left] = stepStr[right];
        stepStr[right] = temp;
        
        printf("\nResult: ");
        displayStringWithPositions(stepStr);
        
        left++;
        right--;
    }
    
    // Performance demonstration
    printf("\n7. Performance Considerations:\n");
    char largeStr[] = "This is a moderately long string that will be reversed to demonstrate performance";
    printf("String length: %zu characters\n", strlen(largeStr));
    printf("Maximum swap operations: %zu\n", strlen(largeStr) / 2);
    
    // Safe reversal with buffer size
    printf("\n8. Safe Reversal with Buffer Size:\n");
    char safeStr[20] = "Buffer safety";
    printf("Original: \"%s\" (buffer size: 20)\n", safeStr);
    if (safeReverseString(safeStr, sizeof(safeStr)) == 1) {
        printf("Reversed: \"%s\"\n", safeStr);
    }
    
    // Interactive test
    printf("\n9. Interactive Test:\n");
    printf("Enter a string to reverse (or 'quit' to exit):\n");
    
    char input[200];
    while (1) {
        printf("\n> ");
        fgets(input, sizeof(input), stdin);
        
        // Remove newline character
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "quit") == 0) {
            break;
        }
        
        printf("Original: \"%s\"\n", input);
        reverseString(input);
        printf("Reversed: \"%s\"\n", input);
        
        // Check if it's a palindrome
        char original[200];
        strcpy(original, input);
        reverseString(input);
        if (strcmp(original, input) == 0) {
            printf("This is a palindrome!\n");
        }
    }
    
    // Summary
    printf("\n\nImplementation Summary:\n");
    printf("=====================\n");
    printf("- Time Complexity: O(n)\n");
    printf("- Space Complexity: O(1) for iterative methods\n");
    printf("- Space Complexity: O(n) for recursive method (stack frames)\n");
    printf("- All methods modify the original string in-place\n");
    printf("- The XOR swap method avoids temporary variables\n");
    printf("- Always ensure strings are modifiable (not string literals)\n");
    
    return 0;
}