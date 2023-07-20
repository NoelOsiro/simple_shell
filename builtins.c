#include "my_shell.h"

int (*get_custom_builtin(char *command))(char **args, char **front);
int my_shell_exit(char **args, char **front);
int my_shell_cd(char **args, char __attribute__((__unused__)) **front);
int my_shell_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_custom_builtin - Matches a command with a corresponding
 *                      custom shell builtin function.
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_custom_builtin(char *command))(char **args, char **front)
{
	custom_command_t funcs[] = {
		{ "exit", my_shell_exit },
		{ "env", display_env },
		{ "setenv", display_setenv },
		{ "unsetenv", display_unsetenv },
		{ "cd", my_shell_cd },
		{ "alias", my_shell_alias },
		{ "help", my_shell_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (compare_strings(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].handler);
}

/**
 * my_shell_exit - Causes normal process termination
 *                 for the custom shell.
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
				return (create_error_message(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error_message(--args, 2));
	args -= 1;
	free_arguments(args, front);
	free_environment();
	free_alias_list(custom_aliases);
	exit(num);
}

/**
 * my_shell_cd - Changes the current directory of the custom shell process.
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
		if (*(args[0]) == '-' || compare_strings(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (get_environment_variable("OLDPWD") != NULL)
					(chdir(*(get_environment_variable("OLDPWD")) + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error_message(args, 2));
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
				return (create_error_message(args, 2));
			}
		}
	}
	else
	{
		if (get_environment_variable("HOME") != NULL)
			chdir(*((get_environment_variable("HOME")) + 5));
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (display_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (display_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, get_string_length(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free_arguments(dir_info, dir_info);
	return (0);
}

/**
 * my_shell_help - Displays information about custom shell builtin commands.
 * @args: An array of arguments.
 * @front: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int my_shell_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		print_help_all();
	else if (compare_strings(args[0], "alias") == 0)
		print_help_alias();
	else if (compare_strings(args[0], "cd") == 0)
		print_help_cd();
	else if (compare_strings(args[0], "exit") == 0)
		print_help_exit();
	else if (compare_strings(args[0], "env") == 0)
		print_help_env();
	else if (compare_strings(args[0], "setenv") == 0)
		print_help_setenv();
	else if (compare_strings(args[0], "unsetenv") == 0)
		print_help_unsetenv();
	else if (compare_strings(args[0], "help") == 0)
		print_help_help();
	else
		write(STDERR_FILENO, program_name, get_string_length(program_name));

	return (0);
}
