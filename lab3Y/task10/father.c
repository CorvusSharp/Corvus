#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    struct sched_param shdprm; // Значения параметров планирования
    int pid, pid1, pid2, ppid;
    pid = getpid();
    ppid = getppid();
    printf("FATHER PARAMS: pid=%i ppid=%i\n", pid, ppid);
    shdprm.sched_priority = 50;
    // Устанавливаем политику планирования и значение приоритета в 50
    if (sched_setscheduler(0, SCHED_RR, &shdprm) == -1) {
        perror("SCHED_SETSCHEDULER");
    }// Выводим сообщение об ошибке, если sched_setscheduler() вернула -1
    // Создаем два дочерних процесса
    if ((pid1 = fork()) == 0)
        execl("s1", "s1", NULL);
    // Запускаем исполняемый файл son1 в первом дочернем процессе
    if ((pid2 = fork()) == 0)
        execl("s2", "s2", NULL);
    // Запускаем исполняемый файл son2 во втором дочернем процессе
    // Выводим текущую политику планирования и значение приоритета текущегo    процесса
            printf("Текущая политика планирования для текущего процесса: ");
    switch (sched_getscheduler(0)) {
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
        case -1:
            perror("SCHED_GETSCHEDULER");
            break;
        default:
            printf("Неизвестная политика планирования\n");
    }
    if (sched_getparam(0, &shdprm) == 0)
        printf("Текущий приоритет текущего процесса: %d\n",
               shdprm.sched_priority);
    else
        perror("SCHED_GETPARAM");
    // Выводим сообщение об ошибке, если sched_getparam() вернула -1
    return 0;
}

