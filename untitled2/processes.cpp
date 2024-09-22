//
// Created by Corvus on 22.09.2024.
//
// processes.cpp

#include <iostream>
#include <vector>
#include <unistd.h>     // Для функций fork(), sleep()
#include <sys/types.h>
#include <sys/wait.h>
#include "matrix_utils.h"

using namespace std;

// Процесс 1: Генерирует матрицы и записывает их в файлы
void process1() {
    vector<vector<int>> matrix1, matrix2;
    int n = 3, m = 3, k = 3;
    genMatrix(matrix1, n, m);
    genMatrix(matrix2, m, k);
    writeMatrixtoTxt(matrix1, "matrix1.txt");
    writeMatrixtoTxt(matrix2, "matrix2.txt");
    cout << "Процесс 1: Матрицы сгенерированы и записаны в файлы." << endl;
}

// Процесс 2: Читает матрицы из файлов, выполняет умножение, записывает результат в файл
void process2() {
    // Ожидание появления файлов с матрицами
    while (!ifstream("matrix1.txt") || !ifstream("matrix2.txt")) {
        sleep(1); // Ждем 1 секунду перед повторной проверкой
    }
    // Чтение матриц из файлов
    vector<vector<int>> matrix1, matrix2;
    readMatrixfromTxt(matrix1, "matrix1.txt");
    readMatrixfromTxt(matrix2, "matrix2.txt");
    // Выполнение умножения
    vector<vector<int>> result = matrixMultiplication(matrix1, matrix2);
    // Запись результата в файл
    writeMatrixtoTxt(result, "result.txt");
    cout << "Процесс 2: Умножение матриц выполнено, результат записан в файл." << endl;
}

// Процесс 3: Читает результат из файла и выводит его
void process3() {
    while (!ifstream("result.txt")) {
        sleep(1); // Ждем 1 секунду перед повторной проверкой
    }
    vector<vector<int>> result;
    readMatrixfromTxt(result, "result.txt");
    cout << "Процесс 3: Результирующая матрица:" << endl;
    printMatrix(result);
}

// Тестовая функция для задания 1.1: Использование процессов
void test1_processes() {
    pid_t pid1, pid2, pid3;

    pid1 = fork();
    if (pid1 == 0) {
        // Дочерний процесс 1
        process1();
        exit(0);
    } else if (pid1 > 0) {
        pid2 = fork();
        if (pid2 == 0) {
            // Дочерний процесс 2
            process2();
            exit(0);
        } else if (pid2 > 0) {
            pid3 = fork();
            if (pid3 == 0) {
                // Дочерний процесс 3
                process3();
                exit(0);
            } else if (pid3 > 0) {
                // Родительский процесс
                // Ожидаем завершения всех дочерних процессов
                waitpid(pid1, NULL, 0);
                waitpid(pid2, NULL, 0);
                waitpid(pid3, NULL, 0);
                cout << "Все процессы завершены." << endl;
            } else {
                perror("fork");
                exit(1);
            }
        } else {
            perror("fork");
            exit(1);
        }
    } else {
        perror("fork");
        exit(1);
    }
}
