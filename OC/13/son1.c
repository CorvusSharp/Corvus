#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    signal(SIGUSR1, SIG_DFL);
    sleep(5);
    return 0;
}
