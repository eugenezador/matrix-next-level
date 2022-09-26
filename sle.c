#include <stdio.h>
#include <stdlib.h>

void sle(double **matrix, int n, int m);
double det(double **matrix, int n);
int input(double ***matrix, int *n, int *m);
void output(double det);
void free_mem_array_of_pointers(double **a, int n);

int main() {
  double **a;
  int n, m;
  if (input(&a, &n, &m)) {
    sle(a, n, m);
  } else {
    printf("n/a");
  }
  for (int i = 0; i < n; i++) {
    free(a[i]);
  }
  free(a);
  return 0;
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

void sle(double **matrix, int n, int m) {
  double **tmp = (double **)malloc(n * sizeof(double *));
  for (int j = 0; j < n; j++) {
    tmp[j] = (double *)malloc(n * sizeof(double *));
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      tmp[i][j] = matrix[i][j];
    }
  }
  double d = det(tmp, n);
  for (int j = 0; j < n; j++) {
    free(tmp[j]);
  }
  free(tmp);
  if (d == 0) {
    printf("n/a");
  } else {
    for (int i = 0; i < n; i++) {
      double **res = (double **)malloc(n * sizeof(double *));
      for (int j = 0; j < n; j++) {
        res[j] = (double *)malloc(n * sizeof(double));
      }
      for (int k = 0; k < n; k++) {
        res[k][i] = matrix[k][m - 1];
      }
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          if (k != i) {
            res[j][k] = matrix[j][k];
          }
        }
      }
      if (i != n - 1) {
        printf("%.6lf ", det(res, n)/d);
      } else {
        printf("%.6lf", det(res, n)/d);
      }
      for (int j = 0; j < n; j++) {
        free(res[j]);
      }
      free(res);
    }
  }
}
