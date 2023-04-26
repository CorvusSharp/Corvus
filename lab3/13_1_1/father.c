#include <signal.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
   int pid[3];
   char * son[3] = {"son1", "son2", "son3"};
for(int i = 0; i < 3; i++) {
       if((pid[i] = fork()) == 0) {
           execl(son[i], son[i], NULL);
       }
   }
   system("echo before signal sent");
   system("ps -l");
   for(int i = 0;i < 3; i++) {
       kill(pid[i], SIGUSR1);
   }
   system("echo after signal sent");
   system("ps -l");
}
