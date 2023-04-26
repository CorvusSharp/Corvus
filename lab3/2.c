#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>



int main() {
    int pid;
    int n = 0;
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    for(int i = 0; i<30; i++) {
        if (pid == 0) {
            /*здесь размещаются вычисления, выполняемые процессом-потомком */
			printf("ПОТОМОК: new pid = %d, ppid = %d\nТекущее значение %d\n\n\n", getpid(),getppid(), n); 
			++n;
				
        } else {
            
			printf("РОДИТЕЛЬ: parent pid = %d, ppid = %d\nТекущее значение %d\n\n\n", getpid(),getppid(), n ); 
            /*здесь размещаются вычисления, выполняемые порождающим процессом */
			--n;
            
        }
    }
    printf("Завершение процесса\n");
    exit(1);

    return 0;
}
