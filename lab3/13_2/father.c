#include <signal.h>
#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){
	int pid1, pid2, pid3;
	pid1 = fork();
	if (pid1 == 0)
		execl("son1", "son1", NULL);
	pid2 = fork();
        if (pid2 == 0)
                execl("son2", "son2", NULL);
	printf("father running\n");
	system("ps");
	kill(pid1, SIGUSR1);
	kill(pid2, SIGUSR1);
	time_t st_t;
	st_t = time(NULL);
	printf("signals sended at time %s\n", ctime(&st_t));
	sleep(2);
	system("ps");
}
