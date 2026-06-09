#include <stdio.h>
#include <stdbool.h>

// Function to perform bubble sort
void bubbleSort(int arr[], int n) {
    bool swapped;
    
    // Outer loop for number of passes
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        
        // Inner loop for comparisons in each pass
        // n-i-1 because the last i elements are already sorted
        for (int j = 0; j < n - i - 1; j++) {
            // Compare adjacent elements
            if (arr[j] > arr[j + 1]) {
                // Swap if they are in wrong order
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        
        // If no swaps occurred, array is already sorted
        if (!swapped) {
            break;
        }
    }
}

// Optimized version with detailed output
void bubbleSortDetailed(int arr[], int n) {
    bool swapped;
    int passCount = 0;
    
    printf("Starting Bubble Sort...\n\n");
    
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        passCount++;
        
        printf("Pass %d:\n", passCount);
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
                
                printf("  Swapped arr[%d]=%d with arr[%d]=%d\n", 
                       j, arr[j + 1], j + 1, arr[j]);
            }
        }
        
        // Print array after each pass
        printf("  Array after pass %d: ", passCount);
        printArray(arr, n);
        printf("\n");
        
        if (!swapped) {
            printf("Array is already sorted! Stopping early.\n");
            break;
        }
    }
}

// Utility function to print array
void printArray(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]");
}

// Function to swap two integers (alternative using pointers)
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble sort using pointer swap function
void bubbleSortWithPointerSwap(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main() {
    // Test case 1: Unsorted array
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    printf("Test Case 1 - Unsorted Array:\n");
    printf("Original array: ");
    printArray(arr1, n1);
    printf("\n");
    
    bubbleSort(arr1, n1);
    
    printf("Sorted array: ");
    printArray(arr1, n1);
    printf("\n\n");
    
    // Test case 2: Already sorted array (to show optimization)
    int arr2[] = {1, 2, 3, 4, 5, 6, 7};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    printf("Test Case 2 - Already Sorted Array:\n");
    printf("Original array: ");
    printArray(arr2, n2);
    printf("\n");
    
    bubbleSort(arr2, n2);
    
    printf("Sorted array: ");
    printArray(arr2, n2);
    printf("\n\n");
    
    // Test case 3: Array with duplicate elements
    int arr3[] = {5, 2, 8, 2, 9, 1, 5, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    
    printf("Test Case 3 - Array with Duplicates:\n");
    printf("Original array: ");
    printArray(arr3, n3);
    printf("\n");
    
    bubbleSort(arr3, n3);
    
    printf("Sorted array: ");
    printArray(arr3, n3);
    printf("\n\n");
    
    // Detailed walkthrough with a small array
    int arr4[] = {64, 34, 25, 12};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    
    printf("Test Case 4 - Detailed Walkthrough:\n");
    bubbleSortDetailed(arr4, n4);
    
    return 0;
}