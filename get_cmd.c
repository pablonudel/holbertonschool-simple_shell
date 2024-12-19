#include "shell.h"

char *get_cmd(char *cmd)
{
	char *path = _getenv("PATH");
	char *token;
	char *cmd_full;
	struct stat st;

	token = strtok(path, ":");
	while (token)
	{
		cmd_full = malloc(strlen(token) + strlen(cmd) + 2);
		if (!cmd_full)
		{
			perror("Error");
			exit(1);
		}
		strcpy(cmd_full, token);
		strcat(cmd_full, "/");
		strcat(cmd_full, cmd);
		if (stat(cmd_full, &st) == 0)
			return (cmd_full);
		free(cmd_full);
		token = strtok(NULL, ":");
	}

	return (cmd);
}
