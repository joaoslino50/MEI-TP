#include <stdio.h>

// Recursive function to calculate factorial
int factorial(int n) {
    // Base case: 0! = 1 and 1! = 1
    if (n == 0 || n == 1) {
        return 1;
    }

    // Recursive case
    return n * factorial(n - 1);
}

int main() {
    int n = 5;

    printf("Factorial of %d is %d\n", n, factorial(n));

    return 0;
}
