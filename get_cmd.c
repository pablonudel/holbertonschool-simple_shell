#include "shell.h"

char *get_cmd(char *arg)
{
	char *var = _getenv("PATH");
	char *tmp_var;
	char *token;
	char *full_path;
	struct stat st;

	if (!var)
		return (NULL);

	if (access(arg, X_OK) == 0)
	{
		full_path = strdup(arg);
		if (!full_path)
			return (NULL);
		return (full_path);
	}

	tmp_var = strdup(var);
	if (!tmp_var)
		return (NULL);

	token = strtok(tmp_var, ":");
	while (token)
	{
		full_path = malloc(strlen(token) + strlen(arg) + 2);
		if (!full_path)
		{
			free(tmp_var);
			return (NULL);
		}

		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, arg);

		if (stat(full_path, &st) == 0 && access(full_path, X_OK) == 0)
		{
			free(tmp_var);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}
	free(tmp_var);
	return (NULL);
}
