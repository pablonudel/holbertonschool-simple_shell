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
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		prompt();
		input = get_input();
		args = split_input(input);

		if (!args || !args[0])
		{
			if (!args)
			{
				free(input);
				perror("hsh: Error allocating memory");
			}
			continue;
		}

		if (strcmp(args[0], "exit") == 0)
			builtin_exit(input, args, &exec_count, argv[0]);
		else if (strcmp(args[0], "env") == 0)
			builtin_env(args, &exec_count);
		else
			exec_cmd(args, &exec_count, argv[0]);

		free(input);
		free_array(args);
	}
	return (0);
}
