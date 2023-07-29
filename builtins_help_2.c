#include "my_shell.h"

void my_helper_env(void);
void my_helper_setenv(void);
void my_helper_unsetenv(void);
void my_helper_history(void);

/**
 * my_helper_env - Displays information on the my_shell builtin command 'env'.
 */
void my_helper_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, my_strlen(msg));
}
/**
 * my_helper_setenv - Displays information on the my_shell builtin command 'setenv'.
 */
void my_helper_setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
}
/**
 * my_helper_unsetenv - Displays information on the my_shell builtin command
 * 'unsetenv'.
 */
void my_helper_unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
}
