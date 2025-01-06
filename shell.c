#include "shell.h"

/**
 * main - Entry point of the simple shell
 *
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: Always 0.
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *input, **args;

	signal(SIGINT, handle_signint);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		prompt();
		input = get_input();
		if (!input)
		{
			free(input);
			fprintf(stderr, "%s: Error getting input\n", argv[0]);
			exit(EXIT_FAILURE);
		}
		args = split_input(input);

		if (!args || !args[0])
		{
			if (!args)
			{
				free(input);
				fprintf(stderr, "%s: Error allocating memory\n", argv[0]);
				exit(EXIT_FAILURE);
			}
			continue;
		}

		if (strncmp(args[0], "exit", 4) == 0)
			builtin_exit(input, args, argv[0]);
		else if (strncmp(args[0], "env", 3) == 0)
			builtin_env(args, argv[0]);
		else
			exec_cmd(args, argv[0]);

		free(input);
		free_array(args);
	}
	return (0);
}
