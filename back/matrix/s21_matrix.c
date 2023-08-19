#include "s21_matrix.h"

#include <math.h>

static int check_bad_matrix(matrix_t *M) {
  return (M->rows <= 0 || M->columns <= 0)
             ? ARITHMETIC_ERROR
             : OK;
}
static int s21_check_matrix(matrix_t *A) {
    return A != NULL && (A->rows > 0) && (A->columns > 0);
}
static int check_bad_eq_matrix(matrix_t *M1, matrix_t *M2) {
  int res = OK;
  if (!(check_bad_matrix(M1) || check_bad_matrix(M2))) {
    res = (M1->rows == M2->rows && M1->columns == M2->columns)
              ? OK
              : ARITHMETIC_ERROR;
  } else {
    res = INVALID_MATRIX;
  }

  return res;
}



int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;

  if ((A->rows && B->rows) &&
      A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < A->rows && res; i++)
      for (int j = 0; j < A->columns && res; j++)
        if (fabs((A->matrix[i][j]) - (B->matrix[i][j])) > 1e-7) res = FAILURE;
  } else
    res = FAILURE;
  return res;
}

matrix_t s21_create_matrix() {
    matrix_t matrix;
    matrix.rows = 4;
    matrix.columns = 4;
    for (int i  = 0; i < matrix.rows;i++){
        for (int j = 0; j < matrix.columns; j++){
            matrix.matrix[i][j] = 0;
        }
    }
    return matrix;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = check_bad_eq_matrix(A, B);
  if (res == OK) {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = check_bad_eq_matrix(A, B);
  if (res == OK) {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (check_bad_matrix(A) || result == NULL) {
    res = INVALID_MATRIX;
  } else {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] * number;
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;

  if (check_bad_matrix(A) || check_bad_matrix(B) || result == NULL) {
    res = INVALID_MATRIX;
  } else if (A->columns != B->rows) {
    res = ARITHMETIC_ERROR;
  } else {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
  }
  return res;
}

static void s21_minor(matrix_t *A, matrix_t *result, int row_alem,
                      int column_alem) {
  if (A->rows == A->columns) {
    s21_create_matrix(A->rows - 1, A->columns - 1, result);
    for (int i = 0, k = 0; i < result->rows; i++, k++) {
      if (i == row_alem) k++;
      for (int j = 0, m = 0; j < result->columns; j++, m++) {
        if (j == column_alem) m++;
        result->matrix[i][j] = A->matrix[k][m];
      }
    }
  }
}

int s21_determinant(matrix_t *A, double *result) {
  int res = OK;
  if (check_bad_matrix(A) || result == NULL) {
    res = INVALID_MATRIX;
  } else {
    if (A->rows == A->columns) {
      if (A->rows == 1)
        *result = A->matrix[0][0];
      else if (A->rows == 2) {
        *result = (A->matrix[0][0] * A->matrix[1][1] -
                   A->matrix[1][0] * A->matrix[0][1]);
      } else {
        *result = 0;
        matrix_t min = {0};
        double alem = 0;
        double determ = 0;
        for (int i = 0; i < A->rows; i++) {
          alem = i % 2 ? -A->matrix[0][i] : A->matrix[0][i];
          s21_minor(A, &min, 0, i);
          s21_determinant(&min, &determ);
          *result += alem * determ;
        }
      }
    } else {
      res = ARITHMETIC_ERROR;
    }
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (check_bad_matrix(A) || result == NULL) return INVALID_MATRIX;
  int res = 0;
  if (A->rows == A->columns) {
    matrix_t temp = {0};
    double det = 0;
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        s21_minor(A, &temp, i, j);
        s21_determinant(&temp, &det);
        result->matrix[i][j] = (i + j) % 2 ? -det : det;
      }
  } else {
    res = ARITHMETIC_ERROR;
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (check_bad_matrix(A) || result == NULL) return INVALID_MATRIX;
  for (int i = 0; i < result->rows; i++)
    for (int j = 0; j < result->columns; j++)
      result->matrix[i][j] = A->matrix[j][i];
  return OK;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int error = INVALID_MATRIX;

    if (A->rows != A->columns) {
        error = ARITHMETIC_ERROR;
    } else if (s21_check_matrix(A)) {
        error = OK;
        double det = 0.0;
        matrix_t calc = s21_create_matrix();
        matrix_t transp = s21_create_matrix();
        s21_determinant(A, &det);
        if (det != 0) {
            s21_calc_complements(A, &calc);
            s21_transpose(&calc, &transp);
            for (int i = 0; i < transp.rows; i++) {
                for (int j = 0; j < transp.columns; j++) {
                    result->matrix[i][j] = (1 / det) * transp.matrix[i][j];
                }
            }
        } else {
            error = ARITHMETIC_ERROR;
        }
    }
    return error;
}
