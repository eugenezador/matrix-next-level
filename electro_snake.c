#include <stdio.h>
#include <stdlib.h>

int input_matrix_size(int *rows, int *cols);

int** memory_allocation(int ** matrix, int rows, int cols);

int input(int **matrix, int rows, int cols);

void output(int **matrix, int rows, int cols);

void horizontal_snake_sort(int* array, int** result, int rows, int cols);

void matrix_to_array(int** matirx, int rows, int cols, int* array);

void vertical_snake_sort(int* array, int** result, int rows, int cols);

void array_sort(int* array, int size);

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
					int *array = NULL;
					array = (int*)malloc(rows * cols * sizeof(int));
					if(array == NULL) {
						printf("Memory allocation error");
					} else {
						matrix_to_array(matrix, rows, cols, array);
						array_sort(array, rows * cols);
						printf("\n");
						vertical_snake_sort(array, result, rows, cols);
						output(result, rows, cols);
						printf("\n");
						horizontal_snake_sort(array, result, rows, cols);
						output(result, rows, cols);
					}
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

void matrix_to_array(int** matrix, int rows, int cols, int* array) {
    int k = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            array[k] = matrix[i][j];
            k++;
        }
    }
}

void horizontal_snake_sort(int* array, int** result, int rows, int cols) {
	int k = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i % 2 == 0) {
				result[i][j] = array[k];
				k++;
			}
			else {
				result[i][cols - j - 1] = array[k];
				k++;
			}
		}
	}
}

void vertical_snake_sort(int* array, int** result, int rows, int cols) {
	int k = 0;
    for(int j = 0; j < cols; j++) {
        for(int i = 0; i < rows; i++) {
            if(j  % 2 == 0) {
                result[i][j] = array[k];
                k++;
            } else {
                result[rows - i - 1][j] = array[k];
                k++;
            }
        }
    }
}

void array_sort(int* array, int size) {
	int tmp;
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size - i - 1; j++){
			if(array[j] > array[j + 1]) {
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
		}
	}
}
