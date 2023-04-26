#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "unistd.h"
int main() {
   printf("\nSon's params: pid = %d, ppid = %d\n", getpid(), getppid());
   while(1)
       pause();
return 0;
}
