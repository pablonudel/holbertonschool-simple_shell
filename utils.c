#include "shell.h"

/**
 * prompt - Print the shell prompt if interactive
 *
 * Return: void
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO) == 1)
		write(1, "simple_shell:~$ ", 16);
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
	char *key;
	char *value;
	char **env = environ;

	while (*env)
	{
		key = *env;
		value = strchr(key, '=');

		if (value)
		{
			*value = '\0';

			if (strcmp(env_var, key) == 0)
			{
				*value = '=';
				return (value + 1);
			}

			*value = '=';
		}
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
	int i;

	for (i = 0; array[i]; i++)
		free(array[i]);
	free(array);
}
