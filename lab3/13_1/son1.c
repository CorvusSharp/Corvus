#include <stdio.h>
#include <unistd.h>


int main(){
	int pid,ppid;
	pid=getpid();
	ppid=getppid();
	printf("SON_1 PARAMS:  pid=%i  ppid=%i\nFather creates andwaits\n",pid,ppid);
	sleep(1);

    return 0;
}
