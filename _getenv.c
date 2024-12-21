#include "shell.h"

char *_getenv(const char *env_var)
{
	char *key;
	char *value;
	char **env = environ;

	while (*env)
	{
		key = *env;
		value = strchr(key, '=');

		if (value != NULL)
		{
			*value = '\0';

			if (strcmp(env_var, key) == 0)
				return (value + 1);

			*value = '=';
		}
		env++;
	}
	return (NULL);
}
