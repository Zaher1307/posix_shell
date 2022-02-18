#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "shell_command_line.h"
#include "helper_wrapper_functions.h"
#include "jobs.h"

extern int nextjid;
extern char **environ;
extern struct job_t jobs[MAXJOBS]; /* The job list */

/* 
 * eval - Evaluate the command line that the user has just typed in
 * 
 * If the user has requested a built-in command (quit, jobs, bg or fg)
 * then execute it immediately. Otherwise, fork a child process and
 * run the job in the context of the child. If the job is running in
 * the foreground, wait for it to terminate and then return.  Note:
 * each child process must have a unique process group ID so that our
 * background children don't receive SIGINT (SIGTSTP) from the kernel
 * when we type ctrl-c (ctrl-z) at the keyboard.  
*/
void eval(char *cmdline) {
    char *argv[MAXARGS];
    char buf[MAXLINE];
    int bg;
    pid_t pid;
    pid_t jid = nextjid;
    sigset_t mask_all, prev_mask;
    sigfillset(&mask_all);

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    
    if (argv[0] == NULL) {
        return;
    }

    if (!builtin_cmd(argv)) {
        if ((pid = fork()) == 0) {
            setpgid(0, 0);
            if (execve(argv[0], argv, environ) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }
        

        sigprocmask(SIG_BLOCK, &mask_all, &prev_mask);
        if (!bg) {
            addjob(jobs, pid, FG, cmdline);
        } else {
            printf("[%d] (%d) %s", jid, pid, cmdline);
            addjob(jobs, pid, BG, cmdline);
        }
        sigprocmask(SIG_SETMASK, &prev_mask, NULL);
        
        if (!bg) {
            waitfg(pid);
        }
    }

}


/* 
 * builtin_cmd - If the user has typed a built-in command then execute
 *    it immediately.  
 */
int builtin_cmd(char **argv) {
    if (!strcmp(argv[0], "quit")) {
        exit(0);
    } else if (!strcmp(argv[0], "jobs")) {
        listjobs(jobs);
        return 1;
    } else if (!strcmp(argv[0], "bg") || !strcmp(argv[0], "fg")) {
        do_bgfg(argv);
        return 1;
    }
    return 0;     /* not a builtin command */
}

/* 
 * do_bgfg - Execute the builtin bg and fg commands
 */
void do_bgfg(char **argv) {
    int id, bg, jidflag = 0;
    pid_t pid = -1, jid = -1;
    struct job_t *job;
    sigset_t mask_all, prev_mask;

    sigfillset(&mask_all);

    if (argv[1] == NULL) {
        printf("%s: command requires PID or %%jobid argument\n", argv[0]);
        return;
    } else if (argv[2] != NULL) {
        printf("Too many arguments.\n");
        return;
    }

    if (argv[1][0] == '%') {
        jidflag = 1;
        id = strtol((argv[1] + 1), NULL, 10);
    } else {
        id = strtol(argv[1], NULL, 10);
    }

    if (id < 1) {
        printf("%s: argument must be a PID or %%jobid\n", argv[0]);
        return;
    }

    bg = strcmp(argv[0], "bg") == 0;

    sigprocmask(SIG_BLOCK, &mask_all, &prev_mask);
    if (jidflag) {
        jid = id;
        job = getjobjid(jobs, jid);
        if (!job) {
            printf("%%%d: No such job\n", jid);
            sigprocmask(SIG_SETMASK, &prev_mask, NULL);
            return;
        } else {
            pid = job->pid;
        }
    } else {
        pid = id;
        job = getjobpid(jobs, pid);
        if (!job) {
            printf("(%d): No such process\n", pid);
            sigprocmask(SIG_SETMASK, &prev_mask, NULL);
            return;
        } else {
            jid = job->jid;
        }
    }
    sigprocmask(SIG_SETMASK, &prev_mask, NULL);

    if (bg) {
        printf("[%d] (%d) %s", jid, pid, job->cmdline);
        kill(-pid, SIGCONT);
        sigprocmask(SIG_BLOCK, &mask_all, &prev_mask);
        job->state = BG; 
        sigprocmask(SIG_SETMASK, &prev_mask, NULL);
    } else {
        sigprocmask(SIG_BLOCK, &mask_all, &prev_mask);
        job->state = FG; 
        sigprocmask(SIG_SETMASK, &prev_mask, NULL);
        kill(-pid, SIGCONT);
        waitfg(pid);
    }

}

/* 
 * waitfg - Block until process pid is no longer the foreground process
 */
void waitfg(pid_t pid) {
    pid_t jid;
    int job_state = -1;
    sigset_t mask_all, prev_mask;
    sigfillset(&mask_all);
    do {
        sigprocmask(SIG_BLOCK, &mask_all, &prev_mask);
        jid = pid2jid(pid);
        struct job_t *job = getjobjid(jobs, jid);
        if (job) {
            job_state = job->state; 
        }
        sigprocmask(SIG_SETMASK, &prev_mask, NULL);
    } while (jid && job_state != ST && job_state != -1);
}

