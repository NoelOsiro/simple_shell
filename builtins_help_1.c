#include "my_shell.h"

void my_helper_all(void);
void my_helper_alias(void);
void my_helper_cd(void);
void my_helper_exit(void);
void my_helper_help(void);

/**
 * my_helper_all - Displays all possible builtin my_shell commands.
 */
void my_helper_all(void)
{
	char *msg = "my_shell\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "Type 'help' to see this list.\nType 'help my_shell_name' to find ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "out more about the function 'my_shell_name'.\n\n  alias   \t";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
}
/**
 * my_helper_alias - Displays information on the my_shell command 'alias'.
 */
void my_helper_alias(void)
{
	char *msg = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "the format NAME='VALUE'.\n\talias my_shell_name [my_shell_name2 ...]:prints";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = " the aliases my_shell_name, my_shell_name2, etc. one per line, in the ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
}

/**
 * my_helper_cd - Displays information on the my_shell builtin command 'cd'.
 */
void my_helper_cd(void)
{
	char *msg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "after a change of directory.\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
}

/**
 * my_helper_exit - Displays information on the my_shell command 'exit'.
 */
void my_helper_exit(void)
{
	char *msg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = " exit 0.\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
}
/**
 * my_helper_help - Displays information on the my_shell command 'help'.
 */
void my_helper_help(void)
{
	char *msg = "help: help\n\tSee all possible my_shell builtin commands.\n";

	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "builtin command.\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
}
