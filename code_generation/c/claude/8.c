#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Basic prime checking function (naive approach)
bool isPrimeBasic(int n) {
    // Edge cases
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    // Check odd divisors up to n-1
    for (int i = 3; i < n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Optimized prime checking (check up to sqrt(n))
bool isPrimeOptimized(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    int limit = (int)sqrt(n);
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Miller-Rabin primality test (probabilistic, for large numbers)
// Deterministic for 32-bit integers with these bases
bool isPrimeMillerRabin(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    
    // Write n-1 as d * 2^s
    int d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    
    // Test these bases for deterministic result in 32-bit range
    int bases[] = {2, 7, 61};
    int numBases = 3;
    
    for (int i = 0; i < numBases; i++) {
        int a = bases[i];
        if (a >= n) continue;
        
        // Compute a^d mod n
        int x = 1;
        int base = a % n;
        int exp = d;
        while (exp > 0) {
            if (exp & 1) {
                x = (x * base) % n;
            }
            base = (base * base) % n;
            exp >>= 1;
        }
        
        if (x == 1 || x == n - 1) continue;
        
        bool composite = true;
        for (int r = 0; r < s - 1; r++) {
            x = (x * x) % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        
        if (composite) return false;
    }
    
    return true;
}

// Sieve of Eratosthenes - generate all primes up to limit
void sieveOfEratosthenes(int limit) {
    if (limit < 2) return;
    
    bool *isPrime = (bool*)malloc((limit + 1) * sizeof(bool));
    if (isPrime == NULL) return;
    
    // Initialize all as true
    for (int i = 0; i <= limit; i++) {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false;
    
    // Sieve
    for (int p = 2; p * p <= limit; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= limit; i += p) {
                isPrime[i] = false;
            }
        }
    }
    
    // Print primes
    printf("Primes up to %d: ", limit);
    int count = 0;
    for (int i = 2; i <= limit; i++) {
        if (isPrime[i]) {
            printf("%d ", i);
            count++;
        }
    }
    printf("\nTotal: %d primes\n", count);
    
    free(isPrime);
}

// Function to find all prime factors of a number
void primeFactors(int n) {
    printf("Prime factors of %d: ", n);
    
    // Handle factor 2
    while (n % 2 == 0) {
        printf("%d ", 2);
        n /= 2;
    }
    
    // Handle odd factors
    for (int i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            printf("%d ", i);
            n /= i;
        }
    }
    
    // If n is still > 1, it's prime
    if (n > 1) {
        printf("%d", n);
    }
    printf("\n");
}

// Get next prime number greater than n
int nextPrime(int n) {
    if (n < 2) return 2;
    
    int candidate = n + 1;
    if (candidate % 2 == 0) candidate++;
    
    while (!isPrimeOptimized(candidate)) {
        candidate += 2;
    }
    return candidate;
}

// Count primes up to n using optimized method
int countPrimes(int n) {
    if (n < 2) return 0;
    
    bool *isPrime = (bool*)malloc((n + 1) * sizeof(bool));
    if (isPrime == NULL) return 0;
    
    for (int i = 0; i <= n; i++) {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false;
    
    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            count++;
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    free(isPrime);
    return count;
}

// Function to demonstrate detailed primality test
void testPrimality(int n) {
    printf("\nTesting %d:\n", n);
    printf("  Basic: %s\n", isPrimeBasic(n) ? "Prime" : "Composite");
    printf("  Optimized: %s\n", isPrimeOptimized(n) ? "Prime" : "Composite");
    printf("  Miller-Rabin: %s\n", isPrimeMillerRabin(n) ? "Prime" : "Composite");
    
    if (!isPrimeOptimized(n) && n > 1) {
        printf("  First divisor: ");
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                printf("%d\n", i);
                break;
            }
        }
    }
}

// Function to find twin primes up to limit
void findTwinPrimes(int limit) {
    printf("Twin primes up to %d:\n", limit);
    int prevPrime = 2;
    int count = 0;
    
    for (int i = 3; i <= limit; i++) {
        if (isPrimeOptimized(i)) {
            if (i - prevPrime == 2) {
                printf("(%d, %d) ", prevPrime, i);
                count++;
            }
            prevPrime = i;
        }
    }
    if (count == 0) {
        printf("None found");
    }
    printf("\nTotal: %d twin prime pairs\n", count);
}

int main() {
    printf("Prime Number Functions in C\n");
    printf("==========================\n");
    
    // Test individual numbers
    int testNumbers[] = {1, 2, 3, 4, 5, 16, 17, 19, 97, 100, 997, 1009};
    int numTests = sizeof(testNumbers) / sizeof(testNumbers[0]);
    
    printf("\nTesting individual numbers:\n");
    printf("Number | Basic | Optimized | Miller-Rabin\n");
    printf("-------|-------|-----------|-------------\n");
    for (int i = 0; i < numTests; i++) {
        int n = testNumbers[i];
        printf("%6d | %5s | %9s | %11s\n", 
               n,
               isPrimeBasic(n) ? "Yes" : "No",
               isPrimeOptimized(n) ? "Yes" : "No",
               isPrimeMillerRabin(n) ? "Yes" : "No");
    }
    
    // Detailed analysis of specific numbers
    testPrimality(9973);
    testPrimality(10000);
    testPrimality(104729); // 10000th prime
    
    // Prime factorization
    printf("\n");
    primeFactors(84);
    primeFactors(97);
    primeFactors(1001);
    primeFactors(999983); // Large prime
    
    // Sieve demonstration
    printf("\n");
    sieveOfEratosthenes(100);
    
    // Count primes
    printf("\nPrime counting:\n");
    printf("Primes up to 10: %d\n", countPrimes(10));
    printf("Primes up to 100: %d\n", countPrimes(100));
    printf("Primes up to 1000: %d\n", countPrimes(1000));
    
    // Twin primes
    printf("\n");
    findTwinPrimes(100);
    
    // Next prime function
    printf("\nNext prime after various numbers:\n");
    int numbers[] = {1, 10, 20, 30, 40, 50, 99, 100};
    for (int i = 0; i < 8; i++) {
        printf("Next prime after %d is %d\n", numbers[i], nextPrime(numbers[i]));
    }
    
    // Performance comparison
    printf("\nPerformance Comparison (100,000 iterations):\n");
    
    int testPrime = 999983; // A large prime
    clock_t start, end;
    double cpu_time;
    
    start = clock();
    for (int i = 0; i < 100000; i++) {
        isPrimeBasic(testPrime);
    }
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Basic method: %.4f seconds\n", cpu_time);
    
    start = clock();
    for (int i = 0; i < 100000; i++) {
        isPrimeOptimized(testPrime);
    }
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Optimized method: %.4f seconds\n", cpu_time);
    
    start = clock();
    for (int i = 0; i < 100000; i++) {
        isPrimeMillerRabin(testPrime);
    }
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Miller-Rabin: %.4f seconds\n", cpu_time);
    
    // Interactive prime checker
    printf("\nInteractive Prime Checker\n");
    printf("Enter a number to check (or 0 to exit):\n");
    
    int n;
    while (1) {
        printf("\n> ");
        scanf("%d", &n);
        
        if (n == 0) break;
        
        if (n < 0) {
            printf("Please enter a positive integer.\n");
            continue;
        }
        
        if (isPrimeOptimized(n)) {
            printf("%d is a prime number!\n", n);
        } else {
            printf("%d is composite.\n", n);
            printf("Divisible by: ");
            int firstDivisor = 2;
            if (n % 2 == 0) {
                firstDivisor = 2;
            } else {
                for (int i = 3; i <= sqrt(n); i += 2) {
                    if (n % i == 0) {
                        firstDivisor = i;
                        break;
                    }
                }
            }
            printf("%d\n", firstDivisor);
        }
    }
    
    return 0;
}