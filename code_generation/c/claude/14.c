#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

// Method 1: Using array to store bits (most common)
void decimalToBinaryArray(int n, char *binary) {
    if (n == 0) {
        strcpy(binary, "0");
        return;
    }
    
    int isNegative = 0;
    if (n < 0) {
        isNegative = 1;
        n = -n;
    }
    
    int bits[32];
    int index = 0;
    
    // Extract bits in reverse order
    while (n > 0) {
        bits[index++] = n % 2;
        n /= 2;
    }
    
    // Add sign for negative numbers (optional)
    int start = 0;
    if (isNegative) {
        binary[start++] = '-';
    }
    
    // Store bits in correct order
    for (int i = index - 1; i >= 0; i--) {
        binary[start++] = bits[i] + '0';
    }
    binary[start] = '\0';
}

// Method 2: Recursive approach
void decimalToBinaryRecursive(int n, char *binary, int *pos) {
    if (n == 0) {
        return;
    }
    
    decimalToBinaryRecursive(n / 2, binary, pos);
    binary[(*pos)++] = (n % 2) + '0';
}

void decimalToBinaryRecursiveWrapper(int n, char *binary) {
    if (n == 0) {
        strcpy(binary, "0");
        return;
    }
    
    int isNegative = 0;
    if (n < 0) {
        isNegative = 1;
        n = -n;
    }
    
    int pos = 0;
    if (isNegative) {
        binary[pos++] = '-';
    }
    
    decimalToBinaryRecursive(n, binary, &pos);
    binary[pos] = '\0';
}

// Method 3: Using bitwise operations (efficient)
void decimalToBinaryBitwise(int n, char *binary) {
    if (n == 0) {
        strcpy(binary, "0");
        return;
    }
    
    unsigned int num = (unsigned int)n; // Handle negative as two's complement
    char temp[33];
    int index = 0;
    
    // Special case for 0
    if (num == 0) {
        temp[index++] = '0';
    } else {
        // Extract bits using bitwise operations
        while (num > 0) {
            temp[index++] = (num & 1) ? '1' : '0';
            num >>= 1;
        }
    }
    
    // Reverse the bits (since we collected from LSB to MSB)
    for (int i = 0; i < index; i++) {
        binary[i] = temp[index - 1 - i];
    }
    binary[index] = '\0';
}

// Method 4: Print binary without storing (direct output)
void printBinary(int n) {
    if (n == 0) {
        printf("0");
        return;
    }
    
    unsigned int num = (unsigned int)n;
    int started = 0;
    
    // Print bits from MSB to LSB (32 bits for int)
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
        if ((num >> i) & 1) {
            started = 1;
            printf("1");
        } else if (started) {
            printf("0");
        }
    }
    
    if (!started) {
        printf("0");
    }
}

// Method 5: Return binary as a string (using malloc)
char* decimalToBinaryString(int n) {
    if (n == 0) {
        char *result = malloc(2);
        strcpy(result, "0");
        return result;
    }
    
    unsigned int num = (unsigned int)n;
    char temp[33];
    int index = 0;
    
    while (num > 0) {
        temp[index++] = (num & 1) ? '1' : '0';
        num >>= 1;
    }
    
    char *result = malloc(index + 1);
    for (int i = 0; i < index; i++) {
        result[i] = temp[index - 1 - i];
    }
    result[index] = '\0';
    
    return result;
}

// Method 6: Two's complement representation (for negative numbers)
void decimalToBinaryTwosComplement(int n, char *binary) {
    unsigned int num = (unsigned int)n; // This automatically gives two's complement
    
    int bits = sizeof(int) * 8;
    for (int i = bits - 1; i >= 0; i--) {
        binary[bits - 1 - i] = ((num >> i) & 1) ? '1' : '0';
    }
    binary[bits] = '\0';
}

// Method 7: Fixed-width binary representation
void decimalToBinaryFixedWidth(int n, int width, char *binary) {
    unsigned int num = (unsigned int)n;
    
    if (width <= 0 || width > 32) {
        width = 8; // Default width
    }
    
    for (int i = width - 1; i >= 0; i--) {
        binary[width - 1 - i] = ((num >> i) & 1) ? '1' : '0';
    }
    binary[width] = '\0';
}

