#include "shell.h"

/**
 * builtin_exit - Exits the shell
 *
 * @input: User input string
 * @args: Array of arguments
 * @prog_name: program name
 *
 * Return: void
 */
void builtin_exit(char *input, char **args, char *prog_name)
{
	if (args[1])
	{
		fprintf(stderr, "%s: Invalid argument: %s\n",
				prog_name, args[1]);
		return;
	}
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
void builtin_env(char **args, char *prog_name)
{
	char **env = environ;

	if (args[1])
	{
		fprintf(stderr, "%s: invalid option -- '%s'\n", prog_name, args[1]);
		return;
	}

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
