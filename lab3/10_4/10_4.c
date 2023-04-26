#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>

void perform_computation() {
    for (int i = 0; i < 1000000000; ++i) 
        2 + 2;
}

int main() {
    pid_t pid1, pid2;
    int status;
    struct timespec start_time, end_time;
    double elapsed_time;

    // Create two child processes with the same priority level
    pid1 = fork();
    if (pid1 == 0) { // child process 1
        // Assign Round-Robin scheduling procedure
        struct sched_param param1 = {.sched_priority = 1};
        sched_setscheduler(0, SCHED_RR, &param1);
        // Perform some computation
        clock_gettime(CLOCK_MONOTONIC, &start_time);
        perform_computation();
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
        printf("Child process 1 execution time: %.6f seconds\n", elapsed_time);
        exit(0);
    }
    else {
        pid2 = fork();
        if (pid2 == 0) { // child process 2
            // Assign First-Come-First-Serve scheduling procedure
            struct sched_param param2 = {.sched_priority = 1};
            sched_setscheduler(0, SCHED_FIFO, &param2);
            // Perform some computation
            clock_gettime(CLOCK_MONOTONIC, &start_time);
            perform_computation();
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
            printf("Child process 2 execution time: %.6f seconds\n", elapsed_time);
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

