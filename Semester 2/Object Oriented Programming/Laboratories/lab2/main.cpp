#include <iostream>

void max_product(int *arr, int n) {
    if (n < 3) {
        printf("The array has less than 3 elements. Application will now stop.");
        return;
    }
    int max1 = arr[0], max2 = arr[1], max3 = arr[2];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (arr[i] * arr[j] * arr[k] > max1 * max2 * max3 && i != j && i != k && j != k) {
                    max1 = arr[i];
                    max2 = arr[j];
                    max3 = arr[k];
                }
            }
        }
    }
    int product = max1 * max2 * max3;
    printf("The maximum triplet is: %d, %d, %d", max1, max2, max3);
    printf(" with a product of %d", product);
}

int main() {
    int* arr = (int*) calloc (100, sizeof(int));
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", arr+i);
    }
    max_product(arr, n);
    return 0;
}