#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

#include "signal_handlers.h"
#include "jobs.h"

extern struct job_t jobs[MAXJOBS]; /* The job list */

/*****************
 * Signal handlers
 *****************/

/* 
 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
 *     available zombie children, but doesn't wait for any other
 *     currently running children to terminate.  
 */
void sigchld_handler(int sig) {
    int prev_errno = errno;

    pid_t pid, jid;
    sigset_t mask_all, prev_mask;
    int status;

    sigfillset(&mask_all);
    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0) {
        sigprocmask(SIG_BLOCK, &mask_all, &prev_mask);
        jid = pid2jid(pid);
        if (WIFEXITED(status)) {
            deletejob(jobs, pid);
        } else if (WIFSIGNALED(status)) {
            deletejob(jobs, pid);
            printf("Job [%d] (%d) terminated by signal %d\n", jid, pid, WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            struct job_t *job = getjobpid(jobs, pid);
            job->state = ST;
            printf("Job [%d] (%d) stopped by signal %d\n", jid, pid, WSTOPSIG(status));
        }

        sigprocmask(SIG_SETMASK, &prev_mask, NULL);        
    }

        errno = prev_errno;
}

/* 
 * sigint_handler - The kernel sends a SIGINT to the shell whenver the
 *    user types ctrl-c at the keyboard.  Catch it and send it along
 *    to the foreground job.  
 */
void sigint_handler(int sig) {
    int prev_errno = errno;
    
    sigset_t mask_all, prev_mask;
    sigfillset(&mask_all);
    sigprocmask(SIG_BLOCK, &mask_all, &prev_mask);
    kill(-fgpid(jobs), SIGINT);
    sigprocmask(SIG_SETMASK, &prev_mask, NULL);

    errno = prev_errno;
}

/*
 * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *     the user types ctrl-z at the keyboard. Catch it and suspend the
 *     foreground job by sending it a SIGTSTP.  
 */
void sigtstp_handler(int sig) {
     int prev_errno = errno;
    
    sigset_t mask_all, prev_mask;
    sigfillset(&mask_all);
    sigprocmask(SIG_BLOCK, &mask_all, &prev_mask);
    kill(-fgpid(jobs), SIGTSTP);
    sigprocmask(SIG_SETMASK, &prev_mask, NULL);

    errno = prev_errno;   
}

/*********************
 * End signal handlers
 *********************/

