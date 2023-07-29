
#include "my_shell.h"

char *my_err_env(char **args);
char *my_err_1(char **args);
char *my_err_2(char **args);
char *my_err_3(char **args);
char *my_err_4(char **args);

/**
 * my_err_env - Creates an error message for my_shell_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *my_err_env(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = my_shell_itoa(hist);
	if (!hist_str)
		return (NULL);

	args--;
	len = my_strlen(name) + my_strlen(hist_str) + my_strlen(args[0]) + 45;
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
	my_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}
/**
 * my_err_1 - Creates an error message for my_shell_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *my_err_1(char **args)
{
	char *error;
	int len;

	len = my_strlen(name) + my_strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	my_strcpy(error, "alias: ");
	my_strcat(error, args[0]);
	my_strcat(error, " not found\n");

	return (error);
}
/**
 * my_err_2 - Creates an error message for my_shell_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *my_err_2(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = my_shell_itoa(hist);
	if (!hist_str)
		return (NULL);

	len = my_strlen(name) + my_strlen(hist_str) + my_strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	my_strcpy(error, name);
	my_strcat(error, ": ");
	my_strcat(error, hist_str);
	my_strcat(error, ": exit: Illegal number: ");
	my_strcat(error, args[0]);
	my_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * my_err_3 - Creates an error message for my_shell_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *my_err_3(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = my_shell_itoa(hist);
	if (!hist_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		my_strcat(error, ": cd: Illegal option ");
	else
		my_strcat(error, ": cd: can't cd to ");
	my_strcat(error, args[0]);
	my_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * my_err_4 - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *my_err_4(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = my_shell_itoa(hist);
	if (!hist_str)
		return (NULL);

	len = my_strlen(name) + my_strlen(hist_str) + my_strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	my_strcpy(error, name);
	my_strcat(error, ": ");
	my_strcat(error, hist_str);
	my_strcat(error, ": Syntax error: \"");
	my_strcat(error, args[0]);
	my_strcat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
