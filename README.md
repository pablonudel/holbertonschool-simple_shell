![Logo](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTob-PjCKECdAeaKJ2385YR9AKZhyGR30ngAw&s)


# SIMPLE SHELL - Holberton School


### 📄 Description
**`Simple_shell`** program is a basic shell interpreter written in C. It allows users to execute internal and external commands, handle input and output redirections, and run commands in the background. This project mimics the behavior of a UNIX shell, implementing the fundamentals of process management and system interaction.

### 🪄 Compilation command

```gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format *.c```

### 🔐 Requierments

- Allowed editors: `vi, vim, emacs`

- All your files will be compiled on `Ubuntu 20.04 LTS` using [gcc](https://gcc.gnu.org/install/)

- Your code should use the [Betty style](https://github.com/hs-hq/Betty).

- No more than **5 functions** per file

- The prototypes of all your functions should be included in your header file called ```main.h```


### 🔍 Exemple

`main.c :`
```
#include <stdio.h>
#include "main.h"

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
    char *input;

    /* Start the shell loop */
    while (1)
    {
        /* Display prompt */
        printf("$ ");
        input = get_input();  // Function to get user input
        
        /* Execute the command */
        if (input == NULL)  // Exit condition
            break;
        execute_command(input);  // Function to execute the command
    }

    return (0);
}

```

**Output :**
```
$ ls
file1.txt  file2.txt
$ echo "Hello, Pablo!"
Hello, Pablo!
$ cd /home/user/Documents
$ exit
```

### 📑 Man page

Man commande : `man ./man_1_simple_shell`
![man Simple_Shell](https://ibb.co/2M0kzLc)

### 🔖 Flowchart


![Flowchart](https://ibb.co/Jp9vjS8)
## Authors

- Github : [@pablonudel](https://github.com/pablonudel)
- Github : [@danish872](https://github.com/danish872)
