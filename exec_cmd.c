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
	char *path, *tmp_path, *token, full_path[1024];
	struct stat st;

	if (strchr(arg, '/'))
	{
		if (stat(arg, &st) == 0)
		{
			if (access(arg, X_OK) != 0)
				errno = EACCES;
			else
				return (strdup(arg));
		}
		else
			errno = ENOENT;

		return (NULL);
	}
	path = _getenv("PATH");

	if (!path)
		return (NULL);

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
 * @context: Pointer to the execution context containing data and state
 *
 * Return: void
 */
void exec_command(exec_context_t *context)
{
	char *command = get_cmd(context->args[0]);
	pid_t pid;

	context->exec_count += 1;
	if (!command)
	{
		if (errno == ENOENT)
			print_error(context, 127);
		else
			print_error(context, 126);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		print_error(context, 1);
		exit(context->exit_code);
	}
	else if (pid == 0)
	{
		if (execve(command, context->args, environ) == -1)
		{
			print_error(context, 1);
			exit(context->exit_code);
		}
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}

	free(command);
}
