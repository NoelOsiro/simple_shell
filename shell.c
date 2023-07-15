#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> // Include the necessary header for the wait() function
#include "shell.h"

extern char **environ;

void display_prompt() {
    printf(">> ");
}

void read_command(char* command) {
    fgets(command, MAX_COMMAND_LENGTH, stdin);

    // Remove trailing newline character
    command[strcspn(command, "\n")] = '\0';
}

void execute_command(const char* command) {
    if (access(command, X_OK) == 0) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
        } else if (pid == 0) {
            // Child process
            char* argv[] = {(char*)command, NULL};
            execve(command, argv, environ);
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL);
        }
    } else {
        printf("Command not found: %s\n", command);
    }
}
