#include <iostream>
#include "functions.hpp"

void print_matrix(float** matrix, const size_t rows, const size_t cols) {
	for (size_t c = 0; c < rows; c++) {
		for (size_t p = 0; p < cols; p++)
			std::cout << matrix[c][p] << ' ';
		std::cout << std::endl;
	}
}

int main() {
	const size_t ROWS = 5;
	const size_t COLS = 3;
	float** matrix = new float* [ROWS];
	float** new_matrix = nullptr;
	for (size_t c = 0; c < ROWS; c++) {
		matrix[c] = new float[COLS];
		for (size_t p = 0; p < COLS; p++) {
			matrix[c][p] = static_cast<float>(rand() % 100);
		}
	}
	print_matrix(matrix, ROWS, COLS);

	new_matrix = transform_matrix(matrix, ROWS, COLS);

	print_matrix(new_matrix, COLS, ROWS);

	for (size_t c = 0; c < ROWS; c++)
		delete[] matrix[c];
	for (size_t c = 0; c < COLS; c++)
		delete[] new_matrix[c];
	delete[] new_matrix;
	delete[] matrix;

	return 0;
}