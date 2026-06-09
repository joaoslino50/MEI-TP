#include <stdio.h>
#include <stdlib.h>

// Iterative version of Euclidean algorithm
int gcdIterative(int a, int b) {
    // Make sure we're working with positive numbers
    a = abs(a);
    b = abs(b);
    
    // Euclidean algorithm
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}

// Recursive version of Euclidean algorithm
int gcdRecursive(int a, int b) {
    // Make positive
    a = abs(a);
    b = abs(b);
    
    // Base case: if b is 0, GCD is a
    if (b == 0) {
        return a;
    }
    
    // Recursive case: GCD(a, b) = GCD(b, a % b)
    return gcdRecursive(b, a % b);
}

// Extended Euclidean Algorithm
// Finds GCD and also coefficients x, y such that ax + by = GCD(a, b)
int extendedGCD(int a, int b, int *x, int *y) {
    // Base case
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    
    int x1, y1;
    int gcd = extendedGCD(b, a % b, &x1, &y1);
    
    // Update x and y using results of recursive call
    *x = y1;
    *y = x1 - (a / b) * y1;
    
    return gcd;
}

// Binary GCD Algorithm (Stein's algorithm) - often faster
int gcdBinary(int a, int b) {
    a = abs(a);
    b = abs(b);
    
    if (a == 0) return b;
    if (b == 0) return a;
    
    // Find common power of 2
    int shift;
    for (shift = 0; ((a | b) & 1) == 0; shift++) {
        a >>= 1;
        b >>= 1;
    }
    
    // Make a odd
    while ((a & 1) == 0) {
        a >>= 1;
    }
    
    // Main loop
    do {
        // Make b odd
        while ((b & 1) == 0) {
            b >>= 1;
        }
        
        // Swap if necessary
        if (a > b) {
            int temp = a;
            a = b;
            b = temp;
        }
        
        b = b - a;
    } while (b != 0);
    
    // Restore common factor of 2
    return a << shift;
}

// GCD for three or more numbers
int gcdMultiple(int arr[], int n) {
    if (n == 0) return 0;
    
    int result = arr[0];
    for (int i = 1; i < n; i++) {
        result = gcdIterative(result, arr[i]);
        if (result == 1) {
            return 1; // Early exit if GCD becomes 1
        }
    }
    return result;
}

// Function to demonstrate step-by-step calculation
void demonstrateGCD(int a, int b) {
    printf("\nCalculating GCD(%d, %d):\n", a, b);
    printf("================================\n");
    
    int x = a, y = b;
    int step = 1;
    
    printf("Step %d: %d = %d * %d + %d\n", step++, x, y, x / y, x % y);
    
    while (y != 0) {
        int remainder = x % y;
        printf("Step %d: %d = %d * %d + %d\n", step++, y, remainder, y / remainder, y % remainder);
        x = y;
        y = remainder;
    }
    
    printf("\nGCD(%d, %d) = %d\n", a, b, x);
}

// Utility function to find LCM using GCD
int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return abs(a * b) / gcdIterative(a, b);
}

int main() {
    printf("Euclidean Algorithm - Greatest Common Divisor\n");
    printf("=============================================\n");
    
    // Test case 1: Basic example
    int a = 48, b = 18;
    printf("\nTest 1: GCD(%d, %d)\n", a, b);
    printf("  Iterative: %d\n", gcdIterative(a, b));
    printf("  Recursive: %d\n", gcdRecursive(a, b));
    printf("  Binary: %d\n", gcdBinary(a, b));
    printf("  LCM: %d\n", lcm(a, b));
    
    // Test case 2: Negative numbers
    a = -24, b = 36;
    printf("\nTest 2: GCD(%d, %d)\n", a, b);
    printf("  Iterative: %d\n", gcdIterative(a, b));
    printf("  Recursive: %d\n", gcdRecursive(a, b));
    
    // Test case 3: Prime numbers
    a = 17, b = 23;
    printf("\nTest 3: GCD(%d, %d)\n", a, b);
    printf("  Result: %d (coprime numbers)\n", gcdIterative(a, b));
    
    // Test case 4: One number is zero
    a = 0, b = 25;
    printf("\nTest 4: GCD(%d, %d)\n", a, b);
    printf("  Result: %d (GCD with zero)\n", gcdIterative(a, b));
    
    // Test case 5: Equal numbers
    a = 42, b = 42;
    printf("\nTest 5: GCD(%d, %d)\n", a, b);
    printf("  Result: %d\n", gcdIterative(a, b));
    
    // Test case 6: Large numbers
    a = 1071, b = 462;
    printf("\nTest 6: GCD(%d, %d)\n", a, b);
    printf("  Result: %d\n", gcdIterative(a, b));
    
    // Step-by-step demonstration
    demonstrateGCD(48, 18);
    demonstrateGCD(1071, 462);
    demonstrateGCD(123456, 789012);
    
    // Extended Euclidean Algorithm demonstration
    printf("\nExtended Euclidean Algorithm:\n");
    printf("================================\n");
    a = 35, b = 15;
    int x, y;
    int gcd = extendedGCD(a, b, &x, &y);
    printf("For GCD(%d, %d) = %d\n", a, b, gcd);
    printf("  Coefficients: x = %d, y = %d\n", x, y);
    printf("  Verification: %d*%d + %d*%d = %d\n", a, x, b, y, a*x + b*y);
    
    // Test with multiple numbers
    printf("\nGCD of Multiple Numbers:\n");
    printf("================================\n");
    int numbers[] = {24, 36, 48, 60};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("Numbers: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\nGCD: %d\n", gcdMultiple(numbers, n));
    
    // Table of GCDs
    printf("\nGCD Table (1-10):\n");
    printf("    ");
    for (int i = 1; i <= 10; i++) {
        printf("%4d", i);
    }
    printf("\n    ");
    for (int i = 1; i <= 10; i++) {
        printf("----");
    }
    printf("\n");
    
    for (int i = 1; i <= 10; i++) {
        printf("%2d |", i);
        for (int j = 1; j <= 10; j++) {
            printf("%4d", gcdIterative(i, j));
        }
        printf("\n");
    }
    
    // Performance comparison
    printf("\nPerformance Characteristics:\n");
    printf("================================\n");
    printf("Euclidean Algorithm: O(log min(a,b))\n");
    printf("- Iterative: Faster, no recursion overhead\n");
    printf("- Recursive: Cleaner code, but O(log n) stack space\n");
    printf("- Binary GCD: Uses bit operations, sometimes faster\n");
    printf("- Extended GCD: Also finds Bézout coefficients\n");
    
    // Interactive mode
    printf("\nInteractive Mode:\n");
    printf("Enter two numbers (or '0 0' to exit):\n");
    
    int num1, num2;
    while (1) {
        printf("\n> ");
        scanf("%d %d", &num1, &num2);
        
        if (num1 == 0 && num2 == 0) {
            break;
        }
        
        printf("GCD(%d, %d) = %d\n", num1, num2, gcdIterative(num1, num2));
        printf("LCM(%d, %d) = %d\n", num1, num2, lcm(num1, num2));
        
        // Show Bézout coefficients
        if (num1 != 0 && num2 != 0) {
            extendedGCD(num1, num2, &x, &y);
            printf("Bézout: %d = %d*%d + %d*%d\n", 
                   gcdIterative(num1, num2), num1, x, num2, y);
        }
    }
    
    return 0;
}