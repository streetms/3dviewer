#ifndef SRC_S21_MATRIX_H
#define SRC_S21_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix_struct {
  double matrix[4][4];
  int rows;
  int columns;
} matrix_t;

#define SUCCESS 1
#define FAILURE 0
#define OK 0
#define INVALID_MATRIX 1
#define ARITHMETIC_ERROR 2
#ifdef __cplusplus
extern "C" {
#endif
//void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
matrix_t  s21_create_matrix();
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
#ifdef __cplusplus
}
#endif
#endif  // SRC_S21_MATRIX_H
