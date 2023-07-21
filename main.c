#include "my_shell.h"

/**
 * main - Main function that starts the shell.
 *
 * @param ac Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return Returns 0 on successful completion.
 */
int main(int ac, char **argv)
{
	(void)ac;
	(void)argv;
	run_shell();
	return 0;
}
