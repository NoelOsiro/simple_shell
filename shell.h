#ifndef SHELL_H
#define SHELL_H

#define MAX_COMMAND_LENGTH 100

extern char **environ;

void display_prompt(void);
void read_command(char *command);
void execute_command(const char *command);

#endif
