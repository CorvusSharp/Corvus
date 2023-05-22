#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define NUM_SIGNALS 5

// Обработчик сигналов реального времени
void handle_rt_signal(int sig, siginfo_t* info, void* context) {
    printf("Обработка сигнала реального времени %d\n", sig - SIGRTMIN + 34);
    usleep(1000000); // Sleep for 1 second
}

// Обработчик обычных сигналов
void handle_normal_signal(int sig) {
    printf("Обработка обычного сигнала %d\n", sig);
}

int main() {
    // Перенаправление вывода в файл
    freopen("output.txt", "w", stdout);

    // Регистрация обработчика обычных сигналов
    for (int i = 1; i <= 5; i++) {
        signal(i, handle_normal_signal);
    }

    // Регистрация обработчика сигналов реального времени
    struct sigaction sa_rt;
    sa_rt.sa_sigaction = handle_rt_signal;
    sigemptyset(&sa_rt.sa_mask);
    sa_rt.sa_flags = SA_SIGINFO;
    for (int i = 34; i <= 38; i++) {
        sigaction(i, &sa_rt, NULL);
    }

    // Блокировка сигналов при отправке
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    // Отправка сигналов
    printf("Отправка сигналов...\n");
    for (int i = 1; i <= 5; i++) {
        printf("Отправка обычного сигнала %d\n", i);
        kill(getpid(), i);
        usleep(100000); // Sleep for 0.1 second between signals
    }
    for (int i = 34; i <= 38; i++) {
        printf("Отправка сигнала реального времени %d\n", i);
        kill(getpid(), i);
        usleep(100000); // Sleep for 0.1 second between signals
    }

    // Разблокировка сигналов
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    // Ожидание обработки сигналов (засыпание на 5 секунд)

    return 0;
}

