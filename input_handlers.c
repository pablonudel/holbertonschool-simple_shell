#include "shell.h"

/**
 * get_input - Allocate the input line of user
 *
 * @context: Pointer to the execution context containing data and state
 *
 * Return: String with user's input, or exits if error
 */
char *get_input(exec_context_t *context)
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
		return (NULL);
	}
	if (n_chars == -1)
	{
		print_error(context, 1);
		exit(context->exit_code);
	}

	if (n_chars > 0 && input[n_chars - 1] == '\n')
		input[n_chars - 1] = '\0';

	i = n_chars - 2;
	while (i >= 0 && (input[i] == ' ' || input[i] == '\t'))
	{
		input[i] = '\0';
		i--;
	}

	if (input[0] == '\0')
	{
		free(input);
		context->exit_code = 1;
		return (NULL);
	}

	return (input);
}

/**
 * split_input - Splits the input
 *
 * @context: Pointer to the execution context containing data and state
 *
 * Return: An array of strings, or NULL if error
 */
char **split_input(exec_context_t *context)
{
	char **tokens;
	char *token;
	char *line;
	int i = 0;

	if (!context->input || *(context->input) == '\0')
		return (NULL);

	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
	{
		print_error(context, 1);
		exit(context->exit_code);
	}

	line = strtok(context->input, "\n");
	while (line)
	{
		token = strtok(line, " \t");
		while (token)
		{
			tokens[i] = strdup(token);
			if (!tokens[i])
			{
				free_array(tokens);
				print_error(context, 1);
				exit(context->exit_code);
			}
			token = strtok(NULL, " \t");
			i++;
		}
		line = strtok(NULL, "\n");
	}

	tokens[i] = NULL;
	return (tokens);
}
