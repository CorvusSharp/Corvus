#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define NUM_SIGNALS 5

void handle_rt_signal(int sig, siginfo_t* info, void* context) {
    printf("Handling real-time signal %d\n", sig);
    usleep(1000000); // Sleep for 1 second
}

void handle_normal_signal(int sig) {
    printf("Handling normal signal %d\n", sig);
}

int main() {
    // Redirect output to a file
    freopen("output.txt", "w", stdout);

    // Register real-time signals
    struct sigaction sa_rt;
    sa_rt.sa_sigaction = handle_rt_signal;
    sa_rt.sa_flags = SA_SIGINFO;
    sigemptyset(&sa_rt.sa_mask);
    for (int i = SIGRTMIN; i <= SIGRTMAX; i++) {
        sigaction(i, &sa_rt, NULL);
    }

    // Register normal signals
    for (int i = 1; i <= NUM_SIGNALS; i++) {
        signal(i, handle_normal_signal);
    }

    // Send signals
    printf("Sending signals...\n");
    for (int i = 1; i <= NUM_SIGNALS; i++) {
        printf("Sending normal signal %d\n", i);
        kill(getpid(), i);
    }
    for (int i = SIGRTMIN; i <= SIGRTMAX; i++) {
        printf("Sending real-time signal %d\n", i);
        kill(getpid(), i);
    }

    printf("Signals sent. Sleeping for 5 seconds to allow handling...\n");
    sleep(5);

    return 0;
}
