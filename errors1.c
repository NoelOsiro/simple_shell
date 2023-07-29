
#include "my_shell.h"

char *my_err_5(char **args);
char *my_err_6(char **args);

/**
 * my_err_5 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *my_err_5(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = my_shell_itoa(hist);
	if (!hist_str)
		return (NULL);

	len = my_strlen(name) + my_strlen(hist_str) + my_strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	my_strcpy(error, name);
	my_strcat(error, ": ");
	my_strcat(error, hist_str);
	my_strcat(error, ": ");
	my_strcat(error, args[0]);
	my_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * my_err_6 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *my_err_6(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = my_shell_itoa(hist);
	if (!hist_str)
		return (NULL);

	len = my_strlen(name) + my_strlen(hist_str) + my_strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	my_strcpy(error, name);
	my_strcat(error, ": ");
	my_strcat(error, hist_str);
	my_strcat(error, ": ");
	my_strcat(error, args[0]);
	my_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}
