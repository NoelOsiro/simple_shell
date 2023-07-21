#include "my_shell.h"
#include "commands.h"
/**
 * run_shell() - Run the interactive shell.
*
* This function implements a simple interactive shell that continuously prompts the user for commands and executes them. The shell reads input from the standard input (stdin) and parses each line into individual tokens (words) using the specified delimiter. It then forks a new process to execute the command using the `execvp()` function, which searches for the command in the directories listed in the PATH environment variable.
*
* The function uses the `getline()` function to read input lines from the user. It allocates memory for each command token and ensures proper memory deallocation after command execution. The shell waits for the command to complete using the `waitpid()` function before showing the next prompt for user input.
*
* The shell will terminate when the user presses the end-of-file (EOF) character (usually Ctrl + D on Unix-based systems) or if there's an error in memory allocation or command execution.
*/
void run_shell(void)
{
	char *prompt = "(Azubi)$ ";
	char *lineptr = NULL, *lineptr_copy = NULL;
	size_t n = 0;
	ssize_t nread;
	const char *delim = " \n";
	char **argv;
	int i;
	int num_tokens = 0;
	char *token;
	pid_t pid;

	while (1)
	{
		printf("%s", prompt);
		nread = getline(&lineptr, &n, stdin);
		if (nread == -1)
		{
			printf("Ski Out....\n");
			break;
		}
		lineptr_copy = malloc(sizeof(char) * nread);
		if (lineptr_copy == NULL)
		{
			perror("tsh: memory allocation error");
			break;
		}
		strcpy(lineptr_copy, lineptr);

		token = strtok(lineptr_copy, delim);

		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;

		argv = malloc(sizeof(char *) * num_tokens);

		token = strtok(lineptr_copy, delim);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
		pid = fork();

		if (pid < 0)
		{
			perror("Fork error");
		} else if (pid == 0)
		{
		   
			execvp(argv[0], argv);
			perror("Execution error");
			exit(1);
		} else
		{
		   
			int status;
			waitpid(pid, &status, 0);
		}

		for (i = 0; i < num_tokens; i++)
		{
			free(argv[i]);
		}
		free(argv);

		free(lineptr_copy);
	}
	free(lineptr);
}
