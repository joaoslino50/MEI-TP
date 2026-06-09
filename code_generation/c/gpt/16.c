#include <stdlib.h>

int contains(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value)
            return 1;
    }
    return 0;
}

// Removes duplicates in-place.
// Returns new size of the array.
int remove_duplicates(int arr[], int size) {
    int *temp = (int *)malloc(size * sizeof(int));
    int new_size = 0;

    for (int i = 0; i < size; i++) {
        if (!contains(temp, new_size, arr[i])) {
            temp[new_size++] = arr[i];
        }
    }

    for (int i = 0; i < new_size; i++) {
        arr[i] = temp[i];
    }

    free(temp);
    return new_size;
}