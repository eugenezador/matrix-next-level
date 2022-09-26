#include <stdio.h>
#include <stdlib.h>

void invert(double **matrix, int n, double **result);
int input(double ***matrix, int *n, int *m);
void output(double **matrix, int n, int m);
void free_mem_array_of_pointers(double **a, int n);
int privedi(double **matrix, double **E, int n);
double det(double **matrix, int n);
int main() {
  double **a;
  int n, m;
  if (input(&a, &n, &m)) {
    if (n == m && det(a, n) != 0) {
      double **E;
      E = (double **)malloc(n * sizeof(double *));
      for (int i = 0; i < n; i++) {
        E[i] = (double *)malloc(n * sizeof(double));
      }
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (i == j) {
            E[i][j] = 1;
          } else {
            E[i][j] = 0;
          }
        }
      }
      if (privedi(a, E, n)) {
        invert(a, n, E);
        output(E, n, n);
      } else {
        printf("n/a");
      }
      free_mem_array_of_pointers(E, n);
    } else {
      printf("n/a");
    }
  } else {
    printf("n/a");
  }
  free_mem_array_of_pointers(a, n);
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

void output(double **a, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (j != m - 1) {
        printf("%.6lf ", a[i][j]);
      } else if (j == m - 1 && i != n - 1) {
        printf("%.6lf\n", a[i][j]);
      } else {
        printf("%.6lf", a[i][j]);
      }
    }
  }
}

int privedi(double **matrix, double **E, int size) {
  double tmp;
  int flag = 1;
  for (int i = 0; (i < size && flag); i++) {
    if (matrix[i][i] == 0) {
      flag = 0;
      for (int j = 0; (j < size && !flag); j++) {
        if (matrix[j][i] != 0) {
          flag = 1;
          for (int k = 0; k < size; k++) {
            tmp = matrix[i][k];
            matrix[i][k] = matrix[j][k];
            matrix[j][k] = tmp;
          }
          for (int k = 0; k < size; k++) {
            tmp = E[i][k];
            E[i][k] = E[j][k];
            E[j][k] = E[i][k];
          }
        }
      }
    }
  }
  return flag;
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

void invert(double **matrix, int n, double **result) {
  double umn;
  for (int cur = 0; cur < n; cur++) {
    double del = matrix[cur][cur];
    for (int j = 0; j < n; j++) {
      matrix[cur][j] /= del;
      result[cur][j] /= del;
    }
    for (int i = cur + 1; i < n; i++) {
      umn = matrix[i][cur];
      for (int j = 0; j < n; j++) {
        matrix[i][j] -= matrix[cur][j] * umn;
        result[i][j] -= result[cur][j] * umn;
      }
    }
  }
  for (int cur = n - 1; cur > 0; cur--) {
    for (int i = cur - 1; i >= 0; i--) {
      umn = matrix[i][cur];
      for (int j = 0; j < n; j++) {
        matrix[i][j] -= matrix[cur][j] * umn;
        result[i][j] -= result[cur][j] * umn;
      }
    }
  }
}
