#include <stdio.h> #include <sched.h> #include <sys/mman.h> #include <stdlib.h> #include <unistd.h> #include <fcntl.h> #include <sys/wait.h>

void itoa(char *buf, int value) { sprintf(buf, "%d", value);
}

int main(void) {
    int pid, ppid, status; int fdrd, fdwr;
    char str1[10], str2[10]; struct sched_param shdprm;
    if (mlockall(MCL_CURRENT | MCL_FUTURE) < 0) perror("mlockall error");
    pid = getpid(); ppid = getppid();
    shdprm.sched_priority = 1;
    if (sched_setscheduler(0, SCHED_RR, &shdprm) == -1) perror("SCHED_SETSCHEDULER_1");
    if ((fdrd = open("infile.txt", O_RDONLY)) == -1) perror("Opening file");
    if ((fdwr = creat("outfile.txt", 0666)) == -1) perror("Creating file");
    itoa(str1, fdrd); itoa(str2, fdwr);
    for (int i = 0; i < 2; i++) { if (fork() == 0) {
            shdprm.sched_priority = 50;
            if (sched_setscheduler(0, SCHED_RR, &shdprm) == -1) perror("SCHED_SETSCHEDULER_1");
            execl("son", "son", str1, str2, NULL); }}
    if (close(fdrd) != 0) perror("Closing file");
    for (int i = 0; i < 2; i++)
    printf("Process pid = %d completed\n", wait(&status));
    return 0; }


#include <sched.h> #include <sys/mman.h> #include <fcntl.h> #include <stdio.h> #include <stdlib.h> #include <unistd.h>

int main(int argc, char *argv[]) {
    if (mlockall(MCL_CURRENT | MCL_FUTURE) < 0) perror("mlockall error");

    char c;
    int pid, ppid;
    int fdrd = atoi(argv[1]); int fdwr = atoi(argv[2]); pid = getpid();
    ppid = getppid();
    printf("son file descriptor = %d\n", fdrd); printf("son params: pid=%i ppid=%i\n", pid, ppid);

    sleep(5);

    for (;;) {
        if (read(fdrd, &c, 1) != 1) return 0;
        write(fdwr, &c, 1);
        printf("pid = %d: %c\n", pid, c); }

    return 0; }
