#include "my_shell.h"

char *extract_arguments(char *line, int *result);
int process_arguments(char **args, char **front, int *result);
int execute_arguments(char **args, char **front, int *result);
int handle_arguments(int *result);
int validate_arguments(char **args);

/**
 * extract_arguments - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @result: The return value of the last execute_commandd command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *extract_arguments(char *line, int *result)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = read_line(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		command_history++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (extract_arguments(line, result));
	}

	line[read - 1] = '\0';
	replace_variables(&line, result);
	process_line(&line, read);

	return (line);
}

/**
 * process_arguments - Partitions operators from commands and calls them.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @result: The return value of the parent process' last execute_commandd command.
 *
 * Return: The return value of the last execute_commandd command.
 */
int process_arguments(char **args, char **front, int *result)
{
	int ret, index;

	if (!args[0])
		return (*result);
	for (index = 0; args[index]; index++)
	{
		if (compare_strings_n(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_custom_aliases(args);
			ret = execute_arguments(args, front, result);
			if (*result != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (compare_strings_n(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_custom_aliases(args);
			ret = execute_arguments(args, front, result);
			if (*result == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
	}
	args = replace_custom_aliases(args);
	ret = execute_arguments(args, front, result);
	return (ret);
}

/**
 * execute_arguments - Calls the execution of a command.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @result: The return value of the parent process' last execute_commandd command.
 *
 * Return: The return value of the last execute_commandd command.
 */
int execute_arguments(char **args, char **front, int *result)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_custom_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT_MARKER)
			*result = ret;
	}
	else
	{
		*result = execute_command(args, front);
		ret = *result;
	}

	command_history++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * handle_arguments - Gets, calls, and runs the execution of a command.
 * @result: The return value of the parent process' last execute_commandd command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The EXIT_MARKER value of the last execute_command command.
 */
int handle_arguments(int *result)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = extract_arguments(line, result);
	if (!line)
		return (EOF_MARKER);

	args = tokenize_string(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (validate_arguments(args) != 0)
	{
		*result = 2;
		free_arguments(args, args);
		return (*result);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (compare_strings_n(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = process_arguments(args, front, result);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = process_arguments(args, front, result);

	free(front);
	return (ret);
}

/**
 * validate_arguments - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int validate_arguments(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error_message(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error_message(&args[i + 1], 2));
		}
	}
	return (0);
}
