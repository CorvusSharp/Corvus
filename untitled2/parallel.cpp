//
// Created by Corvus on 22.09.2024.
//
#include <iostream>
#include <vector>
#include <thread>
#include "matrix_utils.h"

using namespace std;

// Функция для параллельного умножения матриц с использованием P потоков
template <typename T>
void parallelMatrixMultiplication(const vector<vector<T>>& matrix1, const vector<vector<T>>& matrix2, vector<vector<T>>& result, int num_threads) {
    int n = matrix1.size();
    int m = matrix2[0].size();
    int p = matrix1[0].size();

    result.resize(n, vector<T>(m, 0));

    // Лямбда-функция для выполнения части работы в отдельном потоке
    auto worker = [&](int start_row, int end_row) {
        for (int i = start_row; i < end_row; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < p; ++k) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
    };

    vector<thread> threads;
    int rows_per_thread = n / num_threads;
    int extra_rows = n % num_threads;
    int current_row = 0;

    // Создаем и запускаем потоки
    for (int i = 0; i < num_threads; ++i) {
        int start_row = current_row;
        int end_row = current_row + rows_per_thread + (i < extra_rows ? 1 : 0);
        threads.emplace_back(worker, start_row, end_row);
        current_row = end_row;
    }

    // Ожидаем завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }
}

// Тестовая функция для задания 1.2.2: Параллельное умножение матриц
void test2() {
    int n = 500, m = 500, p = 500;
    int P = 4; // Количество потоков
    vector<vector<int>> matrix1, matrix2, result_serial, result_parallel;

    genMatrix(matrix1, n, p);
    genMatrix(matrix2, p, m);

    cout << "Начинается последовательное умножение..." << endl;
    double time_serial = timer([&](){
        result_serial = matrixMultiplication(matrix1, matrix2);
    });
    cout << "Последовательное умножение завершено за " << time_serial << " секунд." << endl;

    cout << "Начинается параллельное умножение с использованием " << P << " потоков..." << endl;
    double time_parallel = timer([&](){
        parallelMatrixMultiplication(matrix1, matrix2, result_parallel, P);
    });
    cout << "Параллельное умножение завершено за " << time_parallel << " секунд." << endl;

    if (compareMatrices(result_serial, result_parallel))
        cout << "Результаты совпадают." << endl;
    else
        cout << "Результаты различаются!" << endl;
}
