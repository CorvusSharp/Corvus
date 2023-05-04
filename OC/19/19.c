#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define NUM_THREADS 2

int count1 = 0;
int count2 = 0;

void *thread_func(void *arg) {
    int id = *((int*) arg);
    while (1) {
        if (id == 1) {
            printf("Thread %d: %d\n", id, count1);
            count1++;
            sleep(5);
        } else {
            printf("Thread %d: %d\n", id, count2);
            count2++;
            sleep(1);
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;

    // create two child threads
    for (i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i+1;

        if (pthread_create(&threads[i], NULL, thread_func, &thread_args[i])) {
            fprintf(stderr, "Error creating thread %d\n", i+1);
            exit(1);
        }
    }

    system("ps -T");

    // join remaining child thread
    if (pthread_join(threads[0], NULL)) {
        fprintf(stderr, "Error joining thread 1\n");
        exit(1);
    }

    return 0;
}
