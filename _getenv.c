#include "shell.h"

char *_getenv(const char *env_var)
{
	char *key;
	char **env = environ;

	while (*env)
	{
		key = strtok(*env, "=");
		if (key != NULL && strcmp(env_var, key) == 0)
			return (strtok(NULL, "\n"));

		env++;
	}
	return (NULL);
}
