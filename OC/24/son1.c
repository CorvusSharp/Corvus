#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>

int main() {
    struct sched_param shdprm; // Значения параметров планирования
    int i, pid, ppid;
    pid = getpid();
    int k = 0;
    ppid = getppid();
    int schedule = sched_getscheduler(0);
    switch (schedule) {
        printf("SCHED_FIFO\n");
        break;
        case SCHED_RR:
            for (int i = 0; i < 100000000; i++) {
                k += 1;
            }
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
    return 0;
}
