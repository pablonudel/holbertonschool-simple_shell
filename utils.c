#include "shell.h"

void prompt(void)
{
	if (isatty(STDIN_FILENO) == 1)
		write(1, "simple_shell:~$ ", 16);
}

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

void free_array(char **array)
{
	int i;

	for (i = 0; array[i]; i++)
		free(array[i]);
	free(array);
}
