#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

// Basic approach: Single pass to find both min and max
void findMinMaxBasic(int arr[], int n, int *min, int *max) {
    if (n <= 0) {
        *min = *max = 0;
        return;
    }
    
    *min = *max = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) {
            *min = arr[i];
        }
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}

// Optimized approach: Compare in pairs (3 comparisons per 2 elements)
void findMinMaxOptimized(int arr[], int n, int *min, int *max) {
    if (n <= 0) {
        *min = *max = 0;
        return;
    }
    
    int i;
    
    // Initialize min and max based on first element(s)
    if (n % 2 == 0) {
        // If even number of elements, compare first two
        if (arr[0] < arr[1]) {
            *min = arr[0];
            *max = arr[1];
        } else {
            *min = arr[1];
            *max = arr[0];
        }
        i = 2;
    } else {
        // If odd number, start with first element
        *min = *max = arr[0];
        i = 1;
    }
    
    // Process rest of the elements in pairs
    while (i < n - 1) {
        if (arr[i] < arr[i + 1]) {
            if (arr[i] < *min) *min = arr[i];
            if (arr[i + 1] > *max) *max = arr[i + 1];
        } else {
            if (arr[i + 1] < *min) *min = arr[i + 1];
            if (arr[i] > *max) *max = arr[i];
        }
        i += 2;
    }
}

// Return min and max using a structure
typedef struct {
    int min;
    int max;
} MinMax;

MinMax findMinMaxStruct(int arr[], int n) {
    MinMax result;
    
    if (n <= 0) {
        result.min = result.max = 0;
        return result;
    }
    
    result.min = result.max = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < result.min) result.min = arr[i];
        if (arr[i] > result.max) result.max = arr[i];
    }
    
    return result;
}

// Recursive divide and conquer approach
void findMinMaxRecursive(int arr[], int left, int right, int *min, int *max) {
    // Base case: single element
    if (left == right) {
        *min = *max = arr[left];
        return;
    }
    
    // Base case: two elements
    if (right == left + 1) {
        if (arr[left] < arr[right]) {
            *min = arr[left];
            *max = arr[right];
        } else {
            *min = arr[right];
            *max = arr[left];
        }
        return;
    }
    
    // Recursive case: divide and conquer
    int mid = left + (right - left) / 2;
    int min1, max1, min2, max2;
    
    findMinMaxRecursive(arr, left, mid, &min1, &max1);
    findMinMaxRecursive(arr, mid + 1, right, &min2, &max2);
    
    *min = (min1 < min2) ? min1 : min2;
    *max = (max1 > max2) ? max1 : max2;
}

// Wrapper for recursive function
void findMinMaxRecursiveWrapper(int arr[], int n, int *min, int *max) {
    if (n <= 0) {
        *min = *max = 0;
        return;
    }
    findMinMaxRecursive(arr, 0, n - 1, min, max);
}

// Function to find min, max, and their positions
void findMinMaxWithPositions(int arr[], int n, 
                             int *min, int *minPos, 
                             int *max, int *maxPos) {
    if (n <= 0) return;
    
    *min = *max = arr[0];
    *minPos = *maxPos = 0;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) {
            *min = arr[i];
            *minPos = i;
        }
        if (arr[i] > *max) {
            *max = arr[i];
            *maxPos = i;
        }
    }
}

// Find second largest and second smallest
void findSecondMinMax(int arr[], int n, 
                      int *secondMin, int *secondMax) {
    if (n < 2) {
        *secondMin = *secondMax = INT_MIN;
        return;
    }
    
    int min = INT_MAX, second_min = INT_MAX;
    int max = INT_MIN, second_max = INT_MIN;
    
    for (int i = 0; i < n; i++) {
        // For minimums
        if (arr[i] < min) {
            second_min = min;
            min = arr[i];
        } else if (arr[i] < second_min && arr[i] != min) {
            second_min = arr[i];
        }
        
        // For maximums
        if (arr[i] > max) {
            second_max = max;
            max = arr[i];
        } else if (arr[i] > second_max && arr[i] != max) {
            second_max = arr[i];
        }
    }
    
    *secondMin = (second_min == INT_MAX) ? INT_MIN : second_min;
    *secondMax = (second_max == INT_MIN) ? INT_MAX : second_max;
}

// Function to demonstrate with detailed output
void demonstrateMinMax(int arr[], int n, const char* title) {
    printf("\n%s:\n", title);
    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    int min, max;
    
    // Method 1: Basic
    findMinMaxBasic(arr, n, &min, &max);
    printf("Basic method - Min: %d, Max: %d\n", min, max);
    
    // Method 2: Optimized
    findMinMaxOptimized(arr, n, &min, &max);
    printf("Optimized method - Min: %d, Max: %d\n", min, max);
    
    // Method 3: Structure
    MinMax result = findMinMaxStruct(arr, n);
    printf("Structure method - Min: %d, Max: %d\n", result.min, result.max);
    
    // Method 4: Recursive
    findMinMaxRecursiveWrapper(arr, n, &min, &max);
    printf("Recursive method - Min: %d, Max: %d\n", min, max);
}

// Find min and max using macros (alternative approach)
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

void findMinMaxMacro(int arr[], int n, int *min, int *max) {
    if (n <= 0) return;
    
    *min = *max = arr[0];
    for (int i = 1; i < n; i++) {
        *min = MIN(*min, arr[i]);
        *max = MAX(*max, arr[i]);
    }
}

// Function to handle empty arrays safely
bool findMinMaxSafe(int arr[], int n, int *min, int *max) {
    if (arr == NULL || n <= 0) {
        return false;
    }
    
    *min = *max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
    return true;
}

