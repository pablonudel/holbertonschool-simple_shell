#include "main.h"
/**
 * main - simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
    char *buf = NULL, *args[2];
    size_t buf_size = 0;
    int status, n_chars = 0;
    pid_t pid;

    while (1)
    {
        write(1, "#cisfun$ ", 9);
        n_chars = getline(&buf, &buf_size, stdin);
        if (n_chars == -1)
        {
            write(1, "\n", 1);
            free(buf);
            exit(0);
        }

        args[0] = strtok(buf, " \t\n");
        if (args[0] == NULL)
            continue;

        args[1] = NULL;

        if (strtok(NULL, " \t\n") != NULL)
        {
            write(2, "Error: Invalid argument(s) provided\n", 36);
            continue;
        }

        pid = fork();

        if (pid == -1)
        {
            perror("Error");
            free(buf);
            return (1);
        }

        if (pid == 0)
        {
            if (execve(args[0], args, environ) == -1)
            {
                perror("Error");
                free(buf);
                exit(1);
            }
            exit(0);
        }
        else
            wait(&status);
    }

    free(buf);
    return (0);
}
