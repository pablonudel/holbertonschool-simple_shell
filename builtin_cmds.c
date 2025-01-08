#include "shell.h"

/**
 * builtin_exit - Exits the shell
 *
 * @context: Pointer to the execution context containing data and state
 *
 * Return: void
 */
void builtin_exit(exec_context_t *context)
{
	char *endptr;

	context->exec_count += 1;
	if (context->args[1])
	{
		context->exit_code = strtol(context->args[1], &endptr, 10);

		if (*endptr || context->exit_code < 0)
		{
			print_error(context, 2);
			return;
		}
	}

	signal(SIGINT, SIG_DFL);
	free(context->input);
	free_array(context->args);
	exit(context->exit_code);
}

/**
 * builtin_env - Prints the current environment variables
 *
 * @context: Pointer to the execution context containing data and state
 *
 * Return: void
 */
void builtin_env(exec_context_t *context)
{
	char **env = environ;

	context->exec_count += 1;
	if (context->args[1])
	{
		print_error(context, 125);
		return;
	}

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
