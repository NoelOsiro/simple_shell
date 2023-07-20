#include "shell.h"

char *get_command(char *line, int *last_exit_code);
int handle_commands(int *last_exit_code);

/**
 * get_command - Reads a command from standard input.
 * @line: A buffer to store the command.
 * @last_exit_code: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_command(char *line, int *last_exit_code)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_command(line, last_exit_code));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, last_exit_code);
	handle_line(&line, read);

	return (line);
}

/**
 * handle_commands - Gets, calls, and runs the execution of a command.
 * @last_exit_code: The return value of the last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         Otherwise - The exit value of the last executed command.
 */
int handle_commands(int *last_exit_code)
{
	int ret = 0;
	char **args, *line = NULL;

	line = get_command(line, last_exit_code);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*last_exit_code = 2;
		free_args(args, args);
		return (*last_exit_code);
	}

	ret = call_args(args, args, last_exit_code);

	free_args(args, args);
	return (ret);
}
