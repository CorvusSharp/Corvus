#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#define DEF_KEY_FILE "key"
typedef struct {
    long type;
    char buf[100];
} Message;
int queue;

int main(int argc, char **argv) {
    char keyFile[100];
    bzero(keyFile, 100);
    if (argc < 3) {
        printf("Usage: %s <key_file> <message_type>\n",
               argv[0]);
        exit(1);
    }
    strcpy(keyFile, argv[1]);
    int messageType = atoi(argv[2]);
    key_t key;
    key = ftok(keyFile, 'Q');
    if (key == -1) {
        printf("Failed to get key for key file %s and id 'Q'\n",
               keyFile);
        exit(1);
    }
    queue = msgget(key, 0); // Получаем доступ к очереди
    if (queue < 0) {
        printf("Can't create queue\n");
        exit(4);
    }
// Основной цикл работы программы
    Message mes;
    int res;
    for (;;) {
        bzero(mes.buf, 100); // Читаем сообщение с консоли
        fgets(mes.buf, 100, stdin);
        mes.buf[strlen(mes.buf) - 1] = '\0';
// Шлем его серверу с указанным типом сообщения
        mes.type = messageType;
        res = msgsnd(queue, &mes, sizeof(Message), 0);
        if (res != 0) {
            printf("Error while sending msg\n");
            exit(1);
        }
// Получаем ответ
        Message response;
        res = msgrcv(queue, &response, sizeof(Message),
                     messageType + 1, 0);
        if (res < 0) {
            printf("Error while recving msg\n");
            exit(1);
        }
        printf("Server's response: %s\n", response.buf);
    }
    return 0;
}
