#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
void main(){
    int pid,ppid;
    pid=getpid();
    ppid=getppid();
    printf("SON_1 PARAMS: pid=%i ppid=%i\nFather creates and waits\n",pid,ppid);
    sleep(3);
}
