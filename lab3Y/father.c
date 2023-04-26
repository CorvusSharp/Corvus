#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Дочерний процесс
        execl("son.out", "son.out", NULL);
       system("ps -xf");
 perror("execl");
        exit(EXIT_FAILURE);
    } else if (pid > 0) { // Родительский процесс
        wait(NULL); // Ожидание завершения дочернего процесса
        printf("Дочерний процесс завершился\n");

        // Получение информации о процессах
        system("ps -xf");
        printf("Информация о процессах сохранена в файле processes.txt\n");
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}

