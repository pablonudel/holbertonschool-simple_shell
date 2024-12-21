#include "shell.h"

char **split_input(char *buffer, char *del)
{
	char **tokens;
	char *token;
	int i = 0;

	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
	{
		fprintf(stderr, "Error: Memory allocation error\n");
		exit(1);
	}
	token = strtok(buffer, del);
	while (token)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, del);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
