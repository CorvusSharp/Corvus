#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int i, pid[4], ppid, status, result;
    pid[0]=getpid();
    ppid=getppid();
    printf("FATHER PARAMS: pid=%i  ppid=%i\n", pid[0],ppid);
    if((pid[1] = fork()) == 0)
        execl("son1", "son1", NULL);
    if((pid[2] = fork()) == 0)
        execl("son2", "son2", NULL);
    if((pid[3] = fork()) == 0)
        execl("son3", "son3", NULL);
    system("ps xf > file.txt");
    for (i = 1; i < 4; i++)
    {
        result = waitpid(pid[i], &status, WUNTRACED);
        printf("%d) Child proccess with pid = %d is finished with status %d\n", i, result, status);
    }

    return 0;
}

