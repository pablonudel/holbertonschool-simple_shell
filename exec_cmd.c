#include "shell.h"

/**
 * check_cmd - checks if command exist, is a directory and
 * has permissions, and set errno errors
 *
 * @arg: The command name
 *
 * Return: 1 if true 0 if false
 */
int check_cmd(char *arg)
{
	if (stat(arg, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			errno = EISDIR;
		else if (access(arg, X_OK) != 0)
			errno = EACCES;
		else
			return (1);
	}
	else
	{
		errno = ENOENT;
	}
	return (0);
}

/**
 * get_cmd - Finds the full path of a command
 *
 * @arg: The command name
 *
 * Return: Full path of the command or NULL if not found
 */
char *get_cmd(char *arg)
{
	char *path, *tmp_path, *token, full_path[1024];
	struct stat st;

	if (strchr(arg, '/'))
	{
		if (check_cmd(arg) == 1)
			return (strdup(arg));
		else
			return (NULL);
	}

	path = _getenv("PATH");
	if (!path)
	{
		errno = ENOENT;
		return (NULL);
	}

	tmp_path = strdup(path);
	token = strtok(tmp_path, ":");

	while (token)
	{
		sprintf(full_path, "%s/%s", token, arg);
		if (stat(full_path, &st) == 0 && access(full_path, X_OK) == 0)
		{
			free(tmp_path);
			return (strdup(full_path));
		}
		token = strtok(NULL, ":");
	}
	free(tmp_path);
	return (NULL);
}

/**
 * exec_command - Executes an external command
 *
 * @args: Array of arguments
 *
 * Return: void
 */
void exec_command(char **args)
{
	char *command = get_cmd(args[0]);
	pid_t pid;

	if (!command)
	{
		perror("./hsh");
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("./hsh");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(command, args, environ) == -1)
		{
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}

	free(command);
}
