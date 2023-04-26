#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Заблокировать все страницы памяти процесса в оперативной памяти
    if (mlockall(MCL_CURRENT | MCL_FUTURE) < 0)
        perror("mlockall error");

    // Объявить переменные
    char c;
    char buff[3];
    int pid, ppid;
    int fdrd = atoi(argv[1]); // Преобразовать строковый параметр входного файла в целочисленный дескриптор файла
    int fdwr = atoi(argv[2]); // Преобразовать строковый параметр выходного файла в целочисленный дескриптор файла
    pid = getpid(); // Получить идентификатор текущего процесса
    ppid = getppid(); // Получить идентификатор родительского процесса
    printf("son file descriptor = %d\n", fdrd); // Вывести дескриптор входного файла
    printf("son params: pid=%i ppid=%i\n", pid, ppid); // Вывести параметры процесса
    sleep(5); // Задержать выполнение процесса на 5 секунд

    // Начать бесконечный цикл
  for (;;) {
   if (read(fdrd, &c, 1) != 1)
      return 0;
   write(fdwr, &c, 1);
   printf("pid = %d: %c\n", pid, c);
   if (close(fdrd) != 0) {
      perror("Closing file");
   }
}

}

