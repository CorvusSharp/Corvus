#include <signal.h>
#include <unistd.h>
int main() {
   signal(SIGUSR1,SIG_IGN);
   sleep(5);
}
