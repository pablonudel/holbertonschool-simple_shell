#include "shell.h"

/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	char *input, **args;

	while (1)
	{
		prompt();
		input = get_input();
		args = split_input(input);

		if (!args)
		{
			free(input);
			continue;
		}

		if (!args[0])
			continue;

		if (strcmp(args[0], "exit") == 0)
			builtin_exit(input, args);
		else if (strcmp(args[0], "env") == 0)
			builtin_env(args);
		else
			exec_cmd(args);

		free_array(args);
		free(input);
	}
	return (0);
}
