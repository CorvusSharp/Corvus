// Подключение необходимых заголовочных файлов
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
// Определение количества сигналов для отправки
#define NUM_SIGNALS 4
// Обработчик сигналов
void handle_signal(int signo, siginfo_t *info, void *context) {
 // Вывод информации о полученном сигнале
 printf("Received signal %d with value %d\n", signo, info->si_value.sival_int);
}
int main() {
 int i;
 struct sigaction sa; // Структура для настройки обработчика сигнала
 union sigval value; // Объединение для хранения значения сигнала
 // Настройка обработчика сигналов
 sa.sa_sigaction = handle_signal;
 sa.sa_flags = SA_SIGINFO;
 sigemptyset(&sa.sa_mask);
 for (i = SIGRTMIN; i <= SIGRTMAX; i++) {
 sigaddset(&sa.sa_mask, i);
 }
 for (i = 1; i <= NUM_SIGNALS; i++) {
 sigaction(SIGINT + i, &sa, NULL);
 sigaction(SIGRTMIN + i, &sa, NULL);
 }
 // Отправка сигналов
 for (i = 1; i <= NUM_SIGNALS; i++) {
 value.sival_int = i;
 printf("Sending normal signal %d with value %d\n", SIGINT + i, value.sival_int);
 if (sigqueue(getpid(), SIGINT + i, value) != 0) {
 perror("sigqueue");
 exit(EXIT_FAILURE);
 }
 printf("Sending real-time signal %d with value %d\n", SIGRTMIN + i, value.sival_int);
 if (sigqueue(getpid(), SIGRTMIN + i, value) != 0) {
 perror("sigqueue");
 exit(EXIT_FAILURE);
 }
 }
 // Ожидание обработки сигналов
 sleep(1);
 return 0;
}
