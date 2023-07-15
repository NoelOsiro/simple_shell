#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
	printf(">> ");
}

/**
 * read_command - Read the user's command from standard input.
 * @command: The command buffer.
 */
void read_command(char *command)
{
	fgets(command, MAX_COMMAND_LENGTH, stdin);

	command[strcspn(command, "\n")] = '\0';
}

/**
 * execute_command - Execute the given command.
 * @command: The command to execute.
 * @environ: The array of environment variables.
 */
void execute_command(const char *command, char **environ)
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


