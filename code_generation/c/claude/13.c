#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

// Method 1: Using character count array (most efficient)
bool areAnagramsCount(char str1[], char str2[]) {
    // If lengths differ, they can't be anagrams
    if (strlen(str1) != strlen(str2)) {
        return false;
    }
    
    // Create count array for 256 ASCII characters
    int count[256] = {0};
    
    // Count characters in first string
    for (int i = 0; str1[i] != '\0'; i++) {
        count[tolower(str1[i])]++;
    }
    
    // Decrement count for characters in second string
    for (int i = 0; str2[i] != '\0'; i++) {
        count[tolower(str2[i])]--;
    }
    
    // If all counts are zero, strings are anagrams
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            return false;
        }
    }
    
    return true;
}

// Method 2: Case-sensitive version
bool areAnagramsCaseSensitive(char str1[], char str2[]) {
    if (strlen(str1) != strlen(str2)) {
        return false;
    }
    
    int count[256] = {0};
    
    for (int i = 0; str1[i] != '\0'; i++) {
        count[str1[i]]++;
    }
    
    for (int i = 0; str2[i] != '\0'; i++) {
        count[str2[i]]--;
    }
    
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            return false;
        }
    }
    
    return true;
}

// Method 3: Using sorting (easier to understand)
int compareChars(const void *a, const void *b) {
    return *(char*)a - *(char*)b;
}

bool areAnagramsSorting(char str1[], char str2[]) {
    if (strlen(str1) != strlen(str2)) {
        return false;
    }
    
    // Create copies to avoid modifying original strings
    char copy1[1000], copy2[1000];
    strcpy(copy1, str1);
    strcpy(copy2, str2);
    
    // Convert to lowercase for case-insensitive comparison
    for (int i = 0; copy1[i]; i++) copy1[i] = tolower(copy1[i]);
    for (int i = 0; copy2[i]; i++) copy2[i] = tolower(copy2[i]);
    
    // Sort both strings
    qsort(copy1, strlen(copy1), sizeof(char), compareChars);
    qsort(copy2, strlen(copy2), sizeof(char), compareChars);
    
    // Compare sorted strings
    return strcmp(copy1, copy2) == 0;
}

// Method 4: Ignoring non-alphanumeric characters (for phrases)
bool areAnagramsPhrase(char str1[], char str2[]) {
    int count[256] = {0};
    
    // Count alphanumeric characters from first string
    for (int i = 0; str1[i] != '\0'; i++) {
        if (isalnum(str1[i])) {
            count[tolower(str1[i])]++;
        }
    }
    
    // Decrement for alphanumeric characters from second string
    for (int i = 0; str2[i] != '\0'; i++) {
        if (isalnum(str2[i])) {
            count[tolower(str2[i])]--;
        }
    }
    
    // Check if all counts are zero
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            return false;
        }
    }
    
    return true;
}

// Method 5: Using a single array with optimization for lowercase letters only
bool areAnagramsOptimized(char str1[], char str2[]) {
    if (strlen(str1) != strlen(str2)) {
        return false;
    }
    
    int count[26] = {0}; // Only for 'a' to 'z'
    
    for (int i = 0; str1[i] != '\0'; i++) {
        if (isalpha(str1[i])) {
            count[tolower(str1[i]) - 'a']++;
        }
    }
    
    for (int i = 0; str2[i] != '\0'; i++) {
        if (isalpha(str2[i])) {
            count[tolower(str2[i]) - 'a']--;
        }
    }
    
    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) {
            return false;
        }
    }
    
    return true;
}

