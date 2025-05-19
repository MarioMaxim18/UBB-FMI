// Parent process sends to the child a filename, and the child sends back to the parent 
// the content of the file or an error message if the file does not exist.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define BUFFER_SIZE 1024

void make_fifo_if_not_exists(char *fifo_name) {
    if(0 > mkfifo(fifo_name, 0600)) {
        perror("Error on create fifo");
        exit(1);
    }
}

int main() {
    make_fifo_if_not_exists(FIFO1);
    make_fifo_if_not_exists(FIFO2);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        char filename[BUFFER_SIZE];
        printf("Enter filename to send to child: ");
        fgets(filename, BUFFER_SIZE, stdin);
        filename[strcspn(filename, "\n")] = '\0';

        int fd1 = open(FIFO1, O_WRONLY);
        write(fd1, filename, strlen(filename) + 1);
        close(fd1);

        int fd2 = open(FIFO2, O_RDONLY);
        char buffer[BUFFER_SIZE];
        printf("\nReceived from child:\n");

        int bytesRead;
        while ((bytesRead = read(fd2, buffer, BUFFER_SIZE)) > 0) {
            write(STDOUT_FILENO, buffer, bytesRead);
        }
        close(fd2);
    } else {
        int fd1 = open(FIFO1, O_RDONLY);
        char filename[BUFFER_SIZE];
        read(fd1, filename, BUFFER_SIZE);
        close(fd1);

        int fd2 = open(FIFO2, O_WRONLY);

        FILE *file = fopen(filename, "r");
        if (!file) {
            snprintf(filename, BUFFER_SIZE, "Cannot open the file");
            write(fd2, filename, strlen(filename));
        } else {
            char buffer[BUFFER_SIZE];
            size_t n;
            while ((n = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
                write(fd2, buffer, n);
            }
            fclose(file);
        }
        close(fd2);
    }
    unlink(FIFO1);
    unlink(FIFO2);
    return 0;
}
