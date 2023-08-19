// #include <dirent.h>

#include "float.h"
#include "s21_matrix.h"
double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}
void print(matrix_t m) {
  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.columns; j++) {
      printf("%g ", (m.matrix)[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int rows = 3;
  int cols = 3;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(0, 10);
      mtx.matrix[i][j] = get_rand(0, 10);
      check.matrix[i][j] = m.matrix[i][j] + mtx.matrix[i][j];
    }
  }
  matrix_t res = {0};

  s21_sum_matrix(&m, &mtx, &res);

  printf("%d\n", res.rows);

  if (s21_eq_matrix(&check, &res) == SUCCESS) {
    printf("OK\n");
  } else {
    printf("fail");
  }

  return 0;
}