#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

void *thread_func(void *arg) {
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &policy, &param);
    printf("Thread policy: %s\n", (policy == SCHED_FIFO ? "FIFO" :
                                   (policy == SCHED_RR ? "Round Robin" :
                                    (policy == SCHED_OTHER ? "Other" :
                                     "Unknown"))));
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_id;
    int ret;
    ret = pthread_create(&thread_id, NULL, &thread_func, NULL);
    if (ret != 0) {
        perror("pthread_create() error");
        exit(EXIT_FAILURE);
    }
    pthread_join(thread_id, NULL);
    return 0;
}
