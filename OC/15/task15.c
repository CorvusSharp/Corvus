#include <signal.h>
#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>

int main() {
    int pr, pid, i;
    pid = getpid();

    for (i = -10; i < 1; i++) {
        setpriority(PRIO_PROCESS, pid, i);
        pr = getpriority(PRIO_PROCESS, pid);

        if (pr != i) {
            continue;
        } else {
            printf("Нижняя граница = %d\n", pr);
            printf("Запросили %d, получили %d\n", i, pr);
            break;
        }
    }

    for (i = 1; i < 10; i++) {
        setpriority(PRIO_PROCESS, pid, i);
        pr = getpriority(PRIO_PROCESS, pid);

        if (pr != i) {
            continue;
        } else {
            printf("Верхняя граница = %d\n", pr+10);
            printf("Запросили %d, получили %d\n", pr+10, pr+9);
            break;
        }
    }

    return 0;
}
