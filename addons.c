#include "my_shell.h"

/**
 * release_memory - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void release_memory(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}

/**
 * get_process_id - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_process_id(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cannot read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * find_env_value - Gets the value corresponding to an environmental variable.
 * @var_name: The environmental variable to search for.
 * @var_len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *find_env_value(char *var_name, int var_len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(var_len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	concatenate_strings_n(var, var_name, var_len);

	var_addr = get_environment_variable(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(get_string_length(temp) + 1);
		if (replacement)
			copy_string(replacement, temp);
	}

	return (replacement);
}

/**
 * replace_variables - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and environmental variables
 *              preceded by $ with their corresponding value.
 */
void replace_variables(char **line, int *exe_ret)
{
	int j, k = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
			old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = get_process_id();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = convert_int_to_string(*exe_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; old_line[k] &&
					old_line[k] != '$' &&
					old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replacement = find_env_value(&old_line[j + 1], len);
			}
			new_line = malloc(j + get_string_length(replacement)
						+ get_string_length(&old_line[k]) + 1);
			if (!new_line)
				return;
			new_line[0] = '\0';
			concatenate_strings_n(new_line, old_line, j);
			if (replacement)
			{
				concatenate_strings(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			concatenate_strings(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
