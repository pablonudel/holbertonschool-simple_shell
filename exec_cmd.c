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

	if (strchr(arg, '/'))
	{
		if (stat(arg, &st) == 0 && access(arg, X_OK) == 0)
			return (strdup(arg));
		return (NULL);
	}
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
		if (stat(full_path, &st) == 0 && access(full_path, X_OK) == 0)
		{
			free(tmp_path);
			return (full_path);
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
	char *command, **env = environ;
	pid_t pid;
	int status;

	*exec_count += 1;
	command = get_cmd(args[0]);
	if (!command)
	{
		fprintf(stderr, "%s: %d: %s: %s\n",
				prog_name, *exec_count, args[0], strerror(errno));
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		fprintf(stderr, "%s: %d: fork: %s\n",
				prog_name, *exec_count, strerror(errno));
		free(command);
		return;
	}
	if (pid == 0)
	{
		if (execve(command, args, env) == -1)
		{
			fprintf(stderr, "%s: %d: %s: %s\n",
					prog_name, *exec_count, command, strerror(errno));
			free(command);
			return;
		}
	}
	else
		wait(&status);
	free(command);
}
