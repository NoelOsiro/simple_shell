
#include "my_shell.h"

char **my_copy_env(void);
void my_free_env(void);
char **my_get_env(const char *var);

/**
 * my_copy_env - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **my_copy_env(void)
{
	char **new_environ;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(my_strlen(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		my_strcpy(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;

	return (new_environ);
}

/**
 * my_free_env - Frees the the environment copy.
 */
void my_free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * my_get_env - Gets an environmental variable from the PATH.
 * @var: The my_name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **my_get_env(const char *var)
{
	int index, len;

	len = my_strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (my_strncmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
