#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Ошибка при создании процесса-потомка\n");
        exit(1);
    } else if (pid == 0) {
	printf("Дочерний процесс с PID: %d\n",getpid());
	execlp ("./son", "son", NULL);
        system("ps -xf --foreset > file");
    } else {
	system("ps -xf --forest > file");
        waitpid(pid, NULL, 0);
        printf("Программа завершена\n");
    }
    return 0;
}

