#ifndef UNTITLED2_MATRIX_UTILS_H
#define UNTITLED2_MATRIX_UTILS_H

#include <vector>
#include <string>
#include <functional>


template <typename T>
void readMatrixfromTxt(std::vector<std::vector<T>>& matrix, const std::string& filename);

template <typename T>
void writeMatrixtoTxt(const std::vector<std::vector<T>>& matrix, const std::string& filename);

template <typename T>
void genMatrix(std::vector<std::vector<T>>& matrix, int n, int m);

template <typename T>
std::vector<std::vector<T>> matrixMultiplication(const std::vector<std::vector<T>>& matrix1, const std::vector<std::vector<T>>& matrix2);

template <typename T>
void printMatrix(const std::vector<std::vector<T>>& matrix);

double timer(const std::function<void()>& func);

template <typename T>
bool compareMatrices(const std::vector<std::vector<T>>& matrix1, const std::vector<std::vector<T>>& matrix2);

#include "matrix_utils_impl.h"


#endif //UNTITLED2_MATRIX_UTILS_H
