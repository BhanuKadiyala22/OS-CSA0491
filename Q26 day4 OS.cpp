#include <stdio.h>
#include <stdlib.h>

int main() {
    // File creation and writing
    FILE *file = fopen("example.txt", "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Hello, world!\n");
    fclose(file);

    // File reading
    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("Read from file: %s", buffer);
    }
    fclose(file);

    // File appending
    file = fopen("example.txt", "a");
    if (file == NULL) {
        perror("Error opening file for appending");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "This is an appended line.\n");
    fclose(file);

    // File reading after appending
    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf("\nAfter appending:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("Read from file: %s", buffer);
    }
    fclose(file);

    // File deletion
    if (remove("example.txt") == -1) {
        perror("Error deleting file");
        exit(EXIT_FAILURE);
    }

    printf("\nFile deleted successfully.\n");

    return 0;
}
