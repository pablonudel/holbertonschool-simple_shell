#include "shell.h"

/**
 * get_cmd - Finds the full path of a command
 *
 * @arg: The command name
 *
 * Return: Full path of the command or NULL if not found
 */
char *get_cmd(char *arg)
{
	char *path = _getenv("PATH"), *tmp_path, *token, *full_path;
	struct stat st;

	if (!path)
		return (NULL);
	if (access(arg, X_OK) == 0)
		return (strdup(arg));
	tmp_path = strdup(path);
	if (!tmp_path)
		return (NULL);

	token = strtok(tmp_path, ":");
	while (token)
	{
		full_path = malloc(strlen(token) + strlen(arg) + 2);
		if (!full_path)
			break;

		sprintf(full_path, "%s/%s", token, arg);
		if (stat(full_path, &st) == 0)
		{
			if (access(full_path, X_OK) != 0)
				fprintf(stderr, "hsh: %s: permission denied\n", arg);
			else
			{
				free(tmp_path);
				return (full_path);
			}
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(tmp_path);
	return (NULL);
}

/**
 * exec_cmd - Executes an external command
 *
 * @args: Array of arguments
 *
 * Return: void
 */
void exec_cmd(char **args)
{
	char *command;
	pid_t pid;
	int status;

	command = get_cmd(args[0]);
	if (!command)
	{
		fprintf(stderr, "hsh: %s: command not found\n", args[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("hsh: Error");
		free(command);
		return;
	}
	if (pid == 0)
	{
		if (execve(command, args, environ) == -1)
		{
			perror("hsh: Error");
			free(command);
			return;
		}
	}
	else
		wait(&status);
	free(command);
}