// Function to demonstrate detailed step-by-step check
void demonstrateAnagramCheck(char str1[], char str2[]) {
    printf("\n========================================\n");
    printf("Checking: \"%s\" and \"%s\"\n", str1, str2);
    printf("========================================\n");
    
    // Show lengths
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    printf("Lengths: %d vs %d\n", len1, len2);
    
    if (len1 != len2) {
        printf("❌ Different lengths - cannot be anagrams\n");
        return;
    }
    
    // Show character frequency analysis
    printf("\nCharacter frequency analysis (case-insensitive):\n");
    int count[26] = {0};
    
    // Count characters from first string
    for (int i = 0; str1[i] != '\0'; i++) {
        if (isalpha(str1[i])) {
            char c = tolower(str1[i]);
            count[c - 'a']++;
        }
    }
    
    printf("\nFirst string frequencies:\n");
    for (int i = 0; i < 26; i++) {
        if (count[i] > 0) {
            printf("  '%c': %d\n", 'a' + i, count[i]);
        }
    }
    
    // Decrement for second string and track
    printf("\nProcessing second string:\n");
    bool isAnagram = true;
    for (int i = 0; str2[i] != '\0'; i++) {
        if (isalpha(str2[i])) {
            char c = tolower(str2[i]);
            count[c - 'a']--;
            printf("  Decrement '%c': new count = %d\n", c, count[c - 'a']);
        }
    }
    
    printf("\nFinal check:\n");
    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) {
            printf("  '%c': count = %d ❌\n", 'a' + i, count[i]);
            isAnagram = false;
        }
    }
    
    if (isAnagram) {
        printf("\n✅ Strings ARE anagrams!\n");
    } else {
        printf("\n❌ Strings are NOT anagrams\n");
    }
}

// Helper function to run multiple test cases
void testAnagramFunction(const char* name, 
                         bool (*func)(char[], char[]), 
                         char str1[], char str2[]) {
    printf("%s: %s\n", name, func(str1, str2) ? "YES ✓" : "NO ✗");
}

