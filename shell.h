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

char *get_input(char *buffer, size_t buffer_size);
char **split_input(char *buffer, char *del);
char *_getenv(const char *env_var);
char *get_cmd(char *cmd);

#endif
