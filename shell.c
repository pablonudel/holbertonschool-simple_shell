#include "shell.h"

/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	char *input, **args;

	while (1)
	{
		prompt();
		input = get_input();
		args = split_input(input);
		command_handler(input, args);
	}
	return (0);
}
