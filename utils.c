#include "shell.h"

/**
 * prompt - Print the shell prompt if interactive
 *
 * Return: void
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO) == 1)
	{
		write(STDOUT_FILENO, "simple_shell:~$ ", 16);
		fflush(stdout);
	}
}

/**
 * handle_signint - Signal handler for SIGINT.
 *
 * @sig: The signal number received.
 *
 * Return: void
 */
void handle_signint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nsimple_shell:~$ ", 17);
}

/**
 * _getenv - Get the value of an environment variable
 *
 * @env_var: The environment variable
 *
 * Return: The value of the variable, or NULL if not found
 */
char *_getenv(const char *env_var)
{
	size_t len = strlen(env_var);
	char **env = environ;

	while (*env)
	{
		if (strncmp(*env, env_var, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);

		env++;
	}
	return (NULL);
}

/**
 * free_array - Frees an array of strings
 *
 * @array: The array of strings
 *
 * Return void
 */
void free_array(char **array)
{
	int i = 0;

	if (!array)
		return;

	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}

	free(array);
	array = NULL;
}

/**
 * print_error - print error according to exit codes
 *
 * @context: Pointer to the execution context containing data and state
 * @code: exit code
 *
 * Return void
 */
void print_error(exec_context_t *context, int code)
{
	if (code == 127)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
				context->program_name, context->exec_count, context->args[0]);
	}
	else if (code == 125)
	{
		fprintf(stderr, "%s: invalid option -- '%s'\n",
				context->args[0], context->args[1]);
	}
	else if (code == 3)
	{
		fprintf(stderr, "%s: %d: %s: too many arguments\n",
				context->program_name, context->exec_count,
				context->args[0]);
	}
	else if (code == 2)
	{
		fprintf(stderr, "%s: %d: %s: Illegal number: %s\n",
				context->program_name, context->exec_count,
				context->args[0], context->args[1]);
	}
	else
	{
		fprintf(stderr, "%s: %d: %s: No such file or directory\n",
				context->program_name, context->exec_count,
				context->args[0]);
	}

	context->exit_code = code;
}
