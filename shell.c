#include "shell.h"
/**
 * main - 
 *
 * Return: Always 0.
 */
int main(void)
{
	char *buffer = NULL, *cmd, **args;
	size_t buffer_size = 0;
	pid_t pid;
	int status, i;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(1, "#cisfun$ ", 9);

		buffer = get_input(buffer, buffer_size);
		args = split_input(buffer, " \t\n");

		if (args[0] == NULL)
			continue;

		if (strcmp(args[0], "exit") == 0)
		{
			for (i = 0; args[i]; i++)
				free(args[i]);
			free(args);
			exit(EXIT_SUCCESS);
		}

		pid = fork();

		if (pid == -1)
		{
			perror("Error\n");
			exit (1);
		}

		if (pid == 0)
		{
			cmd = get_cmd(args[0]);
			if (execve(cmd, args, environ) == -1)
			{
				printf("Error\n");
				exit(1);
			}
			exit(0);
		}
		else
			wait(&status);

		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args);
	}

	free(buffer);
	return (0);
}
