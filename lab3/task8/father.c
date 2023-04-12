#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void run_child(const char *exec_func) {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) { // Child process
        execl("./son.out", "son.out", exec_func, (char *)NULL);
        perror("execl");
        _exit(1);
    } else { // Parent process
        wait(&status);
        printf("Parent: Child process with %s terminated with status %d\n", exec_func, WEXITSTATUS(status));
    }
}

int main() {
    const char *exec_funcs[] = {"execl", "execlp", "execle", "execv", "execvp", "execvpe", NULL};

    printf("Running 'ps' before starting child processes:\n");
    system("ps -aux | grep father.out");
    printf("\n");

    for (int i = 0; exec_funcs[i] != NULL; i++) {
        run_child(exec_funcs[i]);
    }

    printf("\nRunning 'ps' after all child processes terminated:\n");
    system("ps -aux | grep father.out");

    return 0;
}

