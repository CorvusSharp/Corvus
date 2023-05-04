#include <signal.h>
#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid1, pid2, pid3;
    int status;
    pid1 = fork();
    if (pid1 == 0)
        execl("son1", "son1", NULL);
    pid2 = fork();
    if (pid2 == 0)
        execl("son2", "son2", NULL);
    pid3 = fork();
    if (pid3 == 0)
        execl("son3", "son3", NULL);
    system("echo before signal sent");
    system("ps -l");
    kill(pid1, SIGUSR1);
    kill(pid2, SIGUSR1);
    kill(pid3, SIGUSR1);
    waitpid(pid1, &status, WNOHANG);
    waitpid(pid2, &status, WNOHANG);
    waitpid(pid3, &status, WNOHANG);
    system("echo after signal sent");
    system("ps -l");
    return 0;
}
