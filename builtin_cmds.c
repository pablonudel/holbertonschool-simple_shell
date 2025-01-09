#include "shell.h"
#include <ctype.h>

/**
 * string_to_int - check if a string is a positive number
 *
 * @str: the string to check
 *
 * Return: the positive number or -1
 */
int string_to_int(const char *str) {
	
	int result = 0;

	if (*str == '-')
	{
		return (-1);
	}

	while (*str != '\0') {
		if (*str >= '0' && *str <= '9')
		{
			result = result * 10 + (*str - '0');
		}
		else
		{
			return (-1);
		}
		str++;
	}

	return (result);
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

	context->exec_count += 1;
	if (context->args[1])
	{
		context->exit_code = string_to_int(context->args[1]);

		if (context->exit_code == -1)
		{
			print_error(context, 2);
			free_array(context->args);
			context->args = NULL;
			free(context->input);
			context->input = NULL;
			return;
		}
	}

	signal(SIGINT, SIG_DFL);
	free(context->input);
	context->input = NULL;
	free_array(context->args);
	context->args = NULL;

	if (context->buffer != NULL)
	{
		free(context->buffer);
		context->buffer = NULL;
	}
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
