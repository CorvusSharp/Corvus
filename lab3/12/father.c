#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void itoa(char *buf, int value) {
   sprintf(buf, "%d", value);
}

int main(void) {
   int pid, ppid, status;
   int fdrd, fdwr;
   char str1[10], str2[10];
   struct sched_param shdprm;
   if (mlockall(MCL_CURRENT | MCL_FUTURE) < 0)
       perror("mlockall error");
   pid = getpid();
   ppid = getppid();
   shdprm.sched_priority = 1;
   if (sched_setscheduler(0, SCHED_FIFO, &shdprm) == -1)
       perror("SCHED_SETSCHEDULER_1");
   if ((fdrd = open("infile.txt", O_RDONLY)) == -1)
perror("Opening file");
   if ((fdwr = creat("outfile.txt", 0666)) == -1)
       perror("Creating file");
   itoa(str1,fdrd);
   itoa(str2,fdwr);
   for (int i = 0; i < 2; i++) {
       if (fork() == 0) {
           shdprm.sched_priority = 50;
           if (sched_setscheduler(0, SCHED_FIFO, &shdprm) == -1)
               perror("SCHED_SETSCHEDULER_1");
           execl("son", "son", str1, str2, NULL);
       }
   }
   system("ps -o uid,gid,ruid,pid,ppid,pgid,tty,vsz,stat,command");
   if (close(fdrd) != 0)
       perror("Closing file");
   for (int i = 0; i < 2; i++)
       printf("Process pid = %d completed\n", wait(&status));
	return 0;
}
