# Minishell - 42

*This project was created as part of the 42 curriculum by **aleconst** and **alejandj**.*

## 📝 Description

**Minishell** is a project that consists of creating a basic shell, a command-line interface that acts as an intermediary between the user and the operating system. The main goal is to replicate the basic behavior of **Bash**, allowing the user to interact with the system through a robust and functional command-line interface.

### ⚙️ Main features
* **Interactive prompt:** Displays a prompt ready to receive commands.
* **Binary execution:** Searches for and executes programs using the `PATH` environment variable or specific paths.
* **Built-ins:** Custom implementation of essential commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
* **Pipelines (`|`):** Redirects the output of one command to the input of the next.
* **Redirections:** Input/output handling using `<`, `>`, `>>`, and the `<<` (here-doc) mode.
* **Environment variables:** Management and expansion of variables (including `$?` for the exit status).
* **Signals:** Proper handling of interrupts such as `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`.

---

## 🚀 Instructions

### 📋 Prerequisites
The project uses the **GNU Readline** library. Make sure it is installed on your system (on Debian/Ubuntu-based systems, install it as follows):

```bash
sudo apt-get install libreadline-dev
```

### 🛠️ Build and Installation
1. #### Clone this repository:
```bash
git clone https://github.com/AlejandroJimenez16/MiniShell.git
```

2. #### Compile the project using Makefile:
```bash
make
```

### ⌨️ Execution
Once the binary is compiled, you can start the shell by running:
```bash
./minishell
```
To exit the shell, you can use the *`exit`* command or press *`Ctrl-D`*.

---

## 📚 Resources
### 📒 References
The following sources were consulted during the development of this project:

* [GNU Bash Manual](https://www.gnu.org/software/bash/manual/): Main reference for replicating standard behavior.

* [Man pages (Linux Programmer's Manual)](https://www.man7.org/linux/man-pages/man1/man.1.html): Technical documentation for key functions such as `fork`, `execve`, `waitpid`, `pipe`, `dup2` and `signal`.

### 🤖 Use of Artificial Intelligence (AI)
During the development of this project, Artificial Intelligence was used in the following ways:

* **Memory debugging**: AI was used to analyze complex Valgrind traces and identify the source of memory leaks.
* **Test case generation**: AI was used to generate test cases, including edge cases, unusual token combinations, and invalid syntax to ensure the robustness of the code.
---
