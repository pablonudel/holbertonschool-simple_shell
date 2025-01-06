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
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		prompt();
		input = get_input();
		args = split_input(input);

		if (!args[0])
			continue;

		if (strncmp(args[0], "exit", 4) == 0)
			builtin_exit(input, args);
		else if (strncmp(args[0], "env", 3) == 0)
			builtin_env(args);
		else
			exec_cmd(args);

		free(input);
		free_array(args);
	}
	return (0);
}
