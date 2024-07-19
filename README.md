![minishell](https://github.com/user-attachments/assets/04f758fc-c120-4e36-8f90-1e36a9b68fff)



# **minishell**
As beautiful as a shell

## **Project overview**
The **minishell** project is an essential part of the **42 curriculum**.
It tasks students with creating a simple shell, similar to bash.
This project aims to improve understanding of processes, file descriptors, and the intricacies of shell programming in C.

#### **Objective**
- **Create a Shell**: Implement a functional shell that can execute commands, handle pipes, redirections, and more.
- **Builtin Commands**: Implement built-in commands such as `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Signal Handling**: Ensure proper handling of signals like `ctrl-C`, `ctrl-D`, and `ctrl-\`.
- **History Management**: Maintain a working command history.
- **Bonus Features**: Implement logical operators `&&` and `||`, wildcard expansion using `*`, and support for parentheses for command grouping.

#### **Key features**
- **Prompt Display**: The shell displays a prompt when waiting for a new command.
- **Command Execution**: The shell searches for and launches the right executable based on the `PATH` variable or using a relative or absolute path.
- **Quotes Handling**: Properly handle single (`'`) and double (`"`) quotes, preventing interpretation of metacharacters within the quoted sequence.
- **Redirections**: Support for input (`<`), output (`>`), append (`>>`), and heredoc (`<<`) redirections.
- **Pipes**: Implement the pipe (`|`) functionality to connect commands.
- **Environment Variables**: Handle environment variables and special variables like `$?` and `$$` (which returns the PID).
- **Advanced Command Handling**: Support for logical operators `&&` and `||`, and wildcard expansion with `*`.
- **External Thread for Monitoring**: Use an external thread to monitor the state of the shell and ensure proper handling of commands and processes.

#### **Compiling the Project**
The **minishell** project includes a Makefile for easy compilation. Simply run:
```
make
```
This will generate the `minishell` executable.

#### **Running the Project**
To start the shell, run:
```
./minishell
```
Then you are ready to experience a fantastic shell. Enjoy!

#### **Challenges and Achievements**
- **Complex Command Parsing**: Parsing commands with various combinations of quotes, redirections, and pipes was particularly challenging.
- **Signal Handling**: Ensuring correct behavior for `ctrl-C`, `ctrl-D`, and `ctrl-\` required careful handling of signals.
- **Memory Management**: Managing memory efficiently to prevent leaks, especially with the readline function, was a significant task.
- **Builtin Commands**: Implementing builtins with proper handling of options and arguments.
- **Bonus Features**: Adding support for logical operators `&&` and `||`, wildcards, and proper handling of parentheses for command grouping.

#### **Project Details**
- **Philosopher States**: Philosophers can be in one of three states: eating, thinking, or sleeping. They need two forks to eat and release the forks after eating.
- **Synchronization**: Mutexes are used to ensure that no two philosophers can hold the same fork at the same time.
- **State Monitoring**: An external thread monitors the state of philosophers and logs state changes. This thread ensures that no philosopher starves.

#### 🛠 **Skills**
- C
- Concurrency
- Thread management
- Mutex synchronization

#
💬 **Ask Me About:**
- Anything you need related to this project! If you find any errors, please let me know as I am always open to new challenges and improving my code.

#
📫 **How to Reach Me:**
- **42 Students:** Contact me on Slack (smontuor)
- **Others:** Email me at smontuor@student.42firenze.it
