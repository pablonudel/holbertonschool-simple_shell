#include "shell.h"

/**
 * builtin_exit - Exits the shell
 *
 * @input: User input string
 * @args: Array of arguments
 *
 * Return: void
 */
void builtin_exit(char *input, char **args)
{
	int exit_status = 0;

	if (args[1])
	{
		char *endptr;

		exit_status = strtol(args[1], &endptr, 10);

		if (*endptr || exit_status < 0)
		{
			fprintf(stderr, "./hsh: Illegal number: %s\n", args[1]);
			return;
		}
	}	

	signal(SIGINT, SIG_DFL);
	free(input);
	free_array(args);
	exit(exit_status);
}

/**
 * builtin_env - Prints the current environment variables
 *
 * @args: The array of arguments
 *
 * Return: void
 */
void builtin_env(char **args)
{
	char **env = environ;

	if (args[1])
	{
		fprintf(stderr, "./hsh: invalid option -- '%s'\n", args[1]);
		return;
	}

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
