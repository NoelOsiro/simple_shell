#include "commands.h"
#include "my_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * execmd - Execute a command with execve.
 *		This function takes a null-terminated array of strings `argv`,
 *		where the first element `argv[0]` is the name of the command to
 *		be executed, and the remaining elements are its arguments.
 *		The function uses the `get_location` function to obtain the
 *		absolute path of the command based on the PATH environment variable.
 *		If the command is found, it is executed using the `execve` system call,
 *		passing the command's absolute path and the argument array `argv`.
 *		If the command execution is unsuccessful, an error message is displayed
 *		using `perror`.
 * 
 * argv: Null-terminated array of strings containing the command and its arguments.
 */
void execmd(char **argv){
	char *command = NULL, *actual_command = NULL;

	if (argv){
		command = argv[0];
		actual_command = get_location(command);
		if (execve(actual_command, argv, NULL) == -1)
		{
			perror("Error:");
		}
	}

}
