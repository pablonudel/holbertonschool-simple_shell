
![Header](https://raw.githubusercontent.com/pablonudel/holbertonschool-simple_shell/refs/heads/pablonudel/readme_header.jpg)

# Holberton School - Simple Shell Project

This program, made as a project for Holberton School, creates a basic command-line tool that allows users to interact with the operating system. It enables the execution of a limited set of built-in commands, as well as external programs, both interactively and in non-interactive modes.

This project provides a valuable learning experience in key shell programming concepts like understanding how commands are interpreted and processed, learning how to manage the execution of programs, understanding how the program responds to user input and system signals, and exploring how the program interacts with the operating system.

This basic shell replicates some core functionalities of a standard UNIX shell. It serves as a foundation for understanding the fundamental principles of how shell interpreters work and provides a starting point for exploring more advanced shell features.


## 📋 Project Requirements

Here’s a summarized version of the general requirements for this project:

- All your files will be compiled on Ubuntu 20.04 LTS using [gcc](https://gcc.gnu.org/install/)
- All your files should end with a new line
- Your code should use the [Betty](https://github.com/hs-hq/Betty) style
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- Use system calls only when you need to
## 🚀 Get Started

#### Prerequisites
- A UNIX-like operating system (Linux, macOS, etc.)
- GCC compiler

#### 1. Clone the repository
```
git clone https://github.com/pablonudel/holbertonschool-simple_shell.git
```

#### 2. Navigate to the project directory
```
cd holbertonschool-simple_shell/
```

#### 3. Compile the program
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```


## 👨🏽‍💻 Usage

This simple shell can be used in two modes:

#### Interactive mode
Running the shell program with `./hsh` , it prints a prompt `simple_shell:~$` and waits for user's input to execute the command. To exit the shell `exit` must be typed.

Example:
```
root@ubuntu:/holbertonschool-simple_shell# ./hsh
simple_shell:~$ ls -l
total 276
-rw-r--r-- 1 root root    146 Jan 10 09:53 AUTHORS
-rw-r--r-- 1 root root     17 Jan 10 10:02 README.md
-rw-r--r-- 1 root root   1525 Jan 10 16:30 builtin_cmds.c
-rw-r--r-- 1 root root   1596 Jan 10 11:58 exec_cmd.c
-rwxr-xr-x 1 root root 165296 Jan 10 14:36 hsh
-rw-r--r-- 1 root root   2498 Jan 10 15:45 input_handlers.c
-rw-r--r-- 1 root root   2414 Jan 10 10:11 man_1_simple_shell
-rw-r--r-- 1 root root   1031 Jan 10 18:43 shell.c
-rw-r--r-- 1 root root   1188 Jan 10 17:23 shell.h
-rw-r--r-- 1 root root   2080 Jan 10 11:58 utils.c
simple_shell:~$ exit
root@ubuntu:/holbertonschool-simple_shell#
```

#### Non-Interactive Mode
The shell reads commands from a file or pipe and commands are executed sequentially.

Examples:
```
root@ubuntu:/holbertonschool-simple_shell# cat commands.txt
echo Hello World!
pwd
root@ubuntu:/holbertonschool-simple_shell# ./hsh < commands.txt
Hello World!
/holbertonschool-simple_shell
root@ubuntu:/holbertonschool-simple_shell#
```
```
root@ubuntu:/holbertonschool-simple_shell# echo "echo Hello World!
pwd" | ./hsh
Hello World!
/holbertonschool-simple_shell
root@ubuntu:/holbertonschool-simple_shell#
```
## ⚙️ Built-in Commands

This shell supports the following built-in commands:

| Command | Description                |
| :-------- | :------------------------- |
| `exit` | Exits the shell. Optional usage: `exit <exit code>` |
| `env` | Prints the current environment variables. No options are allowed.|

## ⚠️ Error Handling

The shell implements basic error handling to provide informative messages to the user and appropriate exit codes.

#### Command not found
If an unknown command is entered, the shell displays a message indicating the command was not found with an exit code: `127`

```
./hsh: 1: cmd: not found
```
#### Permission denied
If the shell tries to execute a file that the user does not have permission to execute, it will display a permission denied error with an exit code: `126`

```
./hsh: 1: ./no_permissions: permission denied
```
#### Invalid command argument
If an unknown command option is entered, the shell displays a message indicating the invalid option with an exit code: `2`
```
ls: invalid option -- 'z'
Try 'ls --help' for more information.
```
#### EXIT Built-in command error
If a non number or negative number option is entered, the shell displays a message indicating the illegal number with an exit code: `2`
```
./hsh: 1: exit: Illegal number: -1
- or -
./hsh: 1: exit: Illegal number: arg
```
#### ENV Built-in command error
As the env built-in command is a limited version that not handles any options. If any option is entered, the shell displays a message indicating the invalid option with an exit code: `125`
```
env: invalid option -- '-l'
```

## 👉 Limitations
This simple shell has the following limitations:

- No other built-in commands except: exit and env
- No handling the commands separator ;
- No handling the && and || shell logical operators
- No handling variables replacement
- No handling comments (#)
- No handling complex error outputs
- File as input: this simple shell can take a file as a command line argument, but the feature is not entirely completed.
## 💻 Man Page

Command for execute the Man Page: 

```man ./man_1_simple_shell```

Screenshot:
![Man Page Screenshot](https://raw.githubusercontent.com/pablonudel/holbertonschool-simple_shell/refs/heads/pablonudel/man_page_screenshot.jpg)
## 🔁 Flowchart
![Simple Shell Flowchart](https://raw.githubusercontent.com/pablonudel/holbertonschool-simple_shell/refs/heads/pablonudel/simple_shell-flowchart.jpeg)
## 👥 Authors

Pablo Nudel | [Github](https://github.com/pablonudel)  
Dan Florentin Ishimwe | [Github](https://github.com/danish872)
