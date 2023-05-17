#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int reliable_signal_count = 0;
volatile int total_reliable_signals_sent = 0;
volatile int unreliable_signal_count = 0;
volatile int total_unreliable_signals_sent = 0;

void sigint_handler(int signal_number) {
    printf("\nНадежный сигнал (SIGINT) получен.\n");
    printf("Отправлено надежных сигналов (SIGUSR1): %d\n", total_reliable_signals_sent);
    printf("Обработано надежных сигналов (SIGUSR1): %d\n", reliable_signal_count);
    printf("Потеряно надежных сигналов (SIGUSR1): %d\n",
           total_reliable_signals_sent - reliable_signal_count);
    printf("\nОтправлено ненадежных сигналов (SIGALRM): %d\n", total_unreliable_signals_sent);
    printf("Обработано ненадежных сигналов (SIGALRM): %d\n", unreliable_signal_count);
    printf("Потеряно ненадежных сигналов (SIGALRM): %d\n",
           total_unreliable_signals_sent - unreliable_signal_count);
    exit(0);
}

void sigusr1_handler(int signal_number) {
    reliable_signal_count++;
    sleep(2); // Искусственная задержка для имитации долгой обработки сигнала
}

void sigalrm_handler(int signal_number) {
    unreliable_signal_count++;
    sleep(2); // Искусственная задержка для имитации долгой обработки сигнала
    signal(SIGALRM, sigalrm_handler); // Восстанавливаем обработчик сигнала после вызова
}

int main() {
    struct sigaction sa_int, sa_usr1, sa_alrm;
    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sa_usr1.sa_handler = sigusr1_handler;
    sigemptyset(&sa_usr1.sa_mask);
    sa_usr1.sa_flags = 0;
    sa_alrm.sa_handler = sigalrm_handler;
    sigemptyset(&sa_alrm.sa_mask);
    sa_alrm.sa_flags = 0;

    sigaction(SIGINT, &sa_int, NULL);
    sigaction(SIGUSR1, &sa_usr1, NULL);
    sigaction(SIGALRM, &sa_alrm, NULL);

    printf("Демонстрация работы сигналов:\n");
    printf("Процесс ID: %d\n", getpid());
    printf("Надежный сигнал (SIGINT): остановка программы и вывод результатов\n");
    printf("Надежный сигнал (SIGUSR1): инкремент счетчика без потерь\n");
    printf("Ненадежный сигнал (SIGALRM): инкремент счетчика с гарантированной потерей\n");
    printf("Ожидание сигналов...\n");

    while (1) {
        kill(getpid(), SIGUSR1); // Генерируем надежный сигнал SIGUSR1 для текущего процесса
        printf("SIGUSR1 sent\n");
        total_reliable_signals_sent++;
        sleep(1); // Искусственная задержка между отправкой сигналов SIGUSR1

        // Генерируем ненадежный сигнал SIGALRM для текущего процесса
        alarm(1); // Устанавливаем таймер на 1 секунду, после которого генерируется SIGALRM
        printf("SIGALRM sent\n");
        total_unreliable_signals_sent++;

        pause(); // Ожидание сигналов
    }

    return 0;
}

