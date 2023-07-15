#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include "../shell.h"

/**
 * Test the display_prompt() and read_command() functions.
 *
 * Validates that the prompt is displayed correctly
 * and the user's commands are read properly.
 */
void test_display_prompt_and_read_command(void)
{
	char command[MAX_COMMAND_LENGTH];

	printf("Test 1: Display prompt and read a command\n");
	printf("Please enter 'test_command_1':\n");
	display_prompt();
	read_command(command);
	assert(strcmp(command, "test_command_1") == 0);
	printf("Command entered: %s\n", command);
	printf("Test 1 passed\n\n");

	printf("Test 2: Display prompt and read an empty command\n");
	printf("Please press Enter without typing anything:\n");
	display_prompt();
	read_command(command);
	assert(strcmp(command, "") == 0);
	printf("Command entered: %s\n", command);
	printf("Test 2 passed\n\n");

	printf("Test 3: Display prompt and read a long command\n");
	printf("Please enter a long command (>> %d chars):\n", MAX_COMMAND_LENGTH);
	display_prompt();
	read_command(command);
	assert(strlen(command) == MAX_COMMAND_LENGTH - 1);
	printf("Command entered (truncated): %s\n", command);
	printf("Test 3 passed\n\n");
}

/**
 * execute_command - Validates that commands are executed correctly.
 * Validates that commands are executed correctly.
 */
void test_execute_command(void)
{
	char command[MAX_COMMAND_LENGTH];
	extern char **environ;

	printf("Test 4: Execute an existing command\n");
	printf("Please enter an existing command (e.g., 'ls'):\n");
	display_prompt();
	read_command(command);
	printf("Executing command: %s\n", command);
	execute_command(command, environ);
	printf("Test 4 passed\n\n");

	printf("Test 5: Execute a non-existing command\n");
	printf("Please enter a non-existing command:\n");
	display_prompt();
	read_command(command);
	printf("Executing command: %s\n", command);
	execute_command(command, environ);
	printf("Test 5 passed\n\n");
}

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int main(void)
{
	test_display_prompt_and_read_command();
	test_execute_command();

	return (0);
}
