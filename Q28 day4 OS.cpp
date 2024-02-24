#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    // Check if the required arguments are provided
    if (argc < 3) {
        fprintf(stderr, "Usage: %s search_string file_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open the file
    FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read the file line by line and search for the specified string
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, argv[1]) != NULL) {
            printf("%s", line);
        }
    }

    // Close the file
    fclose(file);

    return EXIT_SUCCESS;
}
