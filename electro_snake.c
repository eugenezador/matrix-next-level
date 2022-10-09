#include <stdio.h>
#include <stdlib.h>

int input_matrix_size(int *rows, int *cols);

int** memory_allocation(int ** matrix, int rows, int cols);

int input(int **matrix, int rows, int cols);

void output(int **matrix, int rows, int cols);

void horizontal_snake_sort(int **matrix, int rows, int cols, int **result);

void vertical_snake_sort(int** matrix, int rows, int cols, int **result);

void matrix_sort(int** matrix, int rows, int cols);

int main() {
	int rows, cols;
	if (input_matrix_size(&rows, &cols)) {
		int** matrix = NULL;
		int** result = NULL;
		matrix = memory_allocation(matrix, rows, cols);
		if (matrix == NULL) {
			printf("Memory allocation error!");
		}
		else {
			if (input(matrix, rows, cols)) {
				result = memory_allocation(result, rows, cols);
				if (result == NULL) {
					printf("Memory allocation error!");
				}
				else {
					//matrix_sort(matrix, rows, cols);
					printf("\n");
					vertical_snake_sort(matrix, rows, cols, result);
					output(result, rows, cols);
					printf("\n");
					horizontal_snake_sort(matrix, rows, cols, result);
					output(result, rows, cols);
				}
			}
			else {
				printf("Matrix input error!");
			}
		}
	}
	else {
		printf("Matrix size input error!");
	}
	return 0;
}

int input_matrix_size(int* rows, int* cols) {
	int flag = 0;
	if (scanf("%d %d", rows, cols) == 2 && *rows > 0 && *cols > 0) {
		flag = 1;
	}
	return flag;
}

int** memory_allocation(int **matrix, int rows, int cols) {
	matrix = (int**)malloc( rows * sizeof(int*) + rows * cols * sizeof(int));
	int* ptr = (int*)(matrix + rows);
	for (int i = 0; i < rows; i++) {
		matrix[i] = ptr + cols * i;
	}
	return matrix;
}

int input(int** matrix, int rows, int cols) {
	int flag = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (scanf("%d", &matrix[i][j]) == 1) {
				flag = 1;
			}
		}
	}
	return flag;
}
void output(int** matrix, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		printf("%d", matrix[i][0]);
		for (int j = 1; j < cols; j++) {
			printf(" %d", matrix[i][j]);
		}
		printf("\n");
	}
}

void horizontal_snake_sort(int** matrix, int rows, int cols, int** result) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i % 2 == 0) {
				result[i][j] = matrix[i][j];
			}
			else {
				result[i][j] = matrix[i][cols - j - 1];
			}
			
		}
	}
}

void vertical_snake_sort(int** matrix, int rows, int cols, int** result) {
	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < cols; i++) {
			if (j % 2 == 0) {
				result[i][j] = matrix[j][i];
			}
			else {
				//result[i][j] = 0 /*matrix[i][cols - j - 1]*/;
			}

		}
	}
}

void matrix_sort(int** matrix, int rows, int cols) {
	int tmp;
	for (int k = 0; k < rows* cols; k++) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols - 1; j++) {
				if (matrix[i][j] > matrix[i][j + 1]) {
					tmp = matrix[i][j];
					matrix[i][j] = matrix[i][j + 1];
					matrix[i][j + 1] = tmp;
				}
			}
		}

		for (int x = 0; x < rows; x++)
		{
			for (int z = 0; z < cols - 1; z++)
			{
				if (matrix[z][x] > matrix[z][x + 1])
				{
					tmp = matrix[z][x];
					matrix[z][x] = matrix[z][x + 1];
					matrix[z][x + 1] = tmp;
				}
			}
		}
	}
}
