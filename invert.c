#include <stdio.h>
#include <stdlib.h>

int matrix_size_input(int * rows, int *cols);
double** memory_allocation(double**matrix, int size);
int input_matrix(double** matrix, int size);
void output_matrix(double** matrix, int size);

int main() {



  return 0;
}

int matrix_size_input(int * rows, int *cols){
  int flag = 0;
  if(scanf("%d %d", rows, cols) == 2 && *rows == *cols) {
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