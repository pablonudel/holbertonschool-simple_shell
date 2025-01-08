#include "shell.h"

/**
 * main - Entry point of the simple shell
 *
 * @argc: number of arguments (unused)
 * @argv: array of arguments
 *
 * Return: Always 0.
 */
int main(int argc __attribute__((unused)), char **argv)
{
	exec_context_t context;

	context.exec_count = 0;
	context.program_name = argv[0];
	context.exit_code = 0;

	signal(SIGINT, handle_signint);

	while (1)
	{
		prompt();
		context.input = get_input(&context);
		if (!context.input)
			break;
		context.args = split_input(&context);

		if (!context.args || !context.args[0])
		{
			free(context.input);
			if (context.args)
				free_array(context.args);
			continue;
		}

		if (strncmp(context.args[0], "exit", 4) == 0)
			builtin_exit(&context);
		else if (strncmp(context.args[0], "env", 3) == 0)
			builtin_env(&context);
		else
			exec_command(&context);

		free_array(context.args);
		free(context.input);
	}
	return (context.exit_code);
}
