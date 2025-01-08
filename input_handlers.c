#include "shell.h"

/**
 * read_user_input - Reads user input into the context buffer
 * @context: Pointer to the execution context
 *
 * Return: Pointer to the updated buffer or NULL if EOF
 */
static char *read_user_input(exec_context_t *context)
{
	size_t buffer_size = 0;

	free(context->buffer);
	context->buffer = NULL;

	if (getline(&context->buffer, &buffer_size, stdin) == -1)
	{
		if (isatty(STDIN_FILENO))
			putchar('\n');
		free(context->buffer);
		context->buffer = NULL;
		return (NULL);
	}

	return (context->buffer);
}

/**
 * trim_whitespace - Removes leading and trailing whitespace from a string
 * @line: Pointer to the string to trim
 *
 * Return: Pointer to the trimmed string
 */
static char *trim_whitespace(char *line)
{
	char *end;

	while (*line == ' ' || *line == '\t')
		line++;

	if (*line == '\0') /* String is empty */
		return (line);

	end = line + strlen(line) - 1;
	while (end > line && (*end == ' ' || *end == '\t'))
		*end-- = '\0';

	return (line);
}

/**
 * get_input - Processes user input, trims it, and handles recursion if empty
 * @context: Pointer to the execution context
 *
 * Return: Pointer to the processed input string
 */
char *get_input(exec_context_t *context)
{
	static char *current;
	char *result;
	char *line;

	if (!current || !*current)
	{
		current = read_user_input(context);
		if (!current)
			return (NULL);
	}

	line = current;
	while (*current && *current != '\n')
		current++;
	if (*current == '\n')
		*current++ = '\0';

	line = trim_whitespace(line);

	if (*line == '\0')
	{
		current = NULL;
		return (get_input(context));
	}

	result = strdup(line);
	if (!result)
	{
		print_error(context, 1);
		free(context->buffer);
		context->buffer = NULL;
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
