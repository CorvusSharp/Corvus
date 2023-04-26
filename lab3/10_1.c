#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 == 0) {
        // Этот код выполняется в первом дочернем процессе
        printf("Child 1: PID=%d\n", getpid());

        pid2 = fork();

        if (pid2 == 0) {
            // Этот код выполняется во втором дочернем процессе
            printf("Child 2: PID=%d\n", getpid());
        }
    } else {
        // Этот код выполняется в родительском процессе
        printf("Parent: PID=%d, Child 1 PID=%d\n", getpid(), pid1);
    }

    return 0;
}
