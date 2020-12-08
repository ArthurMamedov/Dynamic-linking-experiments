#include "pch.h"
#include "functions.hpp"

float** transform_matrix(
    float** matrix, const size_t rows, const size_t cols) {

    float** new_matrix = new float* [cols];
    for (size_t c = 0; c < cols; c++)
        new_matrix[c] = new float[rows];

    for (size_t c = 0; c < rows; c++)
        for (size_t p = 0; p < cols; p++)
            new_matrix[p][c] = matrix[c][p];

    return new_matrix;
}