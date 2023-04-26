#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc,char* argv[])
{
    int m,n,pid;
    m=5000;
    n=1;
    pid=fork();
    if (pid==-1) {
        perror("forkerror");
        exit(1);
    }
    printf("pid=%i\n",pid);
    if(pid!=0)
    {
        int j;
        for(j=1;j<=1000;j++)
        {
            m-=1;
        } 
        printf("родитель:%i\n\n",m);
    } 
    else
    {
        int i;
        for(i=1;i<=1000;i++)
        {
            n+=1;
        }
        printf("потомок:%d\n\n",n);
    }
    
    printf("Программа завершена\n");

    exit(1);

    return 0;
}
