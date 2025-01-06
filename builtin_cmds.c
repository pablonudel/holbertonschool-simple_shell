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
	free(input);
	free_array(args);
	exit(EXIT_SUCCESS);
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
