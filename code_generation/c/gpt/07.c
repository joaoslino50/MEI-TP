#include <stdio.h>

int gcd(int a, int b) {
    // Ensure numbers are non-negative
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

int main() {
    int a = 48, b = 18;

    printf("GCD of %d and %d is %d\n", a, b, gcd(a, b));

    return 0;
}