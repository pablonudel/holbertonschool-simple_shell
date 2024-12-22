#include "shell.h"

int main(void)
{
	char *input, **args;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(1, "simple_shell:~$ ", 16);

		input = get_input();
		args = split_input(input);
		command_handler(input, args);
	}
	return (0);
}