int main() {
    printf("ANAGRAM CHECKER IN C\n");
    printf("===================\n");
    
    // Test cases
    struct {
        char str1[100];
        char str2[100];
        const char* description;
    } testCases[] = {
        {"listen", "silent", "Basic anagram"},
        {"hello", "world", "Not anagrams"},
        {"angel", "glean", "Another anagram"},
        {"rail safety", "fairy tales", "Phrase anagram"},
        {"Debit Card", "Bad Credit", "Anagram with spaces and case"},
        {"Astronomer", "Moon starer", "Complex anagram"},
        {"aabbcc", "abcabc", "Repeated characters"},
        {"", "", "Empty strings"},
        {"a", "a", "Single character"},
        {"ab", "ba", "Two characters"},
        {"abc", "def", "Different characters"}
    };
    
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    printf("\n%-20s | %-20s | %-15s | %-10s | %-10s | %-10s\n",
           "String 1", "String 2", "Description", "Count", "Sort", "Phrase");
    printf("--------------------|--------------------|-----------------|-----------|-----------|-----------\n");
    
    for (int i = 0; i < numTests; i++) {
        char s1[100], s2[100];
        strcpy(s1, testCases[i].str1);
        strcpy(s2, testCases[i].str2);
        
        printf("%-20s | %-20s | %-15s | %-10s | %-10s | %-10s\n",
               s1, s2, testCases[i].description,
               areAnagramsCount(s1, s2) ? "YES" : "NO",
               areAnagramsSorting(s1, s2) ? "YES" : "NO",
               areAnagramsPhrase(s1, s2) ? "YES" : "NO");
    }
    
    // Detailed demonstration for a specific case
    demonstrateAnagramCheck("listen", "silent");
    demonstrateAnagramCheck("hello", "world");
    demonstrateAnagramCheck("Debit Card", "Bad Credit");
    
    // Test case sensitivity
    printf("\n=== CASE SENSITIVITY TEST ===\n");
    char caseTest1[] = "Listen";
    char caseTest2[] = "silent";
    char caseTest3[] = "Listen";
    char caseTest4[] = "Silent";
    
    printf("Case-insensitive: \"%s\" vs \"%s\" -> %s\n", 
           caseTest1, caseTest2, 
           areAnagramsCount(caseTest1, caseTest2) ? "Anagram" : "Not anagram");
    printf("Case-sensitive: \"%s\" vs \"%s\" -> %s\n", 
           caseTest1, caseTest2, 
           areAnagramsCaseSensitive(caseTest1, caseTest2) ? "Anagram" : "Not anagram");
    printf("Case-insensitive: \"%s\" vs \"%s\" -> %s\n", 
           caseTest3, caseTest4, 
           areAnagramsCount(caseTest3, caseTest4) ? "Anagram" : "Not anagram");
    
    // Performance comparison
    printf("\n=== PERFORMANCE COMPARISON ===\n");
    char longStr1[10000], longStr2[10000];
    
    // Create two large anagram strings
    for (int i = 0; i < 4999; i++) {
        longStr1[i] = 'a' + (i % 26);
        longStr2[i] = 'a' + ((i + 13) % 26);
    }
    longStr1[4999] = longStr2[4999] = '\0';
    
    clock_t start, end;
    double time_count, time_sort;
    
    // Test count method
    start = clock();
    for (int i = 0; i < 10000; i++) {
        areAnagramsCount(longStr1, longStr2);
    }
    end = clock();
    time_count = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // Test sorting method
    start = clock();
    for (int i = 0; i < 10000; i++) {
        areAnagramsSorting(longStr1, longStr2);
    }
    end = clock();
    time_sort = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("10,000 iterations on 5000-character strings:\n");
    printf("  Count array method: %.4f seconds\n", time_count);
    printf("  Sorting method: %.4f seconds\n", time_sort);
    printf("  Count method is %.2fx faster\n", time_sort / time_count);
    
    // Interactive mode
    printf("\n=== INTERACTIVE MODE ===\n");
    printf("Enter two strings to check if they are anagrams (or 'quit' to exit):\n");
    
    char input1[200], input2[200];
    
    while (1) {
        printf("\nFirst string: ");
        fgets(input1, sizeof(input1), stdin);
        input1[strcspn(input1, "\n")] = 0; // Remove newline
        
        if (strcmp(input1, "quit") == 0) break;
        
        printf("Second string: ");
        fgets(input2, sizeof(input2), stdin);
        input2[strcspn(input2, "\n")] = 0;
        
        if (strcmp(input2, "quit") == 0) break;
        
        printf("\nResults:\n");
        printf("  Basic (case-insensitive): %s\n", 
               areAnagramsCount(input1, input2) ? "✓ ANAGRAMS" : "✗ NOT anagrams");
        printf("  Case-sensitive: %s\n", 
               areAnagramsCaseSensitive(input1, input2) ? "✓ ANAGRAMS" : "✗ NOT anagrams");
        printf("  Ignoring non-alphanumeric: %s\n", 
               areAnagramsPhrase(input1, input2) ? "✓ ANAGRAMS" : "✗ NOT anagrams");
        
        // Show character counts for debugging
        if (!areAnagramsCount(input1, input2) && strlen(input1) == strlen(input2)) {
            printf("\nCharacter count difference:\n");
            int count[26] = {0};
            for (int i = 0; input1[i]; i++) {
                if (isalpha(input1[i])) count[tolower(input1[i]) - 'a']++;
            }
            for (int i = 0; input2[i]; i++) {
                if (isalpha(input2[i])) count[tolower(input2[i]) - 'a']--;
            }
            
            printf("  Characters with imbalance:\n");
            for (int i = 0; i < 26; i++) {
                if (count[i] != 0) {
                    printf("    '%c': %+d\n", 'a' + i, count[i]);
                }
            }
        }
    }
    
    // Educational section
    printf("\n=== EDUCATIONAL NOTES ===\n");
    printf("What are anagrams?\n");
    printf("  Two strings are anagrams if they contain the same characters\n");
    printf("  in the same frequencies, ignoring case, spaces, and punctuation.\n\n");
    
    printf("Algorithm complexity:\n");
    printf("  Count array method: O(n) time, O(1) space\n");
    printf("  Sorting method: O(n log n) time, O(n) space\n\n");
    
    printf("Common anagram examples:\n");
    printf("  • 'listen' -> 'silent'\n");
    printf("  • 'angel' -> 'glean'\n");
    printf("  • 'rail safety' -> 'fairy tales'\n");
    printf("  • 'debit card' -> 'bad credit'\n");
    printf("  • 'astronomer' -> 'moon starer'\n");
    
    return 0;
}