#include <stdio.h>
#include <stdlib.h>

int matrix_size_input(int * rows, int *cols);
int** memory_allocation(int**matrix, int size);
int input_matrix(int** matrix, int size);
void output(int** matrix, int size);

int main() {
  int rows, cols;
  if(matrix_size_input(&rows, &cols)){
    if(input_matrix()){

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
  matrix = malloc(size * sizeof(int*) + size * 2 * sizeof(int));
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
      if(scanf("%d", &matrix[i][j] == 1)){
        flag = 1;
      }
    }
  }
  return flag;
}
void output(int** matrix, int size){
  for(int i = 0; i < size; i++) {
    printf("%d", matrix[i][0]);
    for(int j = 1; j < size; j++) {
      printf(" %d", matrix[i][j]);
    }
    printf("\n");
  }
}
