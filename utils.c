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

			if (strncmp(env_var, key, strlen(key)) == 0)
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
	int i = 0;

	while (array[i])
	{
		free(array[i]);
		i++;
	}

	free(array);
}
