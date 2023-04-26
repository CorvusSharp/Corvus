#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int sig) {
    printf("Signal received: %d\n", sig);
}

int main() {
    pid_t pid;

    // Установить обработчик сигнала
    signal(SIGUSR1, signal_handler);

    // Создать новый процесс-потомок
    pid = fork();

    if (pid == 0) { // Дочерний процесс
        printf("Child process ID: %d\n", getpid());

        // Дочерний процесс засыпает на 3 секунды
        sleep(3);

        // Дочерний процесс отправляет сигнал родительскому процессу
        kill(getppid(), SIGUSR1);

        exit(0);
    }
    else if (pid > 0) { // Родительский процесс
        printf("Parent process ID: %d\n", getpid());

        // Родительский процесс засыпает на 5 секунд
        sleep(5);

        printf("Parent process completed\n");

        exit(0);
    }
    else { // Ошибка при создании дочернего процесса
        perror("fork() failed");
        exit(1);
    }
}
