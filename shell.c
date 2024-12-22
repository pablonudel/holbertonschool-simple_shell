#include "shell.h"

int main(void)
{
	char *input, **args, *command;
	pid_t pid;
	int status;
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(1, "#cisfun$ ", 9);

		input = get_input();
		args = split_input(input);

		if (!args)
		{
			free(input);
			continue;
		}

		if (!args[0])
			continue;

		if (strcmp(args[0], "exit") == 0)
		{
			free(input);
			for (i = 0; args[i]; i++)
				free(args[i]);
			free(args);
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(args[0], "env") == 0)
		{
			if (args[1])
			{
				perror("Error no env args");
				free(input);
				for (i = 0; args[i]; i++)
					free(args[i]);
				free(args);
				continue;
			}
			print_env();
		}
		else
		{
			command = get_cmd(args[0]);
			if (!command)
			{
				fprintf(stderr, "%s: command not found\n", args[0]);
				free(input);
				for (i = 0; args[i]; i++)
					free(args[i]);
				free(args);
				continue;
			}

			pid = fork();

			if (pid == -1)
			{
				perror("Error en pid padre");
			}
			if (pid == 0)
			{   
				if (execve(command, args, environ) == -1)
				{
					perror("Error en pid hijo");
					for (i = 0; args[i]; i++)
						free(args[i]);
					free(args);
					exit(EXIT_FAILURE);
				}
			}
			else
				wait(&status);
			
			free(command);
		}


		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args);
		free(input);
	}
	return (0);
}
