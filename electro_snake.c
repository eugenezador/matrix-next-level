#include <stdio.h>
#include <stdlib.h>
/*
    1 6 7
    2 5 8
    3 4 9
*/
void sort_vertical(int **matrix, int n, int m, int ***result_matrix);
int input_dinamic_array_of_pointers(int ***a, int *n, int *m);
void output_dinamic(int **a, int n, int m);
void free_mem_array_of_pointers(int **a, int n);
void sort_horizontal(int **matrix, int n, int m, int ***result_matrix);

void input(int **matrix, int *n, int *m);
void output(int **matrix, int n, int m);

int main() {
  int **matrix, **result;
  int n, m;

  if (input_dinamic_array_of_pointers(&matrix, &n, &m)) {
    if (n != 0 && m != 0) {
      sort_vertical(matrix, n, m, &result);
      output_dinamic(result, n, m);
      printf("\n\n");
      free_mem_array_of_pointers(result, n);
      sort_horizontal(matrix, n, m, &result);
      output_dinamic(result, n, m);
      free_mem_array_of_pointers(matrix, n);
      free_mem_array_of_pointers(result, n);
    } else {
      free_mem_array_of_pointers(matrix, n);
      printf("n/a");
    }
  } else {
    printf("n/a");
    free_mem_array_of_pointers(matrix, n);
  }

  return 0;
}

int input_dinamic_array_of_pointers(int ***a, int *n, int *m) {
  int flag = 1;
  float x, res;
  res = scanf("%f", &x);
  if (res == 1 && (int)x == x) {
    *n = (int)x;
  } else {
    flag = 0;
  }
  res = scanf("%f", &x);
  if (res == 1 && (int)x == x) {
    *m = (int)x;
  } else {
    flag = 0;
  }
  if (flag) {
    *a = (int **)malloc((*n) * sizeof(int *));
    for (int i = 0; i < *n; i++) {
      (*a)[i] = (int *)malloc((*m) * sizeof(int));
    }

    for (int i = 0; i < *n; i++) {
      for (int j = 0; j < *m; j++) {
        res = scanf("%f", &x);
        if (res == 1 && (int)x == x) {
          (*a)[i][j] = (int)x;
        } else {
          flag = 0;
        }
      }
    }
  }
  return flag;
}

void output_dinamic(int **a, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (j != m - 1) {
        printf("%d ", a[i][j]);
      } else if (j == m - 1 && i != n - 1) {
        printf("%d\n", a[i][j]);
      } else {
        printf("%d", a[i][j]);
      }
    }
  }
}

void free_mem_array_of_pointers(int **a, int n) {
  for (int i = 0; i < n; i++) {
    free(a[i]);
  }
  free(a);
}

void sort_vertical(int **matrix, int n, int m, int ***result_matrix) {
  int *tmp = (int *)malloc(n * m * sizeof(int));
  int k = n * m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      tmp[m * i + j] = matrix[i][j];
    }
  }

  for (int i = 0; i < k; i++) {
    for (int j = 0; j < k - 1 - i; j++) {
      if (tmp[k] > tmp[k + 1]) {
        int t = tmp[k];
        tmp[k] = tmp[k + 1];
        tmp[k + 1] = t;
      }
    }
  }

  *result_matrix = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    (*result_matrix)[i] = (int *)malloc(m * sizeof(int));
  }
  int y = 0;
  for (int j = 0; j < m; j++) {
    if (j % 2 == 0) {
      for (int i = 0; i < n; i++) {
        (*result_matrix)[i][j] = tmp[y++];
      }
    } else {
      for (int i = n - 1; i >= 0; i--) {
        (*result_matrix)[i][j] = tmp[y++];
      }
    }
  }
  free(tmp);
}

void sort_horizontal(int **matrix, int n, int m, int ***result_matrix) {
  int *tmp = (int *)malloc(n * m * sizeof(int));
  int k = n * m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      tmp[m * i + j] = matrix[i][j];
    }
  }

  for (int i = 0; i < k; i++) {
    for (int j = 0; j < k - 1 - i; j++) {
      if (tmp[k] > tmp[k + 1]) {
        int t = tmp[k];
        tmp[k] = tmp[k + 1];
        tmp[k + 1] = t;
      }
    }
  }

  *result_matrix = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    (*result_matrix)[i] = (int *)malloc(m * sizeof(int));
  }
  int y = 0;
  for (int i = 0; i < n; i++) {
    if (i % 2 == 0) {
      for (int j = 0; j < m; j++) {
        (*result_matrix)[i][j] = tmp[y++];
      }
    } else {
      for (int j = m - 1; j >= 0; j--) {
        (*result_matrix)[i][j] = tmp[y++];
      }
    }
  }
  free(tmp);
}
