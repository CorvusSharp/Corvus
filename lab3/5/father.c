#include <stdio.h> // Библиотека ввода-вывода
#include <stdlib.h> // Библиотека стандартных функций
#include <sys/types.h> // Библиотека для работы с типами данных в системе
#include <sys/wait.h> // Библиотека для работы с процессами
#include <unistd.h> // Библиотека для работы с системными вызовами

int main() // Начало функции main()
{
    int pid, ppid, status; // Объявление трех целочисленных переменных

    pid=getpid(); // Получение идентификатора текущего процесса
    ppid=getppid(); // Получение идентификатора родительского процесса
// Вывод на экран идентификатора текущего и родительского процессов
    printf("FATHER PARAM: pid=%i  ppid=%i\n", pid,ppid); 
    if (fork()==0) // Создание дочернего процесса
        execl("son","son", NULL); // Вызов исполняемого файла "son"
	// Запись информации о процессах в файл "file.txt"
    system("ps -abcde > file.txt"); 
    wait(&status); // Ожидание завершения дочернего процесса
	// Вывод на экран статуса завершения дочернего процесса
    printf("Child proccess is finished with status %d\n", status); 

    return 0; // Возврат значения 0, указывающего на успешное завершение программы
} // Конец функции main()