#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // File creation
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    
    // Writing to file
    char *data = "Hello, world!\n";
    if (write(fd, data, strlen(data)) == -1) {
        perror("Error writing to file");
        exit(EXIT_FAILURE);
    }

    // Closing file
    if (close(fd) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    // File opening
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Reading from file
    char buffer[1024];
    ssize_t bytesRead;
    if ((bytesRead = read(fd, buffer, sizeof(buffer))) == -1) {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    }

    // Displaying read data
    printf("Data read from file: %.*s", (int)bytesRead, buffer);

    // Closing file
    if (close(fd) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
