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
	static char *buffer = NULL, *current = NULL;
	char *result;
	size_t buffer_size = 0;
	char *line, *end;

	if (!current || !*current)
	{
		free(buffer), buffer = NULL, current = NULL;
		if (getline(&buffer, &buffer_size, stdin) == -1)
		{
			if (isatty(STDIN_FILENO)) putchar('\n');
			free(buffer), buffer = NULL;
			return (NULL);
		}
		current = buffer;
	}

	line = current;
	while (*current && *current != '\n') current++;
	if (*current == '\n') *current++ = '\0';

	while (*line == ' ' || *line == '\t') line++;
	for (end = line + strlen(line) - 1; 
			end > line && (*end == ' ' || *end == '\t'); end--)
		*end = '\0';

	if (*line == '\0') return (current = NULL, get_input(context));

	result = strdup(line);
	if (!result)
	{
		print_error(context, 1);
		free(buffer), buffer = NULL;
		exit(context->exit_code);
	}
	return (result);
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
	int i = 0;

	if (!context->input || *(context->input) == '\0')
		return (NULL);

	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
	{
		print_error(context, 1);
		exit(context->exit_code);
	}

	token = strtok(context->input, " \t\n");
	while (token)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			free_array(tokens);
			free(tokens);
			print_error(context, 1);
			exit(context->exit_code);
		}
		token = strtok(NULL, " \t\n");
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
