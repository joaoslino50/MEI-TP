#include <stdio.h>
#include <stdlib.h>

void fibonacci(int n, long long *arr) {
    if (n <= 0) return;

    arr[0] = 0;
    if (n == 1) return;

    arr[1] = 1;

    for (int i = 2; i < n; i++) {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
}

int main() {
    int n = 10;

    long long *arr = (long long *)malloc(n * sizeof(long long));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    fibonacci(n, arr);

    for (int i = 0; i < n; i++) {
        printf("%lld ", arr[i]);
    }

    printf("\n");

    free(arr);
    return 0;
}
