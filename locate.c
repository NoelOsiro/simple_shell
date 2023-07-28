#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * get_location - Locates a command in the PATH.
 * @command: The name of the command to find the absolute path for.
 * Return: If the command is found in one of the directories in the PATH,
 *		it returns a dynamically allocated string containing the
 *		absolute path of the command.
 *		If the command is not found in any directory or if the
 *		PATH environment variable is not set, it returns NULL.
 *		The caller is responsible for freeing the memory allocated
 *		for the returned path
 *		using free() when it's no longer needed.
 */
char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	path = getenv("PATH");

	if (path)
	{
		path_copy = strdup(path);
		command_length = strlen(command);

		path_token = strtok(path_copy, ":");

		while (path_token != NULL)
		{
			directory_length = strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			free(file_path);
			path_token = strtok(NULL, ":");
		}
		free(path_copy);
		if (stat(command, &buffer) == 0)
		{
			return (command);
		}
		return (NULL);
	}
	return (NULL);
}
