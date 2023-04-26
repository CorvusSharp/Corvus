#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void itoa(char *buf, int value) {
    sprintf(buf, "%d", value);
}

int main(void) {
    int pid, ppid, status;
    int fdrd, fdwr;
    char str1[10], str2[10];
    struct sched_param shdprm;

    // Заблокировать все страницы памяти процесса в оперативной памяти
    if (mlockall(MCL_CURRENT | MCL_FUTURE) < 0)
        perror("mlockall error");

    // Получить идентификатор текущего и родительского процесса
    pid = getpid();
    ppid = getppid();

    // Установить параметры планировщика задач для родительского процесса
    shdprm.sched_priority = 1;
    if (sched_setscheduler(0, SCHED_RR, &shdprm) == -1)
        perror("SCHED_SETSCHEDULER_1");

    // Открыть файл для чтения и файла для записи
    if ((fdrd = open("infile.txt", O_RDONLY)) == -1)
        perror("Opening file");
    if ((fdwr = creat("outfile.txt",0666)) == -1)
        perror("Creating file");

    // Преобразовать дескрипторы файлов в строковые значения
    itoa(str1, fdrd);
    itoa(str2,fdwr);

    // Создать два процесса-потомка
    for (int i = 0; i < 2; i++) {
        if (fork() == 0) {
            // Установить параметры планировщика задач для процессов-потомков
            shdprm.sched_priority = 50;
            if (sched_setscheduler(0, SCHED_RR, &shdprm) == -1)
                perror("SCHED_SETSCHEDULER_1");
            // Заменить текущий процесс на новый процесс, запущенный из файла "son" с параметрами-строками
            execl("son", "son", str1, str2, NULL);
        }
    }

    // Закрыть файл для чтения
    if (close(fdrd) != 0)
        perror("Closing file");

    // Дождаться завершения процессов-потомков
    for (int i = 0; i < 2; i++)
        printf("Process pid = %d completed\n", wait(&status));

    return 0;
}

