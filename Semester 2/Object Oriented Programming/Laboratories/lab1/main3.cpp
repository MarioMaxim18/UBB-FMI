#include <iostream>

int main() {
    int n;
    int count = 0;
    scanf("%d", &n);
    while (n!= 0) {
        if (n % 2 == 1) {
            count += 1;
        }
        n /= 2;
    }
    printf("%d", count);
    return 0;
}