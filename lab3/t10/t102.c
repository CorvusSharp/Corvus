#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

int main() {
    pid_t pid1, pid2;
    int i;

    // создаем первый процесс-потомок
    pid1 = fork();
    if (pid1 == -1) {
        perror("ошибка fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // код первого процесса-потомка
        printf("Первый процесс %d запущен.\n", getpid());
        for (i = 0; i < 10; i++) {
            printf("Первый процесс %d выполняет итерацию %d.\n", getpid(), i);
            sleep(1);
        }
        exit(EXIT_SUCCESS);
    } else {
        // создаем второй процесс-потомок
        pid2 = fork();
        if (pid2 == -1) {
            perror("ошибка fork");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            // код второго процесса-потомка
            printf("Второй процесс %d запущен.\n", getpid());
            for (i = 0; i < 10; i++) {
                printf("Второй процесс %d выполняет итерацию %d.\n", getpid(), i);
                sleep(1);
            }
            exit(EXIT_SUCCESS);
        } else {
            // код родительского процесса
            printf("Родительский процесс %d запущен.\n", getpid());

            // задаем процедуру планирования SCHED_DEADLINE для второго процесса
            struct sched_attr attr;
            memset(&attr, 0, sizeof(attr));
            attr.size = sizeof(attr);
            attr.sched_policy = SCHED_DEADLINE;
            attr.sched_runtime = 10000000; /* 10 миллисекунд */
            attr.sched_deadline = attr.sched_runtime + 5000000; /* 5 миллисекунд */
            attr.sched_period = attr.sched_deadline + 5000000; /* 5 миллисекунд */
            int ret = sched_setattr(pid2, &attr, 0);
            if (ret == -1) {
                perror("ошибка sched_setattr");
                exit(EXIT_FAILURE);
            }
            printf("Второй процесс %d использует алгоритм SCHED_DEADLINE.\n", pid2);
            system("ps -xf");
           

    if (pid2 == -1) {
        perror("ошибка fork");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        // код второго процесса-потомка
        printf("Второй процесс %d запущен.\n", getpid());
        for (i = 0; i < 10; i++) {
            printf("Второй процесс %d выполняет итерацию %d.\n", getpid(), i);
            sleep(1);
        }
        exit(EXIT_SUCCESS);
    } else {
        // код родительского процесса
        printf("Родительский процесс %d запущен.\n", getpid());
        struct sched_param params;
        params.sched_priority = 0;

        // задаем процедуру планирования SCHED_FIFO для первого процесса
        sched_setscheduler(pid1, SCHED_FIFO, &params);
        printf("Первый процесс %d использует алгоритм FIFO.\n", pid1);
        system("ps -xf");
        char command1[100];
        sprintf(command1, "chrt -p %d", pid1);
        system(command1);
        sleep(5);

        // изменяем процедуру планирования на SCHED_DEADLINE для второго процесса
        struct sched_attr attr;
        memset(&attr, 0, sizeof(attr));
        attr.size = sizeof(struct sched_attr);
        attr.sched_policy = SCHED_DEADLINE;
        attr.sched_runtime = 1000000;
        attr.sched_deadline = 2000000;
        attr.sched_period = 3000000;
        sched_setattr(pid2, &attr, 0);
        printf("Второй процесс %d использует алгоритм Deadline.\n", pid2);
        system("ps -xf");
        char command2[100];
        sprintf(command2, "chrt -p %d", pid2);
        system(command2);
        sleep(5);

        // ожидаем завершения обоих дочерних процессов
        for (i = 0; i < 2; i++) {
            wait(NULL);
        }

        printf("Оба дочерних процесса завершились.\n");

        return 0;
    }
}

