
#include "my_shell.h"

char *fill_path_dir(char *path);
list_t *my_find_path(char *path);


/**
 * my_find_loc - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathmy_name of the command.
 */
char *my_find_loc(char *command)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = my_get_env("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = my_find_path(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(my_strlen(dirs->dir) + my_strlen(command) + 2);
		if (!temp)
			return (NULL);

		my_strcpy(temp, dirs->dir);
		my_strcat(temp, "/");
		my_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			my_free_lists(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	my_free_lists(head);

	return (NULL);
}

/**
 * fill_path_dir - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *fill_path_dir(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(my_get_env("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += my_strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				my_strcat(path_copy, pwd);
				my_strcat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				my_strcat(path_copy, ":");
				my_strcat(path_copy, pwd);
			}
			else
				my_strcat(path_copy, ":");
		}
		else
		{
			my_strncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * my_find_path - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *my_find_path(char *path)
{
	int index;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = my_strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_node_end(&head, dirs[index]) == NULL)
		{
			my_free_lists(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
