#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define EOF_MARKER -2
#define EXIT_MARKER -3

/* Global environment */
extern char **my_environ;
/* Global program name */
char *program_name;
/* Global history counter */
int command_history;

typedef struct dir_list_s
{
	char *path;
	struct dir_list_s *next;
} dir_list_t;

typedef struct custom_command_s
{
	char *name;
	int (*handler)(char **args, char **front);
} custom_command_t;

typedef struct custom_alias_s
{
	char *name;
	char *value;
	struct custom_alias_s *next;
} custom_alias_t;

/* Global aliases linked list */
custom_alias_t *custom_aliases;

/* Main Helpers */
ssize_t read_line(char **lineptr, size_t *n, FILE *stream);
void *resize_memory(void *ptr, unsigned int old_size, unsigned int new_size);
char **tokenize_string(char *line, char *delim);
char *get_command_location(char *command);
dir_list_t *get_directory_paths(char *path);
int execute_command(char **args, char **front);
void free_directory_list(dir_list_t *head);
char *convert_int_to_string(int num);

/* Input Helpers */
void process_line(char **line, ssize_t read);
void replace_variables(char **args, int *result);
char *extract_arguments(char *line, int *result);
int process_arguments(char **args, char **front, int *result);
int execute_arguments(char **args, char **front, int *result);
int handle_arguments(int *result);
int validate_arguments(char **args);
void free_arguments(char **args, char **front);
char **replace_aliases(char **args);

/* String functions */
int get_string_length(const char *s);
char *concatenate_strings(char *dest, const char *src);
char *concatenate_strings_n(char *dest, const char *src, size_t n);
char *copy_string(char *dest, const char *src);
char *find_character(char *s, char c);
int find_string_length_in_set(char *s, char *accept);
int compare_strings(char *s1, char *s2);
int compare_strings_n(const char *s1, const char *s2, size_t n);

/* Custom Commands */
int (*get_custom_command(char *command))(char **args, char **front);
int my_shell_exit(char **args, char **front);
int my_shell_env(char **args, char __attribute__((__unused__)) **front);
int my_shell_setenv(char **args, char __attribute__((__unused__)) **front);
int my_shell_unsetenv(char **args, char __attribute__((__unused__)) **front);
int my_shell_cd(char **args, char __attribute__((__unused__)) **front);
int my_shell_alias(char **args, char __attribute__((__unused__)) **front);
int my_shell_help(char **args, char __attribute__((__unused__)) **front);

/* Custom Command Helpers */
char **copy_environment(void);
void free_environment(void);
char **get_environment_variable(const char *var);

/* Error Handling */
int create_error_message(char **args, int err);
char *error_message_env(char **args);
char *error_message_1(char **args);
char *error_message_2_exit(char **args);
char *error_message_2_cd(char **args);
char *error_message_2_syntax(char **args);
char *error_message_126(char **args);
char *error_message_127(char **args);

/* Linked List Helpers */
custom_alias_t *add_alias(custom_alias_t **head, char *name, char *value);
void free_alias_list(custom_alias_t *head);
dir_list_t *add_directory(dir_list_t **head, char *path);
void free_directory_list(dir_list_t *head);

void print_help_all(void);
void print_help_alias(void);
void print_help_cd(void);
void print_help_exit(void);
void print_help_help(void);
void print_help_env(void);
void print_help_setenv(void);
void print_help_unsetenv(void);
void print_help_history(void);

int process_file_commands(char *file_path, int *result);

#endif /* _MY_SHELL_H_ */
