#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    pid = fork(); // создаем процесс-потомок
    if (pid == -1) {
        perror("ошибка fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // код процесса-потомка
        printf("Дочерний процесс %d запущен.\n", getpid());
        execlp("ls", "ls", NULL); // исполняем команду ls
        perror("ошибка exec"); // если execlp вернула ошибку
        exit(EXIT_FAILURE);
    } else {
        // код родительского процесса
        printf("Родительский процесс %d запущен.\n", getpid());
        wait(NULL); // ожидаем завершения процесса-потомка
        printf("Родительский процесс %d завершен.\n", getpid());
        exit(EXIT_SUCCESS);
    }
}

