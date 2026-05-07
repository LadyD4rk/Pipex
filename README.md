*This project has been created as part of the 42 curriculum by jobraga.*

# pipex

## Description

pipex is a C program that replicates the behavior of the Unix shell pipe operator (`|`), developed as part of the 42 school curriculum. It takes an input file, two shell commands, and an output file as arguments, and executes the commands in sequence — redirecting the output of the first into the input of the second, exactly as the shell would with:

```sh
< infile cmd1 | cmd2 > outfile
```

The project introduces **Unix process management** (`fork`, `execve`, `waitpid`), **inter-process communication** via `pipe`, and **file descriptor redirection** with `dup2` — core concepts for systems programming that underpin how every shell pipeline works.

## Instructions

### Requirements

- A C compiler (`cc`) with the flags `-Wall -Werror -Wextra -g`
- `make` utility

### Compilation

```bash
git clone https://github.com/jobraga/pipex.git
cd pipex
make
```

This produces the `pipex` executable.

### Usage

```bash
./pipex infile "cmd1" "cmd2" outfile
```

**Example:**

```bash
./pipex input.txt "grep hello" "wc -l" output.txt
# Equivalent to: < input.txt grep hello | wc -l > output.txt
```

### Error handling

pipex handles and reports the following situations without crashing: invalid or unreadable input file, unwritable output file, command not found (exit 127), command without execute permission (exit 126), and invalid number of arguments.

All error messages are written to `stderr` using the bundled `ft_printf_error` library.

### Cleanup

```bash
make clean    # removes object files
make fclean   # removes object files and the executable
make re       # full recompile
```

## Algorithm

The core execution model is built around three Unix primitives working together: `pipe`, `fork`, and `execve`.

**`pipe(fd)`** creates two linked file descriptors — `fd[1]` for writing and `fd[0]` for reading. Anything written into `fd[1]` by the first child can be read from `fd[0]` by the second child, forming the inter-process channel.

**Two child processes** are created with `fork`. Each child uses `dup2` to rewire its standard file descriptors before calling `execve`:

- **Child 1** (`child_process_one`): opens the input file, redirects it to `stdin` (`dup2(file1, STDIN_FILENO)`), and redirects `fd[1]` to `stdout` (`dup2(fd[1], STDOUT_FILENO)`). It then executes `cmd1`, whose output flows into the pipe.
- **Child 2** (`child_process_two`): opens the output file, redirects `fd[0]` to `stdin` (`dup2(fd[0], STDIN_FILENO)`), and redirects the output file to `stdout` (`dup2(file2, STDOUT_FILENO)`). It then executes `cmd2`, which reads from the pipe and writes to the output file.

After forking both children, **the parent closes both ends of the pipe** — this is critical: if the parent holds `fd[1]` open, `cmd2` will never receive EOF and will block indefinitely.

**Command resolution** (`path_to_create`) searches the `PATH` environment variable to find the full path of each command. The `PATH=` entry is located in `envp` using `ft_env_line`, then split on `:` with `ft_split`, and each directory is tested with `access(path, F_OK | X_OK)` until a valid executable is found.

**Exit code propagation**: the parent uses `waitpid` to collect the exit status of the second child specifically, and returns it — matching the behavior of the shell, where the exit code of a pipeline is the exit code of its last command.

The overall data flow:

```
infile → [child 1: cmd1] → pipe → [child 2: cmd2] → outfile
```

## Resources

- [Linux man page — pipe(2)](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [Linux man page — fork(2)](https://man7.org/linux/man-pages/man2/fork.2.html)
- [Linux man page — execve(2)](https://man7.org/linux/man-pages/man2/execve.2.html)
- [Linux man page — dup2(2)](https://man7.org/linux/man-pages/man2/dup2.2.html)
- [Linux man page — waitpid(2)](https://man7.org/linux/man-pages/man2/waitpid.2.html)
- [42 Docs — pipex subject](https://harm-smits.github.io/42docs/projects/pipex)

**AI usage:** Claude (claude.ai) was used to help write and structure this README based on the project's source files and the 42 subject requirements. No code was generated or modified with AI assistance.