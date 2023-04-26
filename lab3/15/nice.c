
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
int main() {
    int pid = getpid();
    int priority = getpriority(PRIO_PROCESS, pid);
    printf("Priority is %d\n", priority);
    nice(1000);
    priority = getpriority(PRIO_PROCESS, pid);
    printf("New priority is %d\n", priority);
    nice(1);
    priority = getpriority(PRIO_PROCESS, pid);
    printf("New priority is %d\n", priority);
    nice(-1);
    priority = getpriority(PRIO_PROCESS, pid);
    printf("New priority is %d\n", priority);
    nice(-18);
    priority = getpriority(PRIO_PROCESS, pid);
    printf("New priority is %d\n", priority);
    nice(-20);
    priority = getpriority(PRIO_PROCESS, pid);
    printf("New priority is %d\n", priority);
    return 0;
}