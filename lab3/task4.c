#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>

int main() {
pid_t pid;
int i;
pid = fork(); // создаем процесс-потомок
if (pid == -1) {
perror("ошибка fork");
exit(EXIT_FAILURE);
} else if (pid == 0) {
// код процесса-потомока
printf("Дочерний процесс %d запущен.\n", getpid());
for (i = 0; i < 10; i++) {
printf("Дочерний процесс %d выполняет итерацию %d.\n", getpid(), i);
sleep(1); // замедляем выполнение цикла на 1 секунду
}
exit(EXIT_SUCCESS);
} else {
// код родительского процесса
printf("Родительский процесс %d запущен.\n", getpid());
struct sched_param params;
params.sched_priority = 0;
    // Round Robin
    sched_setscheduler(0, SCHED_RR, &params);
    printf("Родительский процесс %d использует алгоритм Round Robin.\n", getpid());
   
 system("ps -xf");
    sleep(5);
printf("Родительский процесс %d использует алгоритм RR.\n", getpid());
    // FIFO
    sched_setscheduler(0, SCHED_FIFO, &params);
    printf("Родительский процесс %d использует алгоритм FIFO.\n", getpid());
char command_fifo[100];
sprintf(command_fifo, "chrt -p %d", getpid());
system(command_fifo);
sleep(5);
 system("ps -xf");
    sleep(5);
    wait(NULL); // ожидаем завершения процесса-потомока
    printf("Родительский процесс %d завершен.\n", getpid());
    exit(EXIT_SUCCESS);
}

}
