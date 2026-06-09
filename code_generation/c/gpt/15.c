#include <stdlib.h>

static int compare(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

void mean_and_median(const int arr[], int size, double *mean, double *median) {
    long long sum = 0;

    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    *mean = (double)sum / size;

    int *temp = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }

    qsort(temp, size, sizeof(int), compare);

    if (size % 2 == 0) {
        *median = (temp[size / 2 - 1] + temp[size / 2]) / 2.0;
    } else {
        *median = temp[size / 2];
    }

    free(temp);
}