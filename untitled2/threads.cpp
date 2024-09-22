//
// Created by Corvus on 22.09.2024.
//

// threads.cpp

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "matrix_utils.h"

using namespace std;

// Общие переменные для потоков
vector<vector<int>> matrix1, matrix2, result;

// Объекты синхронизации
mutex mtx;
condition_variable cv;
bool matrices_ready = false;
bool result_ready = false;

// Поток 1: Генерирует матрицы
void thread1() {
    // Генерация матриц
    genMatrix(matrix1, 3, 3);
    genMatrix(matrix2, 3, 3);

    // Уведомляем о готовности матриц
    {
        unique_lock<mutex> lock(mtx);
        matrices_ready = true;
        cout << "Поток 1: Матрицы сгенерированы." << endl;
    }
    cv.notify_all();
}

// Поток 2: Выполняет умножение
void thread2() {
    // Ожидание готовности матриц
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []{ return matrices_ready; });
    }
    // Выполнение умножения
    result = matrixMultiplication(matrix1, matrix2);
    // Уведомляем о готовности результата
    {
        unique_lock<mutex> lock(mtx);
        result_ready = true;
        cout << "Поток 2: Умножение матриц выполнено." << endl;
    }
    cv.notify_all();
}

// Поток 3: Выводит результат
void thread3() {
    // Ожидание готовности результата
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []{ return result_ready; });
    }
    // Вывод результата
    cout << "Поток 3: Результирующая матрица:" << endl;
    printMatrix(result);
}

// Тестовая функция для задания 1.2.1: Использование потоков
void test1_threads() {
    // Запускаем все три потока
    thread t1(thread1);
    thread t2(thread2);
    thread t3(thread3);

    // Ожидаем завершения всех потоков
    t1.join();
    t2.join();
    t3.join();
}
