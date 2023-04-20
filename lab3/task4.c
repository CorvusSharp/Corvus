#include <stdio.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc, char* argv[])
{
int n = 0;
struct sched_param shdprm;
shdprm.sched_priority = 1;
if (sched_setscheduler(0, SCHED_FIFO, &shdprm) == -1) {
perror("SCHED_SETSCHEDULER");
}
char command_fifo[100];
sprintf(command_fifo, "chrt -p %d", getpid());
system(command_fifo);
int pid = fork();
if(pid == -1)
{
perror("fork error");
exit(1);
}
for(int i=0; i < 10; i++)
{
if (pid == 0)
{
printf("SON: new pid = %d, ppid = %d \nValue n: %d\n", getpid(), getppid(), n);
n += 1;
}
else
{
printf("PARENT: pid = %d, ppid = %d \nValue n: %d\n", getpid(), getppid(), n);
n -= 1;
}
}
printf("Программа завершена\n");
exit(1);
}