// Helper function to demonstrate step-by-step conversion
void demonstrateConversion(int n) {
    printf("\n========================================\n");
    printf("Converting %d to binary:\n", n);
    printf("========================================\n");
    
    if (n < 0) {
        printf("Negative number: using two's complement\n");
        unsigned int twos = (unsigned int)n;
        printf("Two's complement representation: %u\n", twos);
    }
    
    printf("\nStep-by-step conversion (division method):\n");
    printf("----------------------------------------\n");
    
    int num = abs(n);
    printf("Start with: %d\n", num);
    
    int bits[32];
    int index = 0;
    int step = 1;
    
    while (num > 0) {
        bits[index] = num % 2;
        printf("Step %d: %d ÷ 2 = %d (remainder %d)\n", 
               step++, num, num / 2, bits[index]);
        num /= 2;
        index++;
    }
    
    if (index == 0) {
        printf("Number is 0\n");
        bits[0] = 0;
        index = 1;
    }
    
    printf("\nBits (from LSB to MSB): ");
    for (int i = 0; i < index; i++) {
        printf("%d ", bits[i]);
    }
    
    printf("\nBinary (reading backwards): ");
    for (int i = index - 1; i >= 0; i--) {
        printf("%d", bits[i]);
    }
    printf("\n");
}

// Function to display binary in different formats
void displayBinaryFormats(int n) {
    char binary[65]; // 64 bits + null terminator
    
    printf("\nNumber: %d\n", n);
    printf("--------\n");
    
    decimalToBinaryArray(n, binary);
    printf("Standard binary: %s\n", binary);
    
    decimalToBinaryTwosComplement(n, binary);
    printf("Two's complement (32-bit): %s\n", binary);
    
    decimalToBinaryFixedWidth(n, 8, binary);
    printf("8-bit representation: %s\n", binary);
    
    decimalToBinaryFixedWidth(n, 16, binary);
    printf("16-bit representation: %s\n", binary);
    
    char *dynamic = decimalToBinaryString(n);
    printf("Dynamic allocation: %s\n", dynamic);
    free(dynamic);
}

// Function to verify binary conversion
bool verifyBinary(int decimal, const char *binary) {
    int value = 0;
    int len = strlen(binary);
    
    for (int i = 0; i < len; i++) {
        if (binary[i] == '1') {
            value += pow(2, len - 1 - i);
        }
    }
    
    return value == abs(decimal);
}

