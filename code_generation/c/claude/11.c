#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Basic iterative function to sum digits
int sumOfDigits(int n) {
    // Handle negative numbers by taking absolute value
    n = abs(n);
    
    int sum = 0;
    
    // Extract each digit and add to sum
    while (n > 0) {
        sum += n % 10;  // Add the last digit
        n /= 10;        // Remove the last digit
    }
    
    return sum;
}

// Recursive version
int sumOfDigitsRecursive(int n) {
    n = abs(n);
    
    // Base case: if n is 0, return 0
    if (n == 0) {
        return 0;
    }
    
    // Recursive case: last digit + sum of remaining digits
    return (n % 10) + sumOfDigitsRecursive(n / 10);
}

// Using for loop
int sumOfDigitsForLoop(int n) {
    n = abs(n);
    int sum = 0;
    
    for (; n > 0; n /= 10) {
        sum += n % 10;
    }
    
    return sum;
}

// Using string conversion (alternative approach)
int sumOfDigitsString(int n) {
    char str[20];
    sprintf(str, "%d", abs(n));
    
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        sum += str[i] - '0';  // Convert char to int
    }
    
    return sum;
}

// Function to sum digits until single digit (digital root)
int digitalRoot(int n) {
    n = abs(n);
    
    // If n is 0, digital root is 0
    if (n == 0) return 0;
    
    // Digital root formula: 1 + (n-1) % 9
    return 1 + (n - 1) % 9;
}

// Alternative digital root using iteration
int digitalRootIterative(int n) {
    n = abs(n);
    
    while (n >= 10) {
        n = sumOfDigits(n);
    }
    
    return n;
}

// Sum of digits with different number bases
int sumOfDigitsInBase(int n, int base) {
    if (base < 2) return -1; // Invalid base
    
    n = abs(n);
    int sum = 0;
    
    while (n > 0) {
        sum += n % base;
        n /= base;
    }
    
    return sum;
}

// Function to sum digits and count number of digits
void sumAndCountDigits(int n, int *sum, int *count) {
    n = abs(n);
    *sum = 0;
    *count = 0;
    
    if (n == 0) {
        *count = 1;
        return;
    }
    
    while (n > 0) {
        *sum += n % 10;
        (*count)++;
        n /= 10;
    }
}

// Check if a number is divisible by the sum of its digits (Harshad number)
bool isHarshadNumber(int n) {
    if (n == 0) return false;
    
    int sum = sumOfDigits(n);
    return n % sum == 0;
}

// Function to demonstrate digit sum with detailed steps
void demonstrateDigitSum(int n) {
    printf("\nCalculating sum of digits for %d:\n", n);
    printf("=================================\n");
    
    int original = n;
    n = abs(n);
    int sum = 0;
    int step = 1;
    
    printf("%d = ", original);
    
    while (n > 0) {
        int digit = n % 10;
        sum += digit;
        
        printf("%d", digit);
        if (n >= 10) {
            printf(" + ");
        }
        
        n /= 10;
    }
    
    printf(" = %d\n", sum);
    printf("Sum of digits: %d\n", sum);
}

// Print all Harshad numbers up to a limit
void printHarshadNumbers(int limit) {
    printf("\nHarshad numbers up to %d:\n", limit);
    int count = 0;
    
    for (int i = 1; i <= limit; i++) {
        if (isHarshadNumber(i)) {
            printf("%d ", i);
            count++;
        }
    }
    
    printf("\nTotal: %d Harshad numbers found\n", count);
}

// Alternative: Using pointer for memory efficiency
void sumOfDigitsPointer(int n, int *result) {
    *result = 0;
    n = abs(n);
    
    while (n > 0) {
        *result += n % 10;
        n /= 10;
    }
}

// Sum of digits of a long long integer
long long sumOfDigitsLongLong(long long n) {
    if (n < 0) n = -n;
    
    long long sum = 0;
    
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    
    return sum;
}

