int second_largest_unique(const int arr[], int size) {
    if (size < 2) return -1;

    int largest = -2147483648;
    int second = -2147483648;
    int found_second = 0;

    for (int i = 0; i < size; i++) {
        int x = arr[i];

        if (x > largest) {
            if (x != largest) {
                second = largest;
                found_second = 1;
            }
            largest = x;
        } 
        else if (x < largest && x > second) {
            second = x;
            found_second = 1;
        }
    }

    if (!found_second)
        return -1;

    return second;
}