int main() {
    printf("DECIMAL TO BINARY CONVERTER\n");
    printf("==========================\n");
    
    // Test various conversion methods
    int testNumbers[] = {0, 1, 2, 5, 10, 15, 16, 31, 32, 42, 100, 255, 256, 511, 512, 1023, 1024};
    int numTests = sizeof(testNumbers) / sizeof(testNumbers[0]);
    
    printf("\n%-8s | %-20s | %-20s | %-20s\n", 
           "Decimal", "Array Method", "Recursive", "Bitwise");
    printf("---------|----------------------|----------------------|----------------------\n");
    
    for (int i = 0; i < numTests; i++) {
        int n = testNumbers[i];
        char binary1[33], binary2[33], binary3[33];
        
        decimalToBinaryArray(n, binary1);
        decimalToBinaryRecursiveWrapper(n, binary2);
        decimalToBinaryBitwise(n, binary3);
        
        printf("%-8d | %-20s | %-20s | %-20s\n", 
               n, binary1, binary2, binary3);
    }
    
    // Test negative numbers
    printf("\n--- NEGATIVE NUMBERS (Two's Complement) ---\n");
    int negNumbers[] = {-1, -2, -5, -10, -42, -128, -32768};
    
    printf("\n%-8s | %-20s | %-20s\n", 
           "Decimal", "Sign + Magnitude", "Two's Complement (32-bit)");
    printf("---------|----------------------|----------------------\n");
    
    for (int i = 0; i < 7; i++) {
        int n = negNumbers[i];
        char binary1[33], binary2[33];
        
        decimalToBinaryArray(n, binary1);
        decimalToBinaryTwosComplement(n, binary2);
        
        printf("%-8d | %-20s | %-20s\n", n, binary1, binary2);
    }
    
    // Step-by-step demonstration
    demonstrateConversion(42);
    demonstrateConversion(255);
    demonstrateConversion(1024);
    
    // Display different formats
    printf("\n\n--- BINARY FORMATS COMPARISON ---\n");
    displayBinaryFormats(42);
    displayBinaryFormats(255);
    displayBinaryFormats(-42);
    
    // Verification of conversions
    printf("\n--- VERIFICATION ---\n");
    printf("Testing conversion accuracy:\n");
    
    for (int i = 0; i < numTests; i++) {
        char binary[33];
        decimalToBinaryArray(testNumbers[i], binary);
        
        if (verifyBinary(testNumbers[i], binary)) {
            printf("✓ %d -> %s (verified)\n", testNumbers[i], binary);
        } else {
            printf("✗ %d -> %s (verification failed!)\n", testNumbers[i], binary);
        }
    }
    
    // Performance comparison
    printf("\n--- PERFORMANCE COMPARISON ---\n");
    int iterations = 1000000;
    clock_t start, end;
    char buffer[33];
    
    // Test array method
    start = clock();
    for (int i = 0; i < iterations; i++) {
        decimalToBinaryArray(123456, buffer);
    }
    end = clock();
    printf("Array method: %.4f seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    
    // Test bitwise method
    start = clock();
    for (int i = 0; i < iterations; i++) {
        decimalToBinaryBitwise(123456, buffer);
    }
    end = clock();
    printf("Bitwise method: %.4f seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    
    // Test recursive method
    start = clock();
    for (int i = 0; i < iterations; i++) {
        decimalToBinaryRecursiveWrapper(123456, buffer);
    }
    end = clock();
    printf("Recursive method: %.4f seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    
    // Print binary for all numbers up to 20
    printf("\n--- BINARY TABLE (0-20) ---\n");
    printf("Decimal | Binary\n");
    printf("--------|------------------\n");
    for (int i = 0; i <= 20; i++) {
        char binary[33];
        decimalToBinaryArray(i, binary);
        printf("%7d | %s\n", i, binary);
    }
    
    // Special binary patterns
    printf("\n--- SPECIAL BINARY PATTERNS ---\n");
    struct {
        int value;
        const char* description;
    } special[] = {
        {1, "2^0 (1)"},
        {2, "2^1 (2)"},
        {4, "2^2 (4)"},
        {8, "2^3 (8)"},
        {16, "2^4 (16)"},
        {32, "2^5 (32)"},
        {64, "2^6 (64)"},
        {128, "2^7 (128)"},
        {255, "2^8 - 1 (all ones in 8 bits)"},
        {511, "2^9 - 1"},
        {1023, "2^10 - 1"},
        {1024, "2^10"}
    };
    
    for (int i = 0; i < 12; i++) {
        char binary[33];
        decimalToBinaryArray(special[i].value, binary);
        printf("%-12s -> %-20s (%s)\n", 
               special[i].description, 
               binary,
               special[i].value >= 0 ? "positive" : "negative");
    }
    
    // Interactive mode
    printf("\n--- INTERACTIVE MODE ---\n");
    printf("Enter decimal numbers to convert to binary (or 'quit' to exit):\n");
    
    char input[50];
    while (1) {
        printf("\n> ");
        fgets(input, sizeof(input), stdin);
        
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "quit") == 0) {
            break;
        }
        
        char *endptr;
        long num = strtol(input, &endptr, 10);
        
        if (*endptr != '\0') {
            printf("Invalid input! Please enter a valid integer.\n");
            continue;
        }
        
        char binary[33];
        printf("\nDecimal: %ld\n", num);
        
        // Show various representations
        decimalToBinaryArray((int)num, binary);
        printf("Standard binary: %s\n", binary);
        
        decimalToBinaryTwosComplement((int)num, binary);
        printf("32-bit binary: %s\n", binary);
        
        // Show number of bits needed
        if (num > 0) {
            int bits = (int)(log2(num)) + 1;
            printf("Minimum bits needed: %d\n", bits);
        }
        
        // Show bit count (number of 1s)
        int count_ones = 0;
        unsigned int unum = (unsigned int)num;
        while (unum) {
            count_ones += (unum & 1);
            unum >>= 1;
        }
        printf("Number of 1 bits: %d\n", count_ones);
    }
    
    // Educational notes
    printf("\n=== EDUCATIONAL NOTES ===\n");
    printf("Binary Number System:\n");
    printf("  - Base-2 system using digits 0 and 1\n");
    printf("  - Each position represents a power of 2\n");
    printf("  - Rightmost bit is 2^0 (least significant)\n");
    printf("  - Leftmost bit is 2^(n-1) (most significant)\n\n");
    
    printf("Conversion Methods:\n");
    printf("  1. Division method: Repeatedly divide by 2 and collect remainders\n");
    printf("  2. Bitwise method: Use shift operators (&, >>)\n");
    printf("  3. Recursive method: Elegant but uses more memory\n\n");
    
    printf("Negative Number Representation:\n");
    printf("  - Sign-magnitude: First bit indicates sign\n");
    printf("  - Two's complement: Most common in computers\n");
    printf("  - One's complement: Less common\n");
    
    return 0;
}