int main() {
    printf("DIGIT SUM FUNCTIONS IN C\n");
    printf("=======================\n");
    
    // Test various numbers
    int testNumbers[] = {12345, 9876, 1000, 0, -54321, 999999, 7};
    int numTests = sizeof(testNumbers) / sizeof(testNumbers[0]);
    
    printf("\n%-10s | %-15s | %-15s | %-15s | %-15s\n", 
           "Number", "Iterative", "Recursive", "For Loop", "String");
    printf("-----------|-----------------|-----------------|-----------------|-----------------\n");
    
    for (int i = 0; i < numTests; i++) {
        int n = testNumbers[i];
        printf("%-10d | %-15d | %-15d | %-15d | %-15d\n",
               n,
               sumOfDigits(n),
               sumOfDigitsRecursive(n),
               sumOfDigitsForLoop(n),
               sumOfDigitsString(n));
    }
    
    // Detailed demonstration
    demonstrateDigitSum(12345);
    demonstrateDigitSum(-9876);
    demonstrateDigitSum(1000000);
    
    // Digital root examples
    printf("\nDigital Root (Single Digit Sum):\n");
    printf("================================\n");
    int numbers[] = {12345, 9876, 9999, 123456789};
    for (int i = 0; i < 4; i++) {
        int n = numbers[i];
        printf("Digital root of %d: %d (iterative: %d)\n", 
               n, 
               digitalRoot(n),
               digitalRootIterative(n));
    }
    
    // Different bases
    printf("\nSum of Digits in Different Bases:\n");
    printf("================================\n");
    int num = 255;
    printf("Number: %d\n", num);
    printf("  Base 10: %d\n", sumOfDigitsInBase(num, 10));
    printf("  Base 2: %d\n", sumOfDigitsInBase(num, 2));
    printf("  Base 8: %d\n", sumOfDigitsInBase(num, 8));
    printf("  Base 16: %d\n", sumOfDigitsInBase(num, 16));
    
    // Sum and count together
    printf("\nSum and Count of Digits:\n");
    printf("=======================\n");
    int testNum = 123456789;
    int sum, count;
    sumAndCountDigits(testNum, &sum, &count);
    printf("Number: %d\n", testNum);
    printf("  Sum of digits: %d\n", sum);
    printf("  Number of digits: %d\n", count);
    
    // Harshad numbers
    printf("\nHarshad Numbers:\n");
    printf("===============\n");
    int harshadTests[] = {18, 21, 27, 30, 42, 45, 50, 100, 111};
    for (int i = 0; i < 9; i++) {
        int n = harshadTests[i];
        printf("%d is %s Harshad number\n", 
               n, 
               isHarshadNumber(n) ? "a" : "not a");
    }
    
    printHarshadNumbers(100);
    
    // Large number processing
    printf("\nLarge Number Processing:\n");
    printf("=======================\n");
    long long bigNum = 123456789012345LL;
    printf("Number: %lld\n", bigNum);
    printf("Sum of digits: %lld\n", sumOfDigitsLongLong(bigNum));
    
    // Edge cases
    printf("\nEdge Cases:\n");
    printf("===========\n");
    printf("0: sum = %d\n", sumOfDigits(0));
    printf("1: sum = %d\n", sumOfDigits(1));
    printf("10: sum = %d\n", sumOfDigits(10));
    printf("-100: sum = %d\n", sumOfDigits(-100));
    printf("INT_MAX: sum = %d\n", sumOfDigits(2147483647));
    
    // Performance comparison
    printf("\nPerformance Comparison (1,000,000 iterations):\n");
    printf("==============================================\n");
    
    int iterations = 1000000;
    int result;
    
    // Test iterative
    clock_t start = clock();
    for (int i = 0; i < iterations; i++) {
        result = sumOfDigits(123456789);
    }
    clock_t end = clock();
    double time_iterative = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Iterative: %.4f seconds\n", time_iterative);
    
    // Test recursive
    start = clock();
    for (int i = 0; i < iterations; i++) {
        result = sumOfDigitsRecursive(123456789);
    }
    end = clock();
    double time_recursive = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Recursive: %.4f seconds\n", time_recursive);
    
    // Test string method
    start = clock();
    for (int i = 0; i < iterations; i++) {
        result = sumOfDigitsString(123456789);
    }
    end = clock();
    double time_string = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("String method: %.4f seconds\n", time_string);
    
    // Interactive mode
    printf("\nInteractive Mode:\n");
    printf("Enter an integer to sum its digits (or 0 to exit):\n");
    
    int input;
    while (1) {
        printf("\n> ");
        scanf("%d", &input);
        
        if (input == 0) {
            break;
        }
        
        printf("Number: %d\n", input);
        printf("Sum of digits: %d\n", sumOfDigits(input));
        printf("Digital root: %d\n", digitalRoot(input));
        
        if (isHarshadNumber(input)) {
            printf("%d is a Harshad number (divisible by sum of its digits)\n", input);
        }
        
        // Show detailed digit breakdown
        int temp = abs(input);
        printf("Digit breakdown: ");
        int digits[20];
        int count_digits = 0;
        while (temp > 0) {
            digits[count_digits++] = temp % 10;
            temp /= 10;
        }
        for (int i = count_digits - 1; i >= 0; i--) {
            printf("%d", digits[i]);
            if (i > 0) printf(" + ");
        }
        printf(" = %d\n", sumOfDigits(input));
    }
    
    // Summary
    printf("\n=== IMPLEMENTATION SUMMARY ===\n");
    printf("Time Complexity: O(log₁₀ n) - number of digits\n");
    printf("Space Complexity: O(1) for iterative, O(log n) for recursive\n");
    printf("\nKey Points:\n");
    printf("  - Use abs() to handle negative numbers\n");
    printf("  - n % 10 extracts the last digit\n");
    printf("  - n / 10 removes the last digit\n");
    printf("  - Digital root can be computed directly with formula\n");
    printf("  - String method is convenient but slower\n");
    
    return 0;
}