#include <stdio.h>
#include <stdlib.h>

int matrix_size_input(int * rows, int *cols);
double** memory_allocation(double**matrix, int size);
int input_matrix(double** matrix, int size);
void output_matrix(double** matrix, int size);

void get_minor(double** matrix, double** minor, int size, int i_minor, int j_minor);
double det(double** matrix, int size);

void transpose(double** matrix, int size, double** result);
void multiply(double** matrix, int size, double number);

void get_inverse_matrix(double** matrix, int size);

int main() {
  int rows, cols;
  if(matrix_size_input(&rows, &cols)){
    double** matrix = NULL;
    matrix = memory_allocation(matrix, rows);
    if(matrix == NULL) {
      printf("Memory allocation error!");
    } else {
      if(input_matrix(matrix, rows)){
        if(det(matrix, rows)){
           get_inverse_matrix(matrix, rows);
        } else {
          printf("Determinant is zero!");
        }
      } else {
        printf("Matrix input error!");
      }
      free(matrix);
    }
  } else {
    printf("Matrix size input error!");
  }

  return 0;
}

int matrix_size_input(int * rows, int *cols){
  int flag = 0;
  if(scanf("%d %d", rows, cols) == 2 && *rows == *cols && *rows > 0) {
    flag = 1;
  }
  return flag;
}

double** memory_allocation(double**matrix, int size){
  matrix = (double**)malloc(size * sizeof(double*) + size * size * sizeof(double));
  double* ptr = (double*)(matrix + size);
  for(int i = 0; i < size; i++) {
    matrix[i] = ptr + size * i;
  }
  return matrix;
}

int input_matrix(double** matrix, int size) {
  int flag = 0;
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      if(scanf("%lf", &matrix[i][j]) == 1){
        flag = 1;
      }
    }
  }
  return flag;
}

void output_matrix(double** matrix, int size){
  for(int i = 0; i < size; i++) {
    printf("%.6lf", matrix[i][0]);
    for(int j = 1; j < size; j++) {
      printf(" %.6lf", matrix[i][j]);
    }
    printf("\n");
  }
}

void get_minor(double** matrix, double** minor, int size, int i_minor, int j_minor) {
  int rows = 0, cols = 0;
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      if (i != i_minor && j != j_minor)
      {
        minor[rows][cols] = matrix[i][j];
        cols++;
        if(cols == size -1) {
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

  if(size == 1) determinant = matrix[0][0];
  else if(size == 2) determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  else if(size > 2){
    double** minor = NULL;
        minor = memory_allocation(minor, size -1);
        if(minor == NULL) {
          printf("Memory allocation error!");
        } else {
          for(int j = 0; j < size; j++){
            get_minor(matrix, minor, size, 0, j);
            determinant += znak * matrix[0][j] * det(minor, size - 1);
            znak = -znak;
          }
          free(minor);
        }
  }

  return determinant;
}

void transpose(double** matrix, int size, double** result){
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      result[i][j] = matrix[j][i];
    }
  }
}

void multiply(double** matrix, int size, double number){
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      matrix[i][j] = number * matrix[i][j];
    }
  }
}

void get_inverse_matrix(double** matrix, int size) {
  int simbol = 1;
  double** main_minor_matrix = NULL;
  main_minor_matrix = memory_allocation(main_minor_matrix, size);
  if(main_minor_matrix == NULL) {
    printf("Memory allocation error!");
  } else {
    double** minor = NULL;
        minor = memory_allocation(minor, size -1);
        if(minor == NULL) {
          printf("Memory allocation error!");
        } else {
          for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                if ((i + j) % 2 == 0) simbol = 1;
                else simbol = -1;
                get_minor(matrix, minor, size, i, j);
                main_minor_matrix[i][j] = simbol * det(minor, size -1);
            }
          }

        double** inverse = NULL;
        inverse = memory_allocation(inverse, size);
        if(inverse == NULL) {
          printf("Memory allocation error!");
        } else {

          transpose(main_minor_matrix, size, inverse);
          multiply(inverse, size, (1./det(matrix, size)));
          output_matrix(inverse, size);
          free(inverse);
        }
        
          free(minor);
        } 
    free(main_minor_matrix);
  }
}