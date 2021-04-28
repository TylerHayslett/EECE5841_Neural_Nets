// Tyler Hayslett
// 2021-04-12
#ifndef matrix_functions
#define matrix_functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// I dont want to have to keep typing out unsigned char
typedef unsigned char BYTE;

// Structs for matrixes, I dont want to have to apass sizes manualy 
typedef struct matrix {
  int row_cnt;
  int col_cnt;
  float * data;
} matrix;

typedef struct matrix_set {
  int number_of_matrices;
  matrix ** set;
} matrix_set;

// Matrix creation/deletion functions
matrix * new_matrix(int row_cnt, int col_cnt);
matrix * const_matrix(int row_cnt, int col_cnt, float constant);
matrix * rand_matrix(int row_cnt, int col_cnt, float range);
matrix_set * new_matrix_set(int size_of_set);
void free_matrix(matrix * oldmatrix);
void free_matrix_set(matrix_set * oldmatrix_set);

// Dual Matrix operation functions
matrix * sum_matrix(matrix * matrix_a, matrix * matrix_b);
matrix * dif_matrix(matrix * matrix_a, matrix * matrix_b);
matrix * mult_matrix(matrix * matrix_a, matrix * matrix_b);
matrix * hadamard_matrix(matrix * matrix_a, matrix * matrix_b);

// Single matrix operation functions
matrix * scale_matrix(matrix * matrix_a, float scalar);
matrix * transpose_matrix(matrix * matrix_a);
matrix * sigmoid_matrix(matrix * matrix_a);
matrix * sig_deriv_matrix(matrix * matrix_a);
matrix * ReLU_matrix(matrix * matrix_a);
matrix * ReLU_deriv_matrix(matrix * matrix_a);
void print_matrix(matrix * matrix_a);
void fprint_matrix(FILE * oFile, matrix * matrix_a);

#endif

