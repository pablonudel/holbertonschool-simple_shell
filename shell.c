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
	int int_PID = 0;

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
		{
			int_PID++;
			builtin_env(args);
		}
		else
		{
			int_PID++;
			exec_cmd(args, int_PID, argv[0]);
		}

		free_array(args);
		free(input);
	}
	int_PID = 0;
	return (0);
}
