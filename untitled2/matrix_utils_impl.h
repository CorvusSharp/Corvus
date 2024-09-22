//
// Created by Corvus on 22.09.2024.
//
#ifndef UNTITLED2_MATRIX_UTILS_IMPL_H
#define UNTITLED2_MATRIX_UTILS_IMPL_H
#include <iostream>
#include <fstream>
#include <ctime>

// Реализации функций для работы с матрицами

// Чтение матрицы из текстового файла
template <typename T>
void readMatrixfromTxt(std::vector<std::vector<T>>& matrix, const std::string& filename) {
    if (!std::ifstream(filename)) {
        std::cout << "Ошибка: файл не найден" << std::endl;
        return;
    }
    std::ifstream file(filename);
    int n, m;
    file >> n >> m;
    matrix.resize(n, std::vector<T>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            file >> matrix[i][j];
    }
    file.close();
}

// Запись матрицы в текстовый файл
template <typename T>
void writeMatrixtoTxt(const std::vector<std::vector<T>>& matrix, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл для записи" << std::endl;
        return;
    }
    file << matrix.size() << " " << matrix[0].size() << std::endl;
    for (const auto& row : matrix) {
        for (const auto& elem : row)
            file << elem << " ";
        file << std::endl;
    }
    file.close();
}

// Генерация случайной матрицы
template <typename T>
void genMatrix(std::vector<std::vector<T>>& matrix, int n, int m) {
    matrix.resize(n, std::vector<T>(m));
    for (auto& row : matrix) {
        for (auto& elem : row)
            elem = rand() % 10;
    }
}

// Последовательное умножение матриц
template <typename T>
std::vector<std::vector<T>> matrixMultiplication(const std::vector<std::vector<T>>& matrix1, const std::vector<std::vector<T>>& matrix2) {
    int n = matrix1.size();
    int m = matrix2[0].size();
    int p = matrix1[0].size();
    std::vector<std::vector<T>> result(n, std::vector<T>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < p; ++k)
                result[i][j] += matrix1[i][k] * matrix2[k][j];
        }
    }
    return result;
}

// Вывод матрицы на экран
template <typename T>
void printMatrix(const std::vector<std::vector<T>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row)
            std::cout << elem << " ";
        std::cout << std::endl;
    }
}

// Функция для измерения времени выполнения
inline double timer(const std::function<void()>& func) {
    clock_t start = clock();
    func();
    clock_t end = clock();
    return static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

// Функция для сравнения двух матриц
template <typename T>
bool compareMatrices(const std::vector<std::vector<T>>& matrix1, const std::vector<std::vector<T>>& matrix2) {
    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size())
        return false;
    for (size_t i = 0; i < matrix1.size(); ++i) {
        for (size_t j = 0; j < matrix1[0].size(); ++j) {
            if (matrix1[i][j] != matrix2[i][j])
                return false;
        }
    }
    return true;
}



#endif //UNTITLED2_MATRIX_UTILS_IMPL_H
