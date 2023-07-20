#include "my_shell.h"

char *get_full_path(char *command);
char *fill_path_with_pwd(char *path);
dir_list_t *get_path_directories(char *path);

/**
 * get_full_path - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *		 Otherwise - the full pathname of the command.
 */
char *get_full_path(char *command)
{
	char **path, *temp;
	dir_list_t *dirs, *head;
	struct stat st;

	path = get_environment_variable("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_directories(*path);
	head = dirs;

	while (dirs)
	{
		temp = malloc(get_string_length(dirs->path) + get_string_length(command) + 2);
		if (!temp)
			return (NULL);

		copy_string(temp, dirs->path);
		concatenate_strings(temp, "/");
		concatenate_strings(temp, command);

		if (stat(temp, &st) == 0)
		{
			free_directory_list(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	free_directory_list(head);

	return (NULL);
}

/**
 * fill_path_with_pwd - Copies path but also replaces leading/sandwiched/trailing
 *					  colons (:) with the current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *		 with the current working directory.
 */
char *fill_path_with_pwd(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *get_environment_variable("PWD") + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += get_string_length(pwd) + 1;
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
				concatenate_strings(path_copy, pwd);
				concatenate_strings(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				concatenate_strings(path_copy, ":");
				concatenate_strings(path_copy, pwd);
			}
			else
				concatenate_strings(path_copy, ":");
		}
		else
		{
			concatenate_strings_n(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_directories - Tokenizes a colon-separated list of
 *						directories into a dir_list_t linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
dir_list_t *get_path_directories(char *path)
{
	int index;
	char **dirs, *path_copy;
	dir_list_t *head = NULL;

	path_copy = fill_path_with_pwd(path);
	if (!path_copy)
		return (NULL);
	dirs = tokenize_string(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_directory(&head, dirs[index]) == NULL)
		{
			free_directory_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}

