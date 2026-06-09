#include <stdio.h>
#include <limits.h>

int secondLargestUnique(int arr[], int n) {
    if (n < 2) return -1;
    
    int first = INT_MIN;
    int second = INT_MIN;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > first) {
            second = first;
            first = arr[i];
        }
        else if (arr[i] > second && arr[i] != first) {
            second = arr[i];
        }
    }
    
    return (second == INT_MIN) ? -1 : second;
}

int secondLargestUniqueWithSort(int arr[], int n) {
    if (n < 2) return -1;
    
    // Simple bubble sort for demonstration
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    int largest = arr[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] != largest) {
            return arr[i];
        }
    }
    
    return -1;
}