#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

double calculateMean(int arr[], int n) {
    if (n == 0) return 0.0;
    
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (double)sum / n;
}

double calculateMedian(int arr[], int n) {
    if (n == 0) return 0.0;
    
    int *sorted = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    
    qsort(sorted, n, sizeof(int), compare);
    
    double median;
    if (n % 2 == 0) {
        median = (sorted[n/2 - 1] + sorted[n/2]) / 2.0;
    } else {
        median = sorted[n/2];
    }
    
    free(sorted);
    return median;
}

void calculateMeanAndMedian(int arr[], int n, double *mean, double *median) {
    *mean = calculateMean(arr, n);
    *median = calculateMedian(arr, n);
}