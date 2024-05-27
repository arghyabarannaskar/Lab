#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LEN 50

int main() {
    int choice;
    char command[MAX_COMMAND_LEN];
    char *args[2];

    while (1) {
        // Print menu
        printf("1. ls\n");
        printf("2. pwd\n");
        printf("3. uname\n");
        printf("4. exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Flush stdin to clear any remaining characters
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                strcpy(command, "/bin/ls");
                args[0] = command;
                args[1] = NULL;
                break;
            case 2:
                strcpy(command, "/bin/pwd");
                args[0] = command;
                args[1] = NULL;
                break;
            case 3:
                strcpy(command, "/bin/uname");
                args[0] = command;
                args[1] = NULL;
                break;
            case 4:
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                continue;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Child process
            execv(args[0], args);
            // If execv returns, an error occurred
            perror("execv failed");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL); // Wait for the child to finish
        }
    }

    return 0;
}
