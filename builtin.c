
#include "my_shell.h"
int (*get_builtin(char *command))(char **args, char **front);
int my_shell_exit(char **args, char **front);
int my_shell_cd(char **args, char __attribute__((__unused__)) **front);
int my_shell_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtin - Matches a command with a corresponding
 *               my_shell builtin function.
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", my_shell_exit },
		{ "env", my_shell_env },
		{ "setenv", my_shell_setenv },
		{ "unsetenv", my_shell_unsetenv },
		{ "cd", my_shell_cd },
		{ "alias", my_shell_alias },
		{ "help", my_shell_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (my_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}
/**
 * my_shell_exit - Causes normal process termination
 *                for the my_shell shell.
 * @args: An array of arguments containing the exit value.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int my_shell_exit(char **args, char **front)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (my_create_err(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (my_create_err(--args, 2));
	args -= 1;
	free_arguements(args, front);
	my_free_env();
	free_alias_list(aliases);
	exit(num);
}
/**
 * my_shell_cd - Changes the current directory of the my_shell process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int my_shell_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || my_strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (my_get_env("OLDPWD") != NULL)
					(chdir(*my_get_env("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (my_create_err(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (my_create_err(args, 2));
			}
		}
	}
	else
	{
		if (my_get_env("HOME") != NULL)
			chdir(*(my_get_env("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (my_shell_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (my_shell_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, my_strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}
/**
 * my_shell_help - Displays information about my_shell builtin commands.
 * @args: An array of arguments.
 * @front: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int my_shell_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		my_helper_all();
	else if (my_strcmp(args[0], "alias") == 0)
		my_helper_alias();
	else if (my_strcmp(args[0], "cd") == 0)
		my_helper_cd();
	else if (my_strcmp(args[0], "exit") == 0)
		my_helper_exit();
	else if (my_strcmp(args[0], "env") == 0)
		my_helper_env();
	else if (my_strcmp(args[0], "setenv") == 0)
		my_helper_setenv();
	else if (my_strcmp(args[0], "unsetenv") == 0)
		my_helper_unsetenv();
	else if (my_strcmp(args[0], "help") == 0)
		my_helper_help();
	else
		write(STDERR_FILENO, name, my_strlen(name));

	return (0);
}
