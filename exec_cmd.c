#include "shell.h"

/**
 * get_cmd - Finds the full path of a command
 *
 * @arg: The command name
 * @error: error status
 *
 * Return: Full path of the command or NULL if not found
 */
char *get_cmd(char *arg, int *error)
{
	char *path = _getenv("PATH"), *tmp_path, *token, *full_path;
	struct stat st;
	*error = 0;

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
				*error = 1;
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
 * @exec_count: command execution counter
 * @prog_name: program name
 *
 * Return: void
 */
void exec_cmd(char **args, int *exec_count, char *prog_name)
{
	char *command;
	pid_t pid;
	int status, error;

	*exec_count += 1;
	command = get_cmd(args[0], &error);
	if (!command)
	{
		if (error)
			fprintf(stderr, "%s: %d: %s: permission denied\n",
					prog_name, *exec_count, args[0]);
		else
			fprintf(stderr, "%s: %d: %s: not found\n",
					prog_name, *exec_count, args[0]);
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
