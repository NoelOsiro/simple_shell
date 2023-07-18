#include "my_shell.h"

char **copy_environment(void);
void free_environment(void);
char **get_environment_variable(const char *var);

/**
 * copy_environment - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **copy_environment(void)
{
	char **new_my_environ;
	size_t size;
	int index;

	for (size = 0; my_environ[size]; size++)
		;

	new_my_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_my_environ)
		return (NULL);

	for (index = 0; my_environ[index]; index++)
	{
		new_my_environ[index] = malloc(get_string_length(my_environ[index]) + 1);

		if (!new_my_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_my_environ[index]);
			free(new_my_environ);
			return (NULL);
		}
		copy_string(new_my_environ[index], my_environ[index]);
	}
	new_my_environ[index] = NULL;

	return (new_my_environ);
}

/**
 * free_environment - Frees the environment copy.
 */
void free_environment(void)
{
	int index;

	for (index = 0; my_environ[index]; index++)
		free(my_environ[index]);
	free(my_environ);
}

/**
 * get_environment_variable - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **get_environment_variable(const char *var)
{
	int index, len;

	len = get_string_length(var);
	for (index = 0; my_environ[index]; index++)
	{
		if (compare_strings_n(var, my_environ[index], len) == 0)
			return (&my_environ[index]);
	}

	return (NULL);
}
