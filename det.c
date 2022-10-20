#include <stdio.h>
#include <stdlib.h>

int matrix_size_input(int * rows, int *cols);
int** memory_allocation(int**matrix, int size);
int input_matrix(int** matrix, int size);

void get_minor(int** matrix, int** minor, int size, int i_minor, int j_minor);
int det(int** matrix, int size);

int main() {
  int rows, cols;
  if(matrix_size_input(&rows, &cols)){
    int** matrix = NULL;
    matrix = memory_allocation(matrix, rows);
    if(matrix == NULL) {
      printf("Memory allocation error!");
    } else {
      if(input_matrix(matrix, rows)){
        printf("%d", det(matrix, rows));
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
  if(scanf("%d %d", rows, cols) == 2 && *rows == *cols) {
    flag = 1;
  }
  return flag;
}

int** memory_allocation(int**matrix, int size){
  matrix = (int**)malloc(size * sizeof(int*) + size * size * sizeof(int));
  int* ptr = (int*)(matrix + size);
  for(int i = 0; i < size; i++) {
    matrix[i] = ptr + size * i;
  }
  return matrix;
}

int input_matrix(int** matrix, int size) {
  int flag = 0;
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      if(scanf("%d", &matrix[i][j]) == 1){
        flag = 1;
      }
    }
  }
  return flag;
}

void get_minor(int** matrix, int** minor, int size, int i_minor, int j_minor) {
  int rows = 0, cols = 0;
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      if (i != i_minor && j != j_minor)
      {
        minor[rows][cols++] = matrix[i][j];
        // cols++;
        if(cols == size -1) {
          cols = 0;
          rows++;
        }
      }
    }
  }
}

int det(int** matrix,  int size) {
  int determinant = 0;
  int znak = 1;

  if(size == 1) determinant = matrix[0][0];
  else if(size == 2) determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  else if(size > 2){
    int** minor = NULL;
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
