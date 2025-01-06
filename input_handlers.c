#include "shell.h"

/**
 * get_input - Allocate the input line of user
 *
 * Return: String with user's input, or exits if error
 */
char *get_input(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t n_chars;
	int i;

	n_chars = getline(&input, &input_size, stdin);
	if (n_chars == EOF)
	{
		free(input);
		if (isatty(STDIN_FILENO))
			putchar('\n');
		exit(EXIT_SUCCESS);
	}
	if (n_chars == -1)
	{
		perror("hsh: Error");
		free(input);
		exit(EXIT_FAILURE);
	}

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\n')
		{
			input[i] = '\0';
			break;
		}
		i++;
	}

	return (input);
}

/**
 * split_input - Splits the input
 *
 * @input: The input string to be split
 *
 * Return: An array of strings, or NULL if error
 */
char **split_input(char *input)
{
	char **tokens;
	char *token;
	int i = 0;

	if (!input)
		return (NULL);

	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
		return (NULL);

	token = strtok(input, " \t\n");
	while (token)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			free_array(tokens);
			return (NULL);
		}
		token = strtok(NULL, " \t\n");
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
