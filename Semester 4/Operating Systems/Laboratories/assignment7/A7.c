// Implement the following structure of processes, in which the vertices indicate the communication between processes using pipes:
// Process 1: read from stdin lines of at most 30 chars and write alternatively one line to each processes 2 and 3 
// Process 2: replace digits with 9 and write result to process 4 
// Process 3: replace letters with G and write result to process 4 
// Process 4: print sorted what it receives
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 31
#define MAX_LINES 100

void replace_digits_with_9(char *line) {
    for (int i = 0; line[i]; i++)
        if (isdigit(line[i]))
            line[i] = '9';
}

void replace_letters_with_G(char *line) {
    for (int i = 0; line[i]; i++)
        if (isalpha(line[i]))
            line[i] = 'G';
}

int main() {
    int p1to2[2], p1to3[2]; 
    int p2to4[2], p3to4[2];

    pipe(p1to2);
    pipe(p1to3);
    pipe(p2to4);
    pipe(p3to4);

    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(p1to2[1]);
        close(p1to3[0]); close(p1to3[1]);
        close(p2to4[0]); 
        close(p3to4[0]); close(p3to4[1]);

        char line[MAX_LINE];
        while (read(p1to2[0], line, MAX_LINE) > 0) {
            replace_digits_with_9(line);
            write(p2to4[1], line, MAX_LINE);
        }
        exit(0);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        close(p1to3[1]); 
        close(p1to2[0]); close(p1to2[1]);
        close(p3to4[0]); 
        close(p2to4[0]); close(p2to4[1]);

        char line[MAX_LINE];
        while (read(p1to3[0], line, MAX_LINE) > 0) {
            replace_letters_with_G(line);
            write(p3to4[1], line, MAX_LINE);
        }
        exit(0);
    }

    pid_t pid4 = fork();
    if (pid4 == 0) {
        close(p1to2[0]); close(p1to2[1]);
        close(p1to3[0]); close(p1to3[1]);
        close(p2to4[1]); 
        close(p3to4[1]);

        char lines[MAX_LINES][MAX_LINE];
        int count = 0;

        char buffer[MAX_LINE];
        while (read(p2to4[0], buffer, MAX_LINE) > 0 && count < MAX_LINES) {
            strcpy(lines[count++], buffer);
        }
        while (read(p3to4[0], buffer, MAX_LINE) > 0 && count < MAX_LINES) {
            strcpy(lines[count++], buffer);
        }

        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                if (strcmp(lines[i], lines[j]) > 0) {
                    char temp[MAX_LINE];
                    strcpy(temp, lines[i]);
                    strcpy(lines[i], lines[j]);
                    strcpy(lines[j], temp);
                }
            }
        }
        for (int i = 0; i < count; i++) {
            printf("%s", lines[i]);
        }
        exit(0);
    }

    close(p1to2[0]); 
    close(p1to3[0]);
    close(p2to4[0]); close(p2to4[1]);
    close(p3to4[0]); close(p3to4[1]);

    char line[MAX_LINE];
    int toggle = 0;
    while (fgets(line, MAX_LINE, stdin)) {
        if (toggle == 0)
            write(p1to2[1], line, MAX_LINE);
        else
            write(p1to3[1], line, MAX_LINE);
        toggle = 1 - toggle;
    }

    close(p1to2[1]);
    close(p1to3[1]);

    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}