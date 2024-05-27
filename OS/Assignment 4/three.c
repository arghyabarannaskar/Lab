#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 100

// Function to check if a string is a palindrome
int is_palindrome(const char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0; // Not a palindrome
        }
    }
    return 1; // Palindrome
}

int main() {
    int parent_to_child[2]; // Pipe from parent to child
    int child_to_parent[2]; // Pipe from child to parent
    char buffer[BUFFER_SIZE];

    // Create pipes
    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(parent_to_child[1]); // Close write end of pipe from parent
        close(child_to_parent[0]); // Close read end of pipe to parent

        while (1) {
            // Read string from parent
            if (read(parent_to_child[0], buffer, BUFFER_SIZE) == -1) {
                perror("read failed");
                exit(EXIT_FAILURE);
            }

            // Check if the string is "quit"
            if (strcmp(buffer, "quit") == 0) {
                // Send "quit" to parent and exit
                if (write(child_to_parent[1], "quit", strlen("quit") + 1) == -1) {
                    perror("write failed");
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
            }

            // Check if the string is a palindrome
            if (is_palindrome(buffer)) {
                // Send "YES" to parent
                if (write(child_to_parent[1], "YES", strlen("YES") + 1) == -1) {
                    perror("write failed");
                    exit(EXIT_FAILURE);
                }
            } else {
                // Send "NO" to parent
                if (write(child_to_parent[1], "NO", strlen("NO") + 1) == -1) {
                    perror("write failed");
                    exit(EXIT_FAILURE);
                }
            }
        }
    } else {
        // Parent process
        close(parent_to_child[0]); // Close read end of pipe from parent
        close(child_to_parent[1]); // Close write end of pipe to parent

        while (1) {
            // Read string from user
            printf("Enter a string: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline

            // Send string to child
            if (write(parent_to_child[1], buffer, strlen(buffer) + 1) == -1) {
                perror("write failed");
                exit(EXIT_FAILURE);
            }

            // Wait for response from child
            if (read(child_to_parent[0], buffer, BUFFER_SIZE) == -1) {
                perror("read failed");
                exit(EXIT_FAILURE);
            }

            // Check if the response is "quit"
            if (strcmp(buffer, "quit") == 0) {
                break; // Exit loop if child sent "quit"
            }

            // Print result
            printf("Child response: %s\n", buffer);
        }
    }

    return 0;
}
