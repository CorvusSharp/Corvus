#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pid;
    int n = 1;
    pid = fork();
    printf("Текущее число: %d\n", n);
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0) 
    {
        printf("child pid = %d, ppid = %d\n", getpid(), getppid() );
        n *= 10;
        printf("Текущее число: %d\n", n);
    } else
    {
        printf("parent pid = %d, ppid = %d\n", getpid(), getppid() ); 
        n += 13;
        printf("Текущее число: %d\n", n);
    }
    printf("Завершение процесса\n");
    exit(1);


    return 0;
}
