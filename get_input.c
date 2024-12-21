#include "shell.h"

char *get_input(char *buffer, size_t buffer_size)
{
	ssize_t n_chars;

	n_chars = getline(&buffer, &buffer_size, stdin);
	if (n_chars == -1)
	{
		if (feof(stdin))
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}

	return (buffer);
}
