#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Запущен дочерний процесс с PID: %d\n", getpid());

    // Здесь может быть выполнена какая-либо задача
    sleep(5);

    printf("Дочерний процесс завершается\n");
    return 0;
}

