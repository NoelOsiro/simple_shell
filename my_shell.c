#include "my_shell.h"
#include "commands.h"

/**
 * execute_command - Prompt the user for input and execute the entered command.
 *
 * @param prompt The prompt to display to the user.
 * Returns: 0 on successful execution, -1 on failure.
 */
int execute_command(const char *prompt)
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nread;

	printf("%s", prompt);
	nread = getline(&lineptr, &n, stdin);

	if (nread == -1)
	{
		printf("Ski Out....\n");
		free(lineptr);
		return (-1);
	}

	char **argv = tokenize_input(lineptr);

	if (execute_cmd(argv) == -1)
	{
		perror("Execution error");
		free(lineptr);
		free_tokens(argv);
		return (-1);
	}

	free(lineptr);
	free_tokens(argv);
	return (0);
}

/**
 * tokenize_input - Tokenize the input line.
 *
 * @lineptr: The input line to tokenize.
 * Returns: a dynamically allocated array of command tokens.
 */
char **tokenize_input(char *lineptr)
{
	const char *delim = " \n";
	char *token;
	int num_tokens = 0;

	char *lineptr_copy = strdup(lineptr);
	if (lineptr_copy == NULL)
	{
		perror("tsh: memory allocation error");
		return (NULL);
	}

	token = strtok(lineptr_copy, delim);
	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}

	char **argv = malloc(sizeof(char *) * (num_tokens + 1));
	if (argv == NULL)
	{
		perror("tsh: memory allocation error");
		free(lineptr_copy);
		return (NULL);
	}

	token = strtok(lineptr, delim);
	for (int i = 0; token != NULL; i++)
	{
		argv[i] = strdup(token);
		token = strtok(NULL, delim);
	}
	argv[num_tokens] = NULL;

	free(lineptr_copy);
	return (argv);
}

/**
 * execute_cmd - Execute the given command using execvp.
 * @argv: The command and its arguments as an array of strings.
 * Returns: 0 on successful execution, -1 on failure.
 */
int execute_cmd(char **argv)
{
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("Fork error");
		return (-1);
	} else if (pid == 0)
	{
		execvp(argv[0], argv);
		return (-1);
	} else
	{
		int status;
		waitpid(pid, &status, 0);
		return (0);
	}
}

/**
 * free_tokens - Free the allocated memory for command tokens.
 * @argv: The array of command tokens.
 */
void free_tokens(char **argv)
{
	for (int i = 0; argv[i] != NULL; i++)
	{
		free(argv[i]);
	}
	free(argv);
}

/**
 * run_shell - Run the interactive shell.
 * This function continuously prompts the user for commands and executes them.
 */
void run_shell(void)
{
	char *prompt = "(Azubi)$ ";
	while (execute_command(prompt) == 0);
}
