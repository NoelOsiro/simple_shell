#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	int running = 1;

	while (running)
	{
		display_prompt();
		read_command(command);

		if (strcmp(command, "exit") == 0)
		{
			running = 0;
		}
		else
		{
			execute_command(command);
		}
	}

	return (0);
}
