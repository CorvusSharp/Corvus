#include <signal.h>
#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
 signal(SIGUSR1, SIG_IGN);
 sleep(5);
}
