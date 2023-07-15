#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"


extern char **environ;

void display_prompt(void)
{
    printf(">> ");
}

void read_command(char *command)
{
    fgets(command, MAX_COMMAND_LENGTH, stdin);

    command[strcspn(command, "\n")] = '\0';
}

void execute_command(const char *command)
{
    if (access(command, X_OK) == 0)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork");
        }
        else if (pid == 0)
        {

            char *argv[2];
            argv[0] = (char *)command;
            argv[1] = NULL;
            execve(command, argv, environ);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else
        {

            wait(NULL);
        }
    }
    else
    {
        printf("Command not found: %s\n", command);
    }
}


