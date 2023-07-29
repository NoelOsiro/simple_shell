
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
	char *error, *ctr_str;
	int len;

	ctr_str = my_shell_itoa(my_hist_counter);
	if (!ctr_str)
		return (NULL);

	len = my_strlen(my_name) + my_strlen(ctr_str) + my_strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(ctr_str);
		return (NULL);
	}

	my_strcpy(error, my_name);
	my_strcat(error, ": ");
	my_strcat(error, ctr_str);
	my_strcat(error, ": ");
	my_strcat(error, args[0]);
	my_strcat(error, ": Permission denied\n");

	free(ctr_str);
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
	char *error, *ctr_str;
	int len;

	ctr_str = my_shell_itoa(my_hist_counter);
	if (!ctr_str)
		return (NULL);

	len = my_strlen(my_name) + my_strlen(ctr_str) + my_strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(ctr_str);
		return (NULL);
	}

	my_strcpy(error, my_name);
	my_strcat(error, ": ");
	my_strcat(error, ctr_str);
	my_strcat(error, ": ");
	my_strcat(error, args[0]);
	my_strcat(error, ": not found\n");

	free(ctr_str);
	return (error);
}
