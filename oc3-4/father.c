#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t pid;

  printf("Я родительский процесс с PID: %d\n", getpid());

  // Сохраняем состояние таблицы процессов в файле

  pid = fork();

  if (pid == -1) {
    printf("Ошибка: не удалось создать дочерний процесс\n");
    exit(1);
  } else if (pid == 0) {
    // Код, выполняемый потомком
    printf("Я дочерний процесс с PID: %d\n", getpid());
    execlp("./son", "son", NULL); // Запускаем программу son
  } else {
    // Код, выполняемый родителем
    printf("Я родительский процесс с PID: %d и я жду своего потомка...\n", getpid());
 system("ps -xf --forest > ps-table");
    wait(NULL); // Ждем завершения потомка

    // Выводим информацию о процессах, запущенных в терминале
    printf("Информация о процессах, запущенных в терминале:\n");

    printf("Потомок завершился, я тоже завершаюсь\n");
  }

  return 0;
}

