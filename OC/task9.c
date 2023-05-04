#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int status;
    int num_children = 6;

    for (int i = 0; i < num_children; i++) {
        pid = fork();

        if (pid < 0) {
            perror("fork");
            return 1;
        }

        if (pid == 0) { // Child process
            if (i == 5) {
                printf("Child %d (PID %d) executing 'ls -l'\n", i + 1, getpid());
                execl("/bin/ls", "ls", "-l", NULL);
                perror("execl");
                exit(1);
            } else {
                printf("Child %d (PID %d) started\n", i + 1, getpid());
                sleep(i + 1);
                printf("Child %d (PID %d) exiting\n", i + 1, getpid());
                exit(0);
            }
        }
    }

    // Parent process: отслеживаем только четные дочерние процессы и процесс 'ls -l'
    for (int i = 0; i < num_children; i++) {
        if (i % 2 == 0 || i == 5) {
            pid = waitpid(-1, &status, 0);
            if (pid > 0) {
                printf("Parent: Child %d exited\n", pid);
            }
        }
    }

    sleep(10); // Задержка перед выводом дерева процессов
    system("ps -xf --forest > file");

    return 0;
}

