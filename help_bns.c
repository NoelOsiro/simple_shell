#include "my_shell.h"

void print_help_all(void);
void print_help_alias(void);
void print_help_cd(void);
void print_help_exit(void);
void print_help_help(void);

/**
 * print_help_all - Displays all possible custom shell commands.
 */
void print_help_all(void)
{
	char *msg = "My Shell\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, msg, get_string_length(msg));
}

/**
 * print_help_alias - Displays information on the custom shell builtin command 'alias'.
 */
void print_help_alias(void)
{
	char *msg = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, msg, get_string_length(msg));
}

/**
 * print_help_cd - Displays information on the custom shell builtin command 'cd'.
 */
void print_help_cd(void)
{
	char *msg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "after a change of directory.\n";
	write(STDOUT_FILENO, msg, get_string_length(msg));
}

/**
 * print_help_exit - Displays information on the custom shell builtin command 'exit'.
 */
void print_help_exit(void)
{
	char *msg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = " exit 0.\n";
	write(STDOUT_FILENO, msg, get_string_length(msg));
}

/**
 * print_help_help - Displays information on the custom shell builtin command 'help'.
 */
void print_help_help(void)
{
	char *msg = "help: help\n\tSee all possible Custom Shell builtin commands.\n";

	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, msg, get_string_length(msg));
	msg = "builtin command.\n";
	write(STDOUT_FILENO, msg, get_string_length(msg));
}
