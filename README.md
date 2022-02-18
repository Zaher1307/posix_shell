# Tiny Shell


## Description
- A simple Unix shell that supports jobs control.
- The shell works through three main task: (1): **parse** the command to extract the executable name and the command-line options. (2): **execute** the command by creating a child process then run it. (3): **reap** the processes after terminating.
- It's the 5th lab of [15-213: Introduction to Computer Systems](https://www.cs.cmu.edu/afs/cs.cmu.edu/academic/class/15213-f15/www/index.html).
- You can read the specifications with this [writeup](https://github.com/Zaher1307/tiny-shell/blob/main/shlab.pdf).

## How to use it?
First use the following commands to run the shell:
- `git clone https://github.com/Zaher1307/tiny-shell`
- `make`
- `./tsh`

Tiny-shell supports mainly four built-in commands as follows:
- `quit`: terminate the shell.
- `jobs`: list all running background jobs.
- `bg <job>`: continue the `<job>` in *background*. The arguemnt `<job>` can be either a ***PID*** or ***JID***.
- `fg <job>`: continue the `<job>` in *forground*. The arguemnt `<job>` can be either a ***PID*** or ***JID***.

The shell can be used to run any other command by typing the absolute path of its executable, for instance, the following example runs the **echo** command:
- `tsh> /bin/echo "hello, world!"`

***note:*** tiny-shell doesn't support *pagers*.

## How to test it?
- `tests` contain trace files provided with lab-handouts.
- Run each trace on tshref and tsh then compare the outputs.

For example, you can run trace `trace14` on tsh by using the following command:
```
make test14
```

You can run `trace14` also on tshref by using the following command:
```
make rtest14
```

## Source:
- `job.c`: contains the data structure that keeps track of the created jobs and store its data.
- `signal_handlers.c`: contains the implementation of the customized signal handlers.
- `helper_wrapper_functions.c`: contains wrappers and helpers for the used system calls.
- `shell_command_line.c`: contains the functions that parse and evaluate the commands.
- `sdriver.pl`: program used to run the traces on my shell.
- `tshref`: reference tsh program provided with lab-hanouts to compare tsh outputs with.
