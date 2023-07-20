#include "my_shell.h"

/**
 * error_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_message_126(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = convert_int_to_string(command_history);
	if (!hist_str)
		return (NULL);

	len = get_string_length(program_name) + get_string_length(hist_str) + get_string_length(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copy_string(error, program_name);
	concatenate_strings(error, ": ");
	concatenate_strings(error, hist_str);
	concatenate_strings(error, ": ");
	concatenate_strings(error, args[0]);
	concatenate_strings(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * error_message_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_message_127(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = convert_int_to_string(command_history);
	if (!hist_str)
		return (NULL);

	len = get_string_length(program_name) + get_string_length(hist_str) + get_string_length(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copy_string(error, program_name);
	concatenate_strings(error, ": ");
	concatenate_strings(error, hist_str);
	concatenate_strings(error, ": ");
	concatenate_strings(error, args[0]);
	concatenate_strings(error, ": not found\n");

	free(hist_str);
	return (error);
}
