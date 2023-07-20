#include "my_shell.h"

int display_env(char **args, char __attribute__((__unused__)) **front);
int display_setenv(char **args, char __attribute__((__unused__)) **front);
int display_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * display_env - Prints the current my_environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int display_env(char **args, char __attribute__((__unused__)) **front)
{
	int index;
	char nc = '\n';

	if (!my_environ)
		return (-1);

	for (index = 0; my_environ[index]; index++)
	{
		write(STDOUT_FILENO, my_environ[index], get_string_length(my_environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * display_setenv - Changes or adds an my_environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int display_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_my_environ, *new_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (create_error_message(args, -1));

	new_value = malloc(get_string_length(args[0]) + 1 + get_string_length(args[1]) + 1);
	if (!new_value)
		return (create_error_message(args, -1));
	copy_string(new_value, args[0]);
	concatenate_strings(new_value, "=");
	concatenate_strings(new_value, args[1]);

	env_var = get_environment_variable(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; my_environ[size]; size++)
		;

	new_my_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_my_environ)
	{
		free(new_value);
		return (create_error_message(args, -1));
	}

	for (index = 0; my_environ[index]; index++)
		new_my_environ[index] = my_environ[index];

	free(my_environ);
	my_environ = new_my_environ;
	my_environ[index] = new_value;
	my_environ[index + 1] = NULL;

	return (0);
}

/**
 * display_unsetenv - Deletes an my_environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int display_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_my_environ;
	size_t size;
	int index, index2;

	if (!args[0])
		return (create_error_message(args, -1));
	env_var = get_environment_variable(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; my_environ[size]; size++)
		;

	new_my_environ = malloc(sizeof(char *) * size);
	if (!new_my_environ)
		return (create_error_message(args, -1));

	for (index = 0, index2 = 0; my_environ[index]; index++)
	{
		if (*env_var == my_environ[index])
		{
			free(*env_var);
			continue;
		}
		new_my_environ[index2] = my_environ[index];
		index2++;
	}
	free(my_environ);
	my_environ = new_my_environ;
	my_environ[size - 1] = NULL;

	return (0);
}
