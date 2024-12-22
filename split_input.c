#include "shell.h"

char **split_input(char *input)
{
	char **tokens;
	char *token;
	int i = 0;

	if (!input)
		return (NULL);

	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
	{
		fprintf(stderr, "Error: Memory allocation error\n");
		return (NULL);
	}

	token = strtok(input, " \t\n");
	while (token)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			for (i = 0; tokens[i]; i++)
				free(tokens[i]);
			free(tokens);
			fprintf(stderr, "Error: Memory allocation error\n");
			return (NULL);
		}
		token = strtok(NULL, " \t\n");
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
