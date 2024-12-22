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

char *get_input(void);
char **split_input(char *input);
void print_env(void);
char *_getenv(const char *env_var);
char *get_cmd(char *arg);

#endif
