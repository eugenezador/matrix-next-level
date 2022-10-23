#include <stdio.h>
#include <stdlib.h>

int matrix_size_input(int* rows, int* cols);
double** memory_allocation(double** matrix, int rows, int cols);
int input_matrix(double** matrix, int rows, int cols);
void output_matrix(double** matrix, int rows, int cols);

void get_minor(double** matrix, double** minor, int size, int i_minor, int j_minor);
double det(double** matrix, int size);

void get_slau_solution(double** matrix, int rows, int cols, double* free_members);
void copy_matrix(double** matrix, double** tmp, int rows, int cols);
void array_output(double* array, int size);

int main() {
    int rows, cols;
    if (matrix_size_input(&rows, &cols)) {
        double** slau = NULL;
        slau = memory_allocation(slau, rows, cols);
        if (slau == NULL) {
            printf("Memory allocation error!");
        }
        else {
            if (input_matrix(slau, rows, cols)) {
                double* free_members = NULL;
                double** matrix = NULL;
                free_members = (double*)malloc(rows * sizeof(int));
                matrix = memory_allocation(matrix, rows, cols - 1);
                if (free_members == NULL || matrix == NULL) {
                    printf("Memory allocation error!");
                } else {
                    for (int i = 0; i < rows; i++) {
                        free_members[i] = slau[i][cols - 1];
                    }
                    if (cols != rows + 1)
                    {
                        printf("Slau size Error!");
                    }
                    else {
                        for (int i = 0; i < rows; i++) {
                            for (int j = 0; j < cols - 1; j++) {
                                matrix[i][j] = slau[i][j];
                            }
                        }

                        get_slau_solution(matrix, rows, cols - 1, free_members);

                        free(free_members);
                        free(matrix);
                    }
                }
            }
            else {
                printf("Matrix input error!");
            }
            free(slau);
        }
    }
    else {
        printf("Matrix size input error!");
    }


	return 0;
}

int matrix_size_input(int* rows, int* cols) {
    int flag = 0;
    if (scanf("%d %d", rows, cols) == 2 && *rows > 0 && *cols > 0 ) {
        flag = 1;
    }
    return flag;
}

double** memory_allocation(double** matrix, int rows, int cols) {
    matrix = (double**)malloc(rows * sizeof(double*) + rows * cols * sizeof(double));
    double* ptr = (double*)(matrix + rows);
    for (int i = 0; i < rows; i++) {
        matrix[i] = ptr + cols * i;
    }
    return matrix;
}

int input_matrix(double** matrix, int rows, int cols) {
    int flag = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%lf", &matrix[i][j]) == 1) {
                flag = 1;
            }
        }
    }
    return flag;
}

void output_matrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        printf("%.6lf", matrix[i][0]);
        for (int j = 1; j < cols; j++) {
            printf(" %.6lf", matrix[i][j]);
        }
        printf("\n");
    }
}

void get_minor(double** matrix, double** minor, int size, int i_minor, int j_minor) {
    int rows = 0, cols = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != i_minor && j != j_minor)
            {
                minor[rows][cols] = matrix[i][j];
                cols++;
                if (cols == size - 1) {
                    cols = 0;
                    rows++;
                }
            }
        }
    }
}

double det(double** matrix, int size) {
    double determinant = 0;
    int znak = 1;

    if (size == 1) determinant = matrix[0][0];
    else if (size == 2) determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    else if (size > 2) {
        double** minor = NULL;
        minor = memory_allocation(minor, size - 1, size - 1);
        if (minor == NULL) {
            printf("Memory allocation error!");
        }
        else {
            for (int j = 0; j < size; j++) {
                get_minor(matrix, minor, size, 0, j);
                determinant += znak * matrix[0][j] * det(minor, size - 1);
                znak = -znak;
            }
            free(minor);
        }
    }

    return determinant;
}

void get_slau_solution(double** matrix, int rows, int cols, double* free_members) {
    
    double* solution = NULL;
    solution = (double*)malloc(rows * sizeof(int));

    double** tmp = NULL;
    tmp = memory_allocation(tmp, rows, cols);
    if (tmp == NULL || solution == NULL) {
        printf("Memory allocation error!");
    }
    else {
        double matrix_determinant = det(matrix, cols);
        for (int free_col = 0; free_col < cols; free_col++) {
            
            copy_matrix(matrix, tmp, rows, cols);
            int k = 0;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (j == free_col) {
                        tmp[i][j] = free_members[k];
                        k++;
                    }
                }
            }
            solution[free_col] = det(tmp, rows) / matrix_determinant;
        }

        array_output(solution, rows);

        free(solution);
        free(tmp);
    } 
}

void copy_matrix(double** matrix, double** tmp, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tmp[i][j] = matrix[i][j];
        }
    }
}

void array_output(double* array, int size) {
    printf("%.6lf", array[0]);
    for (int i = 1; i < size; i++) {
        printf(" %.6lf", array[i]);
    }
}