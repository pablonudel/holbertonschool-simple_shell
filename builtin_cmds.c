#include "shell.h"

/**
 * builtin_exit - Exits the shell
 *
 * @input: User input string
 * @args: Array of arguments
 * @exec_count: command execution counter
 * @prog_name: program name
 *
 * Return: void
 */
void builtin_exit(char *input, char **args, int *exec_count)
{
	*exec_count += 1;
	/*
	if (args[1] != NULL)
	{
		fprintf(stderr, "%s: %d: %s: too many arguments\n",
				prog_name, *exec_count, args[0]);
		return;
	}
	*/
	free(input);
	free_array(args);
	exit(EXIT_SUCCESS);
}

/**
 * builtin_env - Prints the current environment variables
 *
 * @args: The array of arguments
 * @exec_count: command execution counter
 *
 * Return: void
 */
void builtin_env(char **args, int *exec_count)
{
	char **env = environ;

	*exec_count += 1;
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
