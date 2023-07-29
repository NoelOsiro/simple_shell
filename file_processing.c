#include "my_shell.h"

int cant_open(char *file_path);
int my_file_cmds(char *file_path, int *exe_ret);

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */
int cant_open(char *file_path)
{
	char *error, *ctr_str;
	int len;

	ctr_str = my_shell_itoa(my_hist_counter);
	if (!ctr_str)
		return (127);

	len = my_strlen(my_name) + my_strlen(ctr_str) + my_strlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(ctr_str);
		return (127);
	}

	my_strcpy(error, my_name);
	my_strcat(error, ": ");
	my_strcat(error, ctr_str);
	my_strcat(error, ": Can't open ");
	my_strcat(error, file_path);
	my_strcat(error, "\n");

	free(ctr_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * my_file_cmds - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int my_file_cmds(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	my_hist_counter = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc(line, old_size, line_size);
		my_strcat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	var_replace(&line, exe_ret);
	process_line(&line, line_size);
	args = my_strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_arguements(args) != 0)
	{
		*exe_ret = 2;
		free_arguements(args, args);
		return (*exe_ret);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (my_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = call_arguements(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}

	ret = call_arguements(args, front, exe_ret);

	free(front);
	return (ret);
}
