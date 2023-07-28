#include "my_shell.h"

/**
 * main - Main function that starts the shell.
 *
 * @ac: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 * Returns: 0 on successful completion.
 */
int main(int ac, char **argv)
{
	(void)ac;
	(void)argv;
	run_shell();
	return 0;
}
