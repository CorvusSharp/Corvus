#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    struct sched_param shdprm; // значения параметров планирования 
	int pid,ppid, status;
    int n = 60;
    int prior = 10;
    char *arr[6] = {"son1", "son2", "son3", "son4", "son5", "son6"};
    int pid_son[6];
    pid = getpid();
    ppid = getppid();
    printf("FATHER PARAMS: pid=%i ppid=%i\n", pid, ppid);
    shdprm.sched_priority = n;
    if (sched_setscheduler(0, SCHED_FIFO, &shdprm) == -1) {
        perror("SCHED_FIFO");
    }

    for (int i = 0; i < 6; i++) {
        if ((pid_son[i] = fork()) == 0) {
            shdprm.sched_priority = prior;
            if (sched_setscheduler(pid_son[i], SCHED_FIFO, &shdprm) == -1)
                perror("SCHED_FIFO");
            execl(arr[i], arr[i], NULL);
        }
    }
    for (int i = 0; i < 6; i++) {
        printf("Процесс с pid = %d завершен\n", wait(&status));
    }
    return 0;
}

