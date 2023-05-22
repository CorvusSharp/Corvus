#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define DEF_FILENAME "testFile.txt"

int main(int argc, char** argv) {
    char fileName[30];
    if (argc < 2) {
        printf("Используется имя файла по умолчанию: '%s'\n", DEF_FILENAME);
        strcpy(fileName, DEF_FILENAME);
    } else {
        strcpy(fileName, argv[1]);
    }
    
    // создаем два канала
    int res = mknod("канал1", S_IFIFO | 0666, 0);
    if (res) {
        perror("Не удалось создать первый канал");
        exit(1);
    }
    
    res = mknod("канал2", S_IFIFO | 0666, 0);
    if (res) {
        printf("Не удалось создать второй канал\n");
        exit(1);
    }
    
    // открываем первый канал для записи
    int chan1 = open("канал1", O_WRONLY);
    if (chan1 == -1) {
        printf("Не удалось открыть канал для записи\n");
        exit(0);
    }
    
    // открываем второй канал для чтения
    int chan2 = open("канал2", O_RDONLY);
    if (chan2 == -1) {
        printf("Не удалось открыть канал для чтения\n");
        exit(0);
    }
    
    // пишем имя файла в первый канал
    write(chan1, fileName, strlen(fileName));
    
    // читаем содержимое файла из второго канала
    char buf[100];
    for (;;) {
        bzero(buf, 100);
        res = read(chan2, buf, 100);
        if (res <= 0)
            break;
        printf("Часть файла: %s\n", buf);
    }
    
    close(chan1);
    close(chan2);
    unlink("канал1");
    unlink("канал2");
    
    return 0;
}

