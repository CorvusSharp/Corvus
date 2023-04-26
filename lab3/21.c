#include <sys/types.h>
#include <linux/unistd.h>
#include <sys/syscall.h>

#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include "time.h"
#include "unistd.h"
#include <stdlib.h>

pthread_t  t1, tn;

// обработчик
void sig_handler(int signo) {
    if (signo == SIGUSR1) {
        printf("Thread 2 is killed\n");
        pthread_cancel(tn); // удаляем вторую нить
		//pthread_exit(NULL);
    }
}


void * thread1() {
	printf("Thread_1 is started\n");
   // здесь код,который должна выполнять нить
   time_t timer;
   timer = time(NULL);
   int n = 1;
   for(int i = 0; i <7; i++) {
		time_t end = time(NULL);
		printf("th1 n=%d, time=%ld\n", n *= 2, -timer + end);
		system("ps axhf > threadn.txt");
		sleep(5);
		pthread_kill(tn, SIGUSR1);
   }
   	//system("ps axhf > thread1.txt");
	printf("Thread_1 is ended\n");
}
void * threadn() {
   printf("Thread_n is started\n");
   // здесь код, который должна выполнять нить n
   time_t timer;
   timer = time(NULL);
   int n = 1;
   for(int i = 0; i <10; i++) {
	    time_t end = time(NULL);
		printf("th2 n=%d, time=%ld\n", n *= 3, -timer + end);
		system("ps axhf > threadn.txt");
	    sleep(1);
   }
	printf("Thread_2 is ended\n");
}
int main() {
	signal(SIGUSR1, sig_handler);
    system("ps axhf > file.txt");
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&tn, NULL, threadn, NULL);
    system("ps axhf >> file.txt");
    pthread_join(t1, NULL);
    pthread_join(tn, NULL);
    system("ps axhf >> file.txt");
}