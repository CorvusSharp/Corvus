#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int i;
    pid = fork(); // создаем процесс-потомок
    if (pid == -1) {
        perror("ошибка fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // код процесса-потомка
        printf("Дочерний процесс %d запущен.\n", getpid());
        for (i = 0; i < 10; i++) {
            printf("Дочерний процесс %d выполняет итерацию %d.\n", getpid(), i);
            sleep(1); // замедляем выполнение цикла на 1 секунду
        }
        exit(EXIT_SUCCESS);
    } else {
        // код родительского процесса
        printf("Родительский процесс %d запущен.\n", getpid());
        for (i = 0; i < 10; i++) {
            printf("Родительский процесс %d выполняет итерацию %d.\n", getpid(), i);
            sleep(1); // замедляем выполнение цикла на 1 секунду
        }
        wait(NULL); // ожидаем завершения процесса-потомка
        printf("Родительский процесс %d завершен.\n", getpid());
        exit(EXIT_SUCCESS);
    }
}

