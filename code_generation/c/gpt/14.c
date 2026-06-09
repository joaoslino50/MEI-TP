void decimal_to_binary(unsigned int n, char *binary) {
    int i = 0;

    if (n == 0) {
        binary[0] = '0';
        binary[1] = '\0';
        return;
    }

    while (n > 0) {
        binary[i++] = (n % 2) + '0';
        n /= 2;
    }

    binary[i] = '\0';

    for (int left = 0, right = i - 1; left < right; left++, right--) {
        char temp = binary[left];
        binary[left] = binary[right];
        binary[right] = temp;
    }
}