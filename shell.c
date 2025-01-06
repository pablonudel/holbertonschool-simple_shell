#include "shell.h"

/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	char *input, **args;

	signal(SIGINT, handle_signint);

	while (1)
	{
		prompt();
		input = get_input();
		args = split_input(input);

		if (!args || !args[0])
		{
			free(input);
			if (args)
				free_array(args);
			continue;
		}

		if (strncmp(args[0], "exit", 4) == 0)
			builtin_exit(input, args);
		else if (strncmp(args[0], "env", 3) == 0)
			builtin_env(args);
		else
			exec_command(args);

		free_array(args);
		free(input);
	}
	return (0);
}
