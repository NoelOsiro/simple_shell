#include "my_shell.h"

/**
 * error_env - Creates an error message for shellby_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_env(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = convert_int_to_string(command_history);
	if (!hist_str)
		return (NULL);

	args--;
	len = get_string_length(program_name) + get_string_length(hist_str) + get_string_length(args[0]) + 45;
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
	concatenate_strings(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * error_1 - Creates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_1(char **args)
{
	char *error;
	int len;

	len = get_string_length("alias: ") + get_string_length(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	copy_string(error, "alias: ");
	concatenate_strings(error, args[0]);
	concatenate_strings(error, " not found\n");

	return (error);
}

/**
 * error_2_exit - Creates an error message for shellby_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_exit(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = convert_int_to_string(command_history);
	if (!hist_str)
		return (NULL);

	len = get_string_length(program_name) + get_string_length(hist_str) + get_string_length(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copy_string(error, program_name);
	concatenate_strings(error, ": ");
	concatenate_strings(error, hist_str);
	concatenate_strings(error, ": exit: Illegal number: ");
	concatenate_strings(error, args[0]);
	concatenate_strings(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_cd - Creates an error message for shellby_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_cd(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = convert_int_to_string(command_history);
	if (!hist_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		concatenate_strings(error, ": cd: Illegal option ");
	else
		concatenate_strings(error, ": cd: can't cd to ");
	concatenate_strings(error, args[0]);
	concatenate_strings(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_syntax - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_syntax(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = convert_int_to_string(command_history);
	if (!hist_str)
		return (NULL);

	len = get_string_length(program_name) + get_string_length(hist_str) + get_string_length(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copy_string(error, program_name);
	concatenate_strings(error, ": ");
	concatenate_strings(error, hist_str);
	concatenate_strings(error, ": Syntax error: \"");
	concatenate_strings(error, args[0]);
	concatenate_strings(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
