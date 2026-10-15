# pipex

> Reproduces the shell pipeline `< infile cmd1 | cmd2 > outfile` in C.

## What it does
Runs two commands connected by a pipe, resolving them through `PATH`, with input/output redirected to files.

## What I learned
- `pipe`, `fork`, `dup2`, `execve`, `waitpid`
- Parsing `PATH` from the environment and error handling

## Tech stack
C, Make, libft

## Build & run
```bash
make
./pipex infile "ls -l" "wc -l" outfile
# equivalent to: < infile ls -l | wc -l > outfile
```

## Structure
`pipex.c`, `pipex_utils.c`, `pipex.h`, `libft/`.

---
*Built at 42 Madrid by jgomez-d (Jorge Gomez De Oliveira).*
