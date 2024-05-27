#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h> // pid_t is defined here

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main() {
    char write_msg[BUFFER_SIZE] = "Hello, Child!";
    char read_msg[BUFFER_SIZE];
    int fd[2]; // File descriptors for the pipe
    pid_t pid;

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    pid = fork();

    if (pid < 0) { // Error occurred
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Parent process
        // Close the unused read end of the pipe
        close(fd[READ_END]);

        // Write to the pipe
        if (write(fd[WRITE_END], write_msg, strlen(write_msg) + 1) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Close the write end of the pipe
        close(fd[WRITE_END]);
    } else { // Child process
        // Close the unused write end of the pipe
        close(fd[WRITE_END]);

        // Read from the pipe
        if (read(fd[READ_END], read_msg, BUFFER_SIZE) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        printf("Child read: %s\n", read_msg);

        // Close the read end of the pipe
        close(fd[READ_END]);
    }

    return 0;
}
