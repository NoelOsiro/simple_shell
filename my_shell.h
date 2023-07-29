#ifndef MY_SHELL_H_
#define MY_SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program my_shell_name */
char *my_shell_name;
/* Global my_hist_counterory counter */
int my_hist_counter;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @my_shell_name: The my_shell_name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *my_shell_name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @my_shell_name: The my_shell_name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *my_shell_name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **my_strtok(char *line, char *delim);
char *my_find_loc(char *command);
list_t *my_find_path(char *path);
int execute(char **args, char **front);
void my_free_lists(list_t *head);
char *my_shell_itoa(int num);
void process_line(char **line, ssize_t read);
void var_replace(char **args, int *exe_ret);
char *get_arguements(char *line, int *exe_ret);
int call_arguements(char **args, char **front, int *exe_ret);
int run_arguements(char **args, char **front, int *exe_ret);
int handle_arguements(int *exe_ret);
int check_arguements(char **args);
void free_arguements(char **args, char **front);
char **replace_aliases(char **args);
int my_strlen(const char *s);
char *my_strcat(char *dest, const char *src);
char *my_strncat(char *dest, const char *src, size_t n);
char *my_strcpy(char *dest, const char *src);
char *my_strchr(char *s, char c);
int my_strspn(char *s, char *accept);
int my_strcmp(char *s1, char *s2);
int my_strncmp(const char *s1, const char *s2, size_t n);
int (*get_builtin(char *command))(char **args, char **front);
int my_shell_exit(char **args, char **front);
int my_shell_env(char **args, char __attribute__((__unused__)) **front);
int my_shell_setenv(char **args, char __attribute__((__unused__)) **front);
int my_shell_unsetenv(char **args, char __attribute__((__unused__)) **front);
int my_shell_cd(char **args, char __attribute__((__unused__)) **front);
int my_shell_alias(char **args, char __attribute__((__unused__)) **front);
int my_shell_help(char **args, char __attribute__((__unused__)) **front);
char **my_copy_env(void);
void my_free_env(void);
char **my_get_env(const char *var);
int my_create_err(char **args, int err);
char *my_err_env(char **args);
char *my_err_1(char **args);
char *my_err_2(char **args);
char *my_err_3(char **args);
char *my_err_4(char **args);
char *my_err_5(char **args);
char *my_err_6(char **args);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *my_shell_name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void my_free_lists(list_t *head);

void my_helper_all(void);
void my_helper_alias(void);
void my_helper_cd(void);
void my_helper_exit(void);
void my_helper_help(void);
void my_helper_env(void);
void my_helper_setenv(void);
void my_helper_unsetenv(void);
void my_helper_my_hist_counterory(void);
int my_file_cmds(char *file_path, int *exe_ret);

#endif /* MY_SHELL_H_ */
