#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n);
int input(double ***matrix, int *n, int *m);
void output(double det);
void free_mem_array_of_pointers(double **a, int n);
void main() {
  double **a;
  int n, m;
  if (input(&a, &n, &m)) {
    if (n == m) {
      printf("%lf", det(a, n));
    } else {
      printf("n/a");
    }
  } else {
    printf("n/a");
  }
  for (int i = 0; i < n; i++) {
    free(a[i]);
  }
  free(a);
}

int input(double ***a, int *n, int *m) {
  int flag = 1;
  double x, res;
  res = scanf("%lf", &x);
  if (res == 1 && (int)x == x) {
    *n = (int)x;
  } else {
    flag = 0;
  }
  res = scanf("%lf", &x);
  if (res == 1 && (int)x == x) {
    *m = (int)x;
  } else {
    flag = 0;
  }
  if (flag) {
    *a = (double **)malloc((*n) * sizeof(double *));
    for (int i = 0; i < *n; i++) {
      (*a)[i] = (double *)malloc((*m) * sizeof(double));
    }

    for (int i = 0; i < *n; i++) {
      for (int j = 0; j < *m; j++) {
        res = scanf("%lf", &x);
        if (res == 1) {
          (*a)[i][j] = x;
        } else {
          flag = 0;
        }
      }
    }
  }
  return flag;
}

void free_mem_array_of_pointers(double **a, int n) {
  for (int i = 0; i < n; i++) {
    free(a[i]);
  }
  free(a);
}

double **get_matrix(double **a, int n, int _i, int _j) {
  double **tmp = (double **)malloc(n * sizeof(double *));
  for (int i = 0; i < n; i++) {
    tmp[i] = (double *)malloc(n * sizeof(double));
  }
  int x = 0, y = 0;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      if (i != _i && j != _j) {
        tmp[y][x] = a[i][j];
        x++;
        if (x == n) {
          x = 0;
          y++;
        }
      }
    }
  }
  return tmp;
}

double det(double **a, int n) {
  double sum = 0;
  if (n == 1) {
    sum = a[0][0];
  } else if (n == 2) {
    sum = (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
  } else {
    int sign = 1;
    for (int i = 0; i < n; i++) {
      double **matrix;
      matrix = get_matrix(a, n - 1, i, 0);
      sum += sign * a[i][0] * det(matrix, n - 1);
      sign = -sign;
      for (int i = 0; i < n - 1; i++) {
        free(matrix[i]);
      }
      free(matrix);
    }
  }
  return sum;
}
