#include "shell.h"

/**
 * free_context_resources - Frees all resources in the context
 *
 * @context: Pointer to the execution context
 *
 * Return: void
 */
void free_context_resources(exec_context_t *context)
{
	if (context->args != NULL)
	{
		free_array(context->args);
		context->args = NULL;
	}

	if (context->input != NULL)
	{
		free(context->input);
		context->input = NULL;
	}

	if (context->buffer != NULL)
	{
		free(context->buffer);
		context->buffer = NULL;
	}
}

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
	if (context->args[2] != NULL)
	{
		print_error(context, 3);
		free_context_resources(context);
		return;
	}
	if (context->args[1])
	{
		context->exit_code = strtol(context->args[1], &endptr, 10);

		if (*endptr || context->exit_code < 0)
		{
			print_error(context, 2);
			free_context_resources(context);
			return;
		}
	}

	signal(SIGINT, SIG_DFL);
	free_context_resources(context);

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
