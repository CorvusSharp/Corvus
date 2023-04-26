#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    int i, ppid, pid[4], status[3], result[3];
    char *son[] = {"son1", "son2", "son3"};
    int option[] = {WNOHANG, WUNTRACED, WNOHANG};
    // Создаем массив строк, содержащий имена трех дочерних процессов
    // Создаем массив опций для waitpid() 

    pid[3] = getpid();
    ppid = getppid();
    printf("FATHER PARAMS: pid=%i  ppid=%i\n", pid[3],ppid);
    // Получаем и выводим идентификаторы процесса и родительского процесса

    for (i = 0; i < 3; i++)
        if((pid[i] = fork()) == 0)
            execl(son[i], son[i], NULL);
    // Создаем три дочерних процесса и запускаем каждый из них в отдельной программе

    system("ps xf > file.txt");
    // Записываем список процессов в файл file.txt

    for (i = 0; i < 3; i++)
    {
        result[i] = waitpid(pid[i], &status[i], option[i]);
        printf("%d) Child with pid = %d is finished with status %d\n", (1 + i), result[i], status[i]);
    }
    // Ждем завершения каждого дочернего процесса и выводим информацию о завершении

    for(i = 0; i < 3; i++)
        if (WIFEXITED(status[i]) == 0)
            printf("Proccess pid = %d was failed.\n",pid[i]);
        else
            printf("Proccess pid = %d was success.\n", pid[i]);
    // Проверяем, были ли все процессы успешно завершены

    return 0;
}
