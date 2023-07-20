#include "my_shell.h"

void sig_handler(int sig);
int execute_command(char **args, char **front);

/**
 * sig_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void sig_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execute_command - Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *		 Otherwise - The exit value of the last executed command.
 */
int execute_command(char **args, char **front)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_command_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = create_error_message(args, 126);
		else
			ret = create_error_message(args, 127);
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, my_environ);
			if (errno == EACCES)
				ret = create_error_message(args, 126);
			free_environment();
			free_arguments(args, front);
			free_alias_list(custom_aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

	program_name = argv[0];
	command_history = 1;
	custom_aliases = NULL;
	signal(SIGINT, sig_handler);

	*exe_ret = 0;
	my_environ = copy_environment();
	if (!my_environ)
		exit(-100);

	if (argc != 1)
	{
		ret = proc_file_commands(argv[1], exe_ret);
		free_environment();
		free_alias_list(custom_aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != EOF_MARKER && ret != EXIT_MARKER)
			ret = handle_arguments(exe_ret);
		free_environment();
		free_alias_list(custom_aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = handle_arguments(exe_ret);
		if (ret == EOF_MARKER || ret == EXIT_MARKER)
		{
			if (ret == EOF_MARKER)
				write(STDOUT_FILENO, new_line, 1);
			free_environment();
			free_alias_list(custom_aliases);
			exit(*exe_ret);
		}
	}

	free_environment();
	free_alias_list(custom_aliases);
	return (*exe_ret);
}
