#include "shell.h"

char *get_input(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t n_chars;

	n_chars = getline(&input, &input_size, stdin);
	if (n_chars == -1)
	{
		if (feof(stdin))
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("Error");
			free(input);
			exit(EXIT_FAILURE);
		}
	}

	return (input);
}

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
		perror("Error");
		return (NULL);
	}

	token = strtok(input, " \t\n");
	while (token)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			free_array(tokens);			
			perror("Error");
			return (NULL);
		}
		token = strtok(NULL, " \t\n");
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
