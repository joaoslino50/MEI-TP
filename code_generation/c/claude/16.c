#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;
    
    int *seen = (int*)calloc(1000, sizeof(int));
    int uniqueCount = 0;
    
    for (int i = 0; i < n; i++) {
        if (!seen[arr[i]]) {
            seen[arr[i]] = 1;
            arr[uniqueCount++] = arr[i];
        }
    }
    
    free(seen);
    return uniqueCount;
}

int removeDuplicatesWithFlag(int arr[], int n) {
    if (n == 0) return 0;
    
    int uniqueCount = 0;
    
    for (int i = 0; i < n; i++) {
        bool isDuplicate = false;
        
        for (int j = 0; j < uniqueCount; j++) {
            if (arr[i] == arr[j]) {
                isDuplicate = true;
                break;
            }
        }
        
        if (!isDuplicate) {
            arr[uniqueCount++] = arr[i];
        }
    }
    
    return uniqueCount;
}

int removeDuplicatesSorted(int arr[], int n) {
    if (n == 0) return 0;
    
    int uniqueCount = 1;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[uniqueCount - 1]) {
            arr[uniqueCount++] = arr[i];
        }
    }
    
    return uniqueCount;
}