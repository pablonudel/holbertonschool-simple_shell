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
	int exec_count = 0;

	signal(SIGINT, handle_signint);
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
			builtin_exit(input, args, &exec_count, argv[0]);
		else if (strcmp(args[0], "env") == 0)
			builtin_env(args, &exec_count);
		else
			exec_cmd(args, &exec_count, argv[0]);

		free_array(args);
		free(input);
	}
	return (0);
}
