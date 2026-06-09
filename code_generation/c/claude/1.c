#include <stdio.h>

// Recursive function to calculate factorial
long long factorial(int n) {
    // Base case: factorial of 0 or 1 is 1
    if (n == 0 || n == 1) {
        return 1;
    }
    // Recursive case: n! = n * (n-1)!
    else if (n > 1) {
        return n * factorial(n - 1);
    }
    // Handle negative numbers
    else {
        return -1; // Error indicator for invalid input
    }
}

int main() {
    int n;
    
    printf("Enter a non-negative integer: ");
    scanf("%d", &n);
    
    long long result = factorial(n);
    
    if (result == -1) {
        printf("Error: Factorial is not defined for negative numbers.\n");
    } else {
        printf("Factorial of %d is %lld\n", n, result);
    }
    
    return 0;
}