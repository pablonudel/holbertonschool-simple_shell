#include "shell.h"

void builtin_exit(char *input, char **args)
{
	free(input);
	free_array(args);
	exit(EXIT_SUCCESS);
}

void builtin_env(char **args)
{
	char **env = environ;

	if (args[1])
	{
		fprintf(stderr, "%s: invalid option -- '%s'\n", args[0], args[1]);
		return;
	}

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
