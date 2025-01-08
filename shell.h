#ifndef shell_h
#define shell_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

extern char **environ;

/**
 * struct exec_context - Structure to hold execution context data
 *
 * @input: User input string
 * @args: Array of arguments parsed from the input
 * @exec_count: Count of executed commands or tasks
 * @program_name: Name of the current program or shell
 * @exit_code: Exit code of the last executed command
 * @buffer: Internal buffer used to manage user input lines
 */
typedef struct exec_context
{
	char *input;
	char **args;
	int exec_count;
	char *program_name;
	int exit_code;
	char *buffer;
} exec_context_t;

void prompt(void);
void handle_signint(int sig);
char *get_input(exec_context_t *context);
char **split_input(exec_context_t *context);
char *_getenv(const char *env_var);
void free_array(char **array);
void print_error(exec_context_t *context, int code);
char *get_cmd(char *arg);
void exec_command(exec_context_t *context);
void builtin_exit(exec_context_t *context);
void builtin_env(exec_context_t *context);

#endif
