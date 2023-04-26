#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int i, status;

    for (i = 0; i < 2; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("ошибка fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            int j;
            printf("Дочерний процесс %d запущен\n", getpid());

            for (j = 0; j < 5; j++) {
                printf("Дочерний процесс %d выполняет итерацию %d\n", getpid(), j);
                system("ps -o pid,ppid,stat,time,cmd");
                sleep(1);
            }

            exit(getpid());
        }
    }

    for (i = 0; i < 2; i++) {
        wait(&status);
        printf("Дочерний процесс %d завершился\n", WEXITSTATUS(status));
    }

    printf("Оба дочерних процесса завершились\n");

    return 0;
}

