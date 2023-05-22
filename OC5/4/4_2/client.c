#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    // сервер уже создал каналы, открываем их
    int chan1 = open("канал1", O_RDONLY);
    if (chan1 == -1) {
        printf("Не удалось открыть канал1 для чтения\n");
        exit(0);
    }
    
    int chan2 = open("канал2", O_WRONLY);
    if (chan2 == -1) {
        printf("Не удалось открыть канал2 для записи\n");
        exit(0);
    }
    
    // читаем имя файла из первого канала
    char fileName[100];
    bzero(fileName, 100);
    int res = read(chan1, fileName, 100);
    if (res <= 0) {
        printf("Не удалось прочитать имя файла из канала1\n");
        exit(0);
    }
    
    // открываем файл на чтение
    FILE *f = fopen(fileName, "r");
    if (!f) {
        printf("Не удалось открыть файл %s\n", fileName);
        exit(0);
    }
    
    // читаем из файла и пишем во второй канал
    char buf[100];
    while (!feof(f)) {
        // читаем данные из файла
        res = fread(buf, sizeof(char), 100, f);
        // пишем их в канал
        write(chan2, buf, res);
    }
    
    fclose(f);
    close(chan1);
    close(chan2);
    
    return 0;
}

