#include <stdio.h>
#include <stdbool.h>

// Iterative Binary Search
// Returns index if found, -1 if not found
int binarySearchIterative(int arr[], int left, int right, int target) {
    while (left <= right) {
        // Calculate mid index to avoid overflow
        int mid = left + (right - left) / 2;
        
        // Check if target is present at mid
        if (arr[mid] == target) {
            return mid;
        }
        
        // If target is greater, ignore left half
        if (arr[mid] < target) {
            left = mid + 1;
        }
        // If target is smaller, ignore right half
        else {
            right = mid - 1;
        }
    }
    
    // Target not found
    return -1;
}

// Recursive Binary Search
int binarySearchRecursive(int arr[], int left, int right, int target) {
    // Base case: element not found
    if (left > right) {
        return -1;
    }
    
    // Calculate mid index
    int mid = left + (right - left) / 2;
    
    // Base case: element found
    if (arr[mid] == target) {
        return mid;
    }
    
    // Recursive cases
    if (arr[mid] < target) {
        // Search in right half
        return binarySearchRecursive(arr, mid + 1, right, target);
    } else {
        // Search in left half
        return binarySearchRecursive(arr, left, mid - 1, target);
    }
}

// Enhanced binary search that returns first occurrence (for duplicate elements)
int binarySearchFirstOccurrence(int arr[], int left, int right, int target) {
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            // Continue searching in left half for earlier occurrence
            right = mid - 1;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Enhanced binary search that returns last occurrence (for duplicate elements)
int binarySearchLastOccurrence(int arr[], int left, int right, int target) {
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            // Continue searching in right half for later occurrence
            left = mid + 1;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Function to demonstrate binary search with detailed output
void demonstrateBinarySearch(int arr[], int size, int target) {
    printf("\n--- Searching for %d ---\n", target);
    
    // Iterative binary search
    int result_iter = binarySearchIterative(arr, 0, size - 1, target);
    if (result_iter != -1) {
        printf("Iterative: Found at index %d\n", result_iter);
    } else {
        printf("Iterative: Element not found\n");
    }
    
    // Recursive binary search
    int result_recur = binarySearchRecursive(arr, 0, size - 1, target);
    if (result_recur != -1) {
        printf("Recursive: Found at index %d\n", result_recur);
    } else {
        printf("Recursive: Element not found\n");
    }
}

// Utility function to print array
void printArray(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    // Test case 1: Sorted array with distinct elements
    int arr1[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    
    printf("Test Case 1 - Sorted Array (Distinct Elements):\n");
    printf("Array: ");
    printArray(arr1, size1);
    
    // Search for various elements
    demonstrateBinarySearch(arr1, size1, 23);  // Element exists in middle
    demonstrateBinarySearch(arr1, size1, 2);   // Element at beginning
    demonstrateBinarySearch(arr1, size1, 78);  // Element at end
    demonstrateBinarySearch(arr1, size1, 100); // Element not found
    
    // Test case 2: Array with duplicate elements
    int arr2[] = {1, 3, 5, 5, 5, 7, 9, 11, 11, 13};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    printf("\n\nTest Case 2 - Sorted Array (With Duplicates):\n");
    printf("Array: ");
    printArray(arr2, size2);
    
    int target = 5;
    printf("\n--- Searching for %d ---\n", target);
    
    int first = binarySearchFirstOccurrence(arr2, 0, size2 - 1, target);
    int last = binarySearchLastOccurrence(arr2, 0, size2 - 1, target);
    
    if (first != -1) {
        printf("First occurrence at index: %d\n", first);
        printf("Last occurrence at index: %d\n", last);
        printf("Count of %d: %d\n", target, last - first + 1);
    } else {
        printf("Element not found\n");
    }
    
    // Test case 3: Single element array
    int arr3[] = {42};
    int size3 = 1;
    
    printf("\n\nTest Case 3 - Single Element Array:\n");
    printf("Array: ");
    printArray(arr3, size3);
    demonstrateBinarySearch(arr3, size3, 42);
    demonstrateBinarySearch(arr3, size3, 99);
    
    // Test case 4: Large search demonstration
    int arr4[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    
    printf("\n\nTest Case 4 - Search Steps Demonstration:\n");
    printf("Array: ");
    printArray(arr4, size4);
    
    int target2 = 70;
    printf("\nSearching for %d (Iterative with step-by-step):\n", target2);
    
    int left = 0, right = size4 - 1;
    int step = 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        printf("Step %d: left=%d, right=%d, mid=%d, arr[mid]=%d\n", 
               step++, left, right, mid, arr4[mid]);
        
        if (arr4[mid] == target2) {
            printf("Found %d at index %d!\n", target2, mid);
            break;
        }
        else if (arr4[mid] < target2) {
            printf("%d > arr[mid]=%d, searching right half\n", target2, arr4[mid]);
            left = mid + 1;
        }
        else {
            printf("%d < arr[mid]=%d, searching left half\n", target2, arr4[mid]);
            right = mid - 1;
        }
    }
    
    // Performance comparison
    printf("\n\nPerformance Note:\n");
    printf("Binary search has O(log n) time complexity.\n");
    printf("For an array of size %d, maximum steps needed = ceil(log2(%d)) = %d\n", 
           size4, size4, (int)(sizeof(arr4)/sizeof(arr4[0])));
    
    return 0;
}