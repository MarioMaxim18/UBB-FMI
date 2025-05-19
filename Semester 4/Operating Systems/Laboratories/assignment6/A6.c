// Calculate the product of an array n of numbers using divide et impera method: 
// a process splits the array in two sub-arrays and gives them to two other chid processes to compute their product, 
// then multiplies the results obtained from the two. The two child processes apply the same technique (split, etc…).
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int product(int *arr, int left, int right) {
    if (left == right) return arr[left];

    int mid = (left + right) / 2;

    int pipefd1[2], pipefd2[2];
    pipe(pipefd1);
    pipe(pipefd2);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        int left_result = product(arr, left, mid);
        close(pipefd1[0]); 
        write(pipefd1[1], &left_result, sizeof(int));
        close(pipefd1[1]);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        int right_result = product(arr, mid + 1, right);
        close(pipefd2[0]); 
        write(pipefd2[1], &right_result, sizeof(int));
        close(pipefd2[1]);
        exit(0);
    }

    int left_result, right_result;
    close(pipefd1[1]); 
    close(pipefd2[1]);

    read(pipefd1[0], &left_result, sizeof(int));
    read(pipefd2[0], &right_result, sizeof(int));

    close(pipefd1[0]);
    close(pipefd2[0]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return left_result * right_result;
}

int main() {
    int arr[] = {2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = product(arr, 0, n - 1);
    printf("Product: %d\n", result);

    return 0;
}