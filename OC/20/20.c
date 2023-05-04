#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define NUM_THREADS 2

int count1 = 0;
int count2 = 0;
pthread_t threads[NUM_THREADS];

void *thread_func(void *arg) {
    int id = *((int*) arg);
    while (1) {
        if (id == 1) {
            printf("Thread %d: %d\n", id, count1);
            count1++;
            sleep(5);
            printf("Удаление второй нити.");
            pthread_kill(threads[1], SIGUSR1);
        } else {
            printf("Thread %d: %d\n", id, count2);
            count2++;
            sleep(1);
        }
    }
    pthread_exit(NULL);
}

int main() {
    int thread_args[NUM_THREADS];
    int i;

    for (i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i+1;
        if (pthread_create(&threads[i], NULL, thread_func, &thread_args[i])) {
            fprintf(stderr, "Error creating thread %d\n", i+1);
            exit(1);
        }
    }

    if (pthread_join(threads[0], NULL)) {
        fprintf(stderr, "Error joining thread 1\n");
        exit(1);
    }

    return 0;
}
