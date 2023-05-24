#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(shell *datash);
} builtin_t;

sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(shell *datash, char *input, int i, int bool);
int check_syntax_error(shell *datash, char *input);
char *without_comment(char *in);
void shell_prompt(shell *datash);
char *read_line(int *i_eof);
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, shell *datash);
int split_commands(shell *datash, char *input);
char **split_line(char *input);
void check_env(r_var **h, char *in, shell *data);
int check_vars(r_var **h, char *in, char *st, shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, shell *datash);
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
int exec_line(shell *datash);
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(shell *datash);
int check_error_cmd(char *dir, shell *datash);
int cmd_exec(shell *datash);
char *_getenv(const char *name, char **_environ);
int _env(shell *datash);
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, shell *datash);
int _setenv(shell *datash);
int _unsetenv(shell *datash);
void cd_dot(shell *datash);
void cd_to(shell *datash);
void cd_previous(shell *datash);
void cd_to_home(shell *datash);
int cd_shell(shell *datash);
int (*get_builtin(char *cmd))(shell *datash);
int exit_shell(shell *datash);
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);
char *strcat_cd(shell *, char *, char *, char *);
char *error_get_cd(shell *datash);
char *error_not_found(shell *datash);
char *error_exit_shell(shell *datash);
char *error_env(shell *datash);
char *error_path_126(shell *datash);
int get_error(shell *datash, int eval);
void get_sigint(int sig);
void reverse_string(char *s);

#endif
