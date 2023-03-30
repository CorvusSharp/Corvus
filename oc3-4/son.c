#include <stdio.h>
#include <unistd.h>

int main() {

  printf("Я дочерний процесс (son)!!! с PID: %d и мой родительский процесс имеет PID: %d\n", getpid(), getppid());
  sleep(5);


  return 0;
}

