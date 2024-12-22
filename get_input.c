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
