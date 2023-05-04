#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROC_AMOUNT 12

int main() {
    int i;
    char *program = "son1";
    struct sched_param params;
    int sched;
    for (i = 0; i < PROC_AMOUNT; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Ошибка при создании дочернего процесса\n");
            return 1;
        } else if (pid == 0) {
            sched = (i % 2 == 0) ? SCHED_FIFO : SCHED_RR;
            params.sched_priority = sched_get_priority_max(sched);
            if (sched_setscheduler(0, sched, &params) < 0) {
                printf("Ошибка при установке политики планирования\n");
                return 1;
            }
            execl(program, program, NULL);
            printf("Ошибка при вызове функции execl\n");
            return 1;
        }
    }
    for (int i = 0; i < PROC_AMOUNT; i++) {
        int status;
        pid_t pid = wait(&status);
        if (pid < 0) {
            printf("Ошибка при вызове функции wait\n");
            return 1;
        }
    }
    return 0;
}