int main() {
    printf("FIND MINIMUM AND MAXIMUM IN ARRAY\n");
    printf("=================================\n");
    
    // Test case 1: Normal array
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    demonstrateMinMax(arr1, n1, "Test Case 1 - Normal Array");
    
    // Test case 2: Array with negative numbers
    int arr2[] = {-5, -10, -3, -8, -1, -7};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    demonstrateMinMax(arr2, n2, "Test Case 2 - Negative Numbers");
    
    // Test case 3: Single element
    int arr3[] = {42};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    demonstrateMinMax(arr3, n3, "Test Case 3 - Single Element");
    
    // Test case 4: Two elements
    int arr4[] = {100, 50};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    demonstrateMinMax(arr4, n4, "Test Case 4 - Two Elements");
    
    // Test case 5: All elements same
    int arr5[] = {7, 7, 7, 7, 7};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    demonstrateMinMax(arr5, n5, "Test Case 5 - All Elements Same");
    
    // Test case 6: Sorted array
    int arr6[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n6 = sizeof(arr6) / sizeof(arr6[0]);
    demonstrateMinMax(arr6, n6, "Test Case 6 - Sorted Array");
    
    // Test case 7: Reverse sorted array
    int arr7[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n7 = sizeof(arr7) / sizeof(arr7[0]);
    demonstrateMinMax(arr7, n7, "Test Case 7 - Reverse Sorted");
    
    // Find min, max with positions
    printf("\n=== MIN/MAX WITH POSITIONS ===\n");
    int arr8[] = {34, 12, 56, 78, 23, 89, 5, 67};
    int n8 = sizeof(arr8) / sizeof(arr8[0]);
    
    int min, max, minPos, maxPos;
    findMinMaxWithPositions(arr8, n8, &min, &minPos, &max, &maxPos);
    
    printf("Array: ");
    for (int i = 0; i < n8; i++) {
        printf("%d ", arr8[i]);
    }
    printf("\n");
    printf("Minimum: %d at index %d\n", min, minPos);
    printf("Maximum: %d at index %d\n", max, maxPos);
    
    // Second min and max
    printf("\n=== SECOND MINIMUM AND MAXIMUM ===\n");
    int arr9[] = {10, 5, 20, 15, 8, 25, 3, 18};
    int n9 = sizeof(arr9) / sizeof(arr9[0]);
    
    int secondMin, secondMax;
    findSecondMinMax(arr9, n9, &secondMin, &secondMax);
    
    printf("Array: ");
    for (int i = 0; i < n9; i++) {
        printf("%d ", arr9[i]);
    }
    printf("\n");
    printf("Second Minimum: %d\n", secondMin);
    printf("Second Maximum: %d\n", secondMax);
    
    // Performance comparison
    printf("\n=== PERFORMANCE COMPARISON ===\n");
    int largeArr[10000];
    for (int i = 0; i < 10000; i++) {
        largeArr[i] = rand() % 10000;
    }
    
    clock_t start, end;
    double time_basic, time_optimized, time_recursive;
    int min_result, max_result;
    
    // Basic method
    start = clock();
    for (int i = 0; i < 1000; i++) {
        findMinMaxBasic(largeArr, 10000, &min_result, &max_result);
    }
    end = clock();
    time_basic = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // Optimized method
    start = clock();
    for (int i = 0; i < 1000; i++) {
        findMinMaxOptimized(largeArr, 10000, &min_result, &max_result);
    }
    end = clock();
    time_optimized = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // Recursive method
    start = clock();
    for (int i = 0; i < 1000; i++) {
        findMinMaxRecursiveWrapper(largeArr, 10000, &min_result, &max_result);
    }
    end = clock();
    time_recursive = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("1000 iterations on array of 10,000 elements:\n");
    printf("  Basic method: %.4f seconds\n", time_basic);
    printf("  Optimized method: %.4f seconds\n", time_optimized);
    printf("  Recursive method: %.4f seconds\n", time_recursive);
    
    // Comparison of number of comparisons
    printf("\n=== NUMBER OF COMPARISONS ===\n");
    printf("For n elements:\n");
    printf("  Basic method: 2n - 2 comparisons\n");
    printf("  Optimized method: 3n/2 - 2 comparisons (25%% fewer)\n");
    printf("  Recursive method: 3n/2 - 2 comparisons\n");
    
    printf("\nExample with n = 8:\n");
    printf("  Basic: 14 comparisons\n");
    printf("  Optimized: 10 comparisons\n");
    
    // Edge case demonstration
    printf("\n=== SAFE FUNCTION DEMONSTRATION ===\n");
    int *nullArr = NULL;
    int safeMin, safeMax;
    
    if (findMinMaxSafe(nullArr, 5, &safeMin, &safeMax)) {
        printf("Min: %d, Max: %d\n", safeMin, safeMax);
    } else {
        printf("Invalid array: NULL or empty\n");
    }
    
    int emptyArr[] = {};
    if (findMinMaxSafe(emptyArr, 0, &safeMin, &safeMax)) {
        printf("Min: %d, Max: %d\n", safeMin, safeMax);
    } else {
        printf("Invalid array: NULL or empty\n");
    }
    
    // Summary
    printf("\n=== IMPLEMENTATION SUMMARY ===\n");
    printf("Time Complexity: O(n)\n");
    printf("Space Complexity: \n");
    printf("  - Iterative methods: O(1)\n");
    printf("  - Recursive method: O(log n) due to recursion stack\n");
    printf("\nKey Points:\n");
    printf("  - Single pass is sufficient (no need to sort)\n");
    printf("  - Optimized method reduces comparisons by 25%%\n");
    printf("  - Always handle edge cases (empty, single element)\n");
    printf("  - Use pointers or structures to return multiple values\n");
    printf("  - Consider integer overflow for very large arrays\n");
    
    return 0;
}