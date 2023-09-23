This project revolves around a straightforward shell program,created by Frank Ikoro Almond, designed for user interaction through a command-line interface.

#The Simple Shell offers the following functionalities:

Command Execution: It supports the execution of both built-in commands and external commands available in the system's PATH.

Built-in Commands: The shell provides various built-in commands, including exit, env, cd, setenv, unsetenv, help, history, and alias, to facilitate basic system interactions.

Command Chaining: It enables command chaining using logical AND (&&) and logical OR (||) operators.

History Management: The shell maintains a command history, allowing users to access and replay previously executed commands.

Alias Management: Users can create and use command aliases for the convenient execution of frequently used commands.

Environment Variable Manipulation: The shell offers capabilities to view, set, and unset environment variables.

#Getting Started
To run the Simple Shell program, follow these steps:

Clone the repository: git clone <repository_url>
Navigate to the project directory: cd simple-shell
Compile the source files: gcc -o shell *.c
Run the shell program: ./shell
You can interact with the shell by entering commands and pressing Enter. Utilize built-in commands like "help" to access more information about available features.

#Usage
The shell supports both interactive and non-interactive modes. In interactive mode, you can directly input commands into the shell's prompt. In non-interactive mode, you can provide a script file as an argument to execute a sequence of commands.

#Examples:
Interactive mode: ./shell
Non-interactive mode: ./shell script.sh

#Contributing
Contributions to the Simple Shell project are encouraged! If you encounter issues, have suggestions for enhancements, or wish to introduce new features, please don't hesitate to open an issue or submit a pull request.

#License
This project licensed by MIT License.
