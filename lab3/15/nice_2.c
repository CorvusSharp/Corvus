#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
void main()
{
    int priority, pid, i;
    pid=getpid();
    for (i = -100; i < 1; i++)
    {
        setpriority(PRIO_PROCESS, pid, i);
        priority = getpriority(PRIO_PROCESS, pid);
        if (priority != i) continue;
        else
        {
            printf("Нижняя граница = %d\n", priority);
            printf("Запросили %d, получили %d\n", i, priority);
            break;
        }
    }
    for (i = 1; i < 100; i++)
    {
        setpriority(PRIO_PROCESS, pid, i);
        priority = getpriority(PRIO_PROCESS, pid);
        if (priority == i) continue;
        else
        {
            printf("Верхняя граница = %d\n", priority);
            printf("Запросили %d, получили %d\n", i, priority);
            break;
        }
    }
}