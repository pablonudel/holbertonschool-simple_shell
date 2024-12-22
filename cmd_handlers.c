#include "shell.h"

void command_handler(char *input, char **args)
{
	if (!args)
	{
		free(input);
		return;
	}

	if (!args[0])
		return;

	if (strcmp(args[0], "exit") == 0)
		builtin_exit(input, args);
	else if (strcmp(args[0], "env") == 0)
		builtin_env(args);
	else
		exec_cmd(input, args);

	free_array(args);
	free(input);
	return;
}

char *get_cmd(char *arg)
{
	char *var = _getenv("PATH"), *tmp_var, *token, *full_path;
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

void exec_cmd(char *input, char **args)
{
	char *command;
	pid_t pid;
	int status;

	command = get_cmd(args[0]);
	if (!command)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		free(command);
		free(input);
		free_array(args);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{   
		if (execve(command, args, environ) == -1)
		{
			perror("Error");
			free(command);
			free(input);
			free_array(args);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);    
	free(command);
	return;
}
