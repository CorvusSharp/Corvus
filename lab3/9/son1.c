#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pid,ppid;
    pid=getpid();
    ppid=getppid();
    printf("SONPARAMS:  pid=%i  ppid=%i\n",pid,ppid);
    sleep(2);
    return 0;
    // exit(1);
    // exit(-1);
}
