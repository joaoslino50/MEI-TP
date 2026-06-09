#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Function to check if a string is a palindrome (ignoring case)
bool isPalindrome(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    int left = 0;
    int right = strlen(str) - 1;
    
    while (left < right) {
        // Skip non-alphanumeric characters (optional - uncomment if needed)
        // while (left < right && !isalnum(str[left])) left++;
        // while (left < right && !isalnum(str[right])) right--;
        
        // Compare characters ignoring case
        if (tolower(str[left]) != tolower(str[right])) {
            return false;
        }
        
        left++;
        right--;
    }
    
    return true;
}

// Alternative: Function that ignores non-alphanumeric characters
// (useful for phrases like "A man, a plan, a canal: Panama")
bool isPalindromeAlphaNumeric(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    int left = 0;
    int right = strlen(str) - 1;
    
    while (left < right) {
        // Skip non-alphanumeric characters from left
        while (left < right && !isalnum(str[left])) {
            left++;
        }
        // Skip non-alphanumeric characters from right
        while (left < right && !isalnum(str[right])) {
            right--;
        }
        
        // Compare alphanumeric characters ignoring case
        if (tolower(str[left]) != tolower(str[right])) {
            return false;
        }
        
        left++;
        right--;
    }
    
    return true;
}

// Recursive version (for educational purposes)
bool isPalindromeRecursive(const char *str, int left, int right) {
    // Base case: if pointers cross, it's a palindrome
    if (left >= right) {
        return true;
    }
    
    // Compare characters ignoring case
    if (tolower(str[left]) != tolower(str[right])) {
        return false;
    }
    
    // Recursive case: check inner substring
    return isPalindromeRecursive(str, left + 1, right - 1);
}

// Wrapper function for recursive version
bool isPalindromeRecursiveWrapper(const char *str) {
    if (str == NULL) {
        return false;
    }
    return isPalindromeRecursive(str, 0, strlen(str) - 1);
}

// Function to test and display results
void testPalindrome(const char *str) {
    printf("\n\"%s\"", str);
    
    if (isPalindrome(str)) {
        printf(" → IS a palindrome (basic)");
    } else {
        printf(" → NOT a palindrome (basic)");
    }
    
    if (isPalindromeAlphaNumeric(str)) {
        printf(" → IS a palindrome (alphanumeric only)");
    } else {
        printf(" → NOT a palindrome (alphanumeric only)");
    }
    
    if (isPalindromeRecursiveWrapper(str)) {
        printf(" → IS a palindrome (recursive)");
    } else {
        printf(" → NOT a palindrome (recursive)");
    }
    
    printf("\n");
}

int main() {
    printf("Palindrome Checker (Case-Insensitive)\n");
    printf("=====================================\n");
    
    // Test case 1: Simple palindrome
    testPalindrome("racecar");
    
    // Test case 2: Palindrome with mixed case
    testPalindrome("RaCeCaR");
    
    // Test case 3: Not a palindrome
    testPalindrome("hello");
    
    // Test case 4: Single character (always palindrome)
    testPalindrome("a");
    
    // Test case 5: Empty string (considered palindrome)
    testPalindrome("");
    
    // Test case 6: Palindrome with spaces
    testPalindrome("never odd or even");
    
    // Test case 7: Palindrome with punctuation (only basic version)
    printf("\n\"A man, a plan, a canal: Panama\"");
    if (isPalindrome("A man, a plan, a canal: Panama")) {
        printf(" → IS a palindrome (basic - fails due to spaces/punctuation)");
    } else {
        printf(" → NOT a palindrome (basic - spaces/punctuation break it)");
    }
    
    if (isPalindromeAlphaNumeric("A man, a plan, a canal: Panama")) {
        printf("\n\"A man, a plan, a canal: Panama\" → IS a palindrome (alphanumeric only)");
    } else {
        printf("\n\"A man, a plan, a canal: Panama\" → NOT a palindrome (alphanumeric only)");
    }
    
    // Test case 8: Number palindrome
    testPalindrome("12321");
    
    // Test case 9: Mixed alphanumeric
    testPalindrome("A1B2C2B1A");
    
    // Test case 10: Null string
    printf("\n\"NULL\"");
    if (isPalindrome(NULL)) {
        printf(" → IS a palindrome");
    } else {
        printf(" → NOT a palindrome (handles NULL safely)");
    }
    
    // Demonstration of manual check
    printf("\n\n=====================================\n");
    printf("Interactive Test:\n");
    
    char input[100];
    printf("Enter a string to check (or 'quit' to exit): ");
    
    while (1) {
        printf("\n> ");
        fgets(input, sizeof(input), stdin);
        
        // Remove newline character
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "quit") == 0) {
            break;
        }
        
        printf("\nResults for \"%s\":\n", input);
        printf("  Basic palindrome check: %s\n", 
               isPalindrome(input) ? "YES" : "NO");
        printf("  Alphanumeric-only check: %s\n", 
               isPalindromeAlphaNumeric(input) ? "YES" : "NO");
        printf("  Recursive check: %s\n", 
               isPalindromeRecursiveWrapper(input) ? "YES" : "NO");
        
        // Show step-by-step comparison
        int len = strlen(input);
        printf("  Comparisons: ");
        for (int i = 0; i < len / 2; i++) {
            printf("\n    %c vs %c", input[i], input[len - 1 - i]);
            if (tolower(input[i]) == tolower(input[len - 1 - i])) {
                printf(" ✓ match");
            } else {
                printf(" ✗ mismatch");
            }
        }
        printf("\n");
    }
    
    // Performance demonstration
    printf("\n=====================================\n");
    printf("Implementation Details:\n");
    printf("- Time Complexity: O(n)\n");
    printf("- Space Complexity: O(1) for iterative, O(n) for recursive\n");
    printf("- Uses tolower() for case-insensitive comparison\n");
    printf("- isalnum() optional for alphanumeric-only checking\n");
    
    return 0;
}