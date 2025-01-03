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

extern char **environ;

void prompt(void);
char *get_input(void);
char **split_input(char *input);
char *_getenv(const char *env_var);
void free_array(char **array);
char *get_cmd(char *arg, int *error);
void exec_cmd(char **args, int int_PID, char *prog_name);
void builtin_exit(char *input, char **args);
void builtin_env(char **args);

#endif
