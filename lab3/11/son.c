#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <time.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
    printf("SONPARAMS:  pid=%i  ppid=%i\n",getpid(),getppid());


    return 0;
}
