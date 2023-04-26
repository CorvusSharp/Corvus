#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sched.h>

void perform_computation() {
    // Perform some computation
}

int main() {
    pid_t pid1, pid2;
    int status;

    // Create two child processes with the same priority level
    pid1 = fork();
    if (pid1 == 0) { // child process 1
        // Assign Round-Robin scheduling procedure
        sched_rr();
        // Perform some computation
        perform_computation();
        exit(0);
    }
    else {
        pid2 = fork();
        if (pid2 == 0) { // child process 2
            // Assign First-Come-First-Serve scheduling procedure
            sched_fifo();
            // Perform some computation
            perform_computation();
            exit(0);
        }
        else { // parent process
            // Wait for both child processes to finish
            waitpid(pid1, &status, 0);
            waitpid(pid2, &status, 0);
        }
    }

    return 0;
}

