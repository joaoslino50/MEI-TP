#include <stdio.h>
#include <stdlib.h>

// Iterative function to generate first n Fibonacci numbers
// Returns a dynamically allocated array containing the sequence
unsigned long long* fibonacci_sequence(int n) {
    // Handle invalid input
    if (n <= 0) {
        return NULL;
    }
    
    // Allocate memory for the sequence
    unsigned long long* fib = (unsigned long long*)malloc(n * sizeof(unsigned long long));
    if (fib == NULL) {
        return NULL; // Memory allocation failed
    }
    
    // Generate Fibonacci sequence iteratively
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            fib[i] = 0; // First Fibonacci number
        }
        else if (i == 1) {
            fib[i] = 1; // Second Fibonacci number
        }
        else {
            fib[i] = fib[i - 1] + fib[i - 2]; // Each subsequent number
        }
    }
    
    return fib;
}

// Alternative: Function that prints the sequence directly
void print_fibonacci_sequence(int n) {
    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return;
    }
    
    unsigned long long a = 0, b = 1, next;
    
    printf("First %d Fibonacci numbers: ", n);
    
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            printf("%llu", a);
        }
        else if (i == 1) {
            printf(", %llu", b);
        }
        else {
            next = a + b;
            printf(", %llu", next);
            a = b;
            b = next;
        }
    }
    printf("\n");
}

int main() {
    int n;
    
    printf("Enter the number of Fibonacci numbers to generate: ");
    scanf("%d", &n);
    
    // Method 1: Get array from function
    unsigned long long* sequence = fibonacci_sequence(n);
    
    if (sequence != NULL) {
        printf("First %d Fibonacci numbers: ", n);
        for (int i = 0; i < n; i++) {
            printf("%llu", sequence[i]);
            if (i < n - 1) {
                printf(", ");
            }
        }
        printf("\n");
        
        // Free the allocated memory
        free(sequence);
    } else if (n > 0) {
        printf("Memory allocation failed.\n");
    }
    
    printf("\n");
    
    // Method 2: Print directly (more memory efficient)
    print_fibonacci_sequence(n);
    
    return 0;
}