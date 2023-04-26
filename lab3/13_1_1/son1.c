#include <signal.h>
#include <unistd.h>

int main(){
   signal(SIGUSR1,SIG_DFL);
   sleep(5);
}
