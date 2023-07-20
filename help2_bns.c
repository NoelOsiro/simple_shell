#include "my_shell.h"

void print_help_env(void);
void print_help_setenv(void);
void print_help_unsetenv(void);
void print_help_history(void);

/**
 * print_help_env - Displays information on the custom shell builtin command 'env'.
 */
void print_help_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, get_string_length(msg));
}

/**
 * print_help_setenv - Displays information on the custom shell builtin command 'setenv'.
 */
void print_help_setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, get_string_length(msg));
}

/**
 * print_help_unsetenv - Displays information on the custom shell builtin command 'unsetenv'.
 */
void print_help_unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, get_string_length(msg));
}
