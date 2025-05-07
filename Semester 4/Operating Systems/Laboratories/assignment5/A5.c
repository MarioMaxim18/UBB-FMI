// Write a C Program that receives a command line argument a filename, and prints to standard output the content of this text file, 
// printing also an empty line after each line of text. Make no assumption regarding the maximum length of a line. 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        printf("%s", line);
        printf("\n");      
    }
    printf("\n");      
    fclose(file);
    return 0;
}