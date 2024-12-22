#include "shell.h"

void print_env(void)
{
	char **env = environ;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
