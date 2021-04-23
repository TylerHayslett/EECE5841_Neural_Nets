// Tyler Hayslett
// 2021-04-12
#ifndef matrix_functions
#define matrix_functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common.h"

typedef unsigned char BYTE;

typedef struct matrix {
  int row_cnt;
  int col_cnt;
  float * data;
} matrix;

typedef struct matrix_set {
  int number_of_matrices;
  matrix ** set;
} matrix_set;


// Read from data file and write to pgm
int imageread(char s[], matrix * result, int index);
int imagewrite(char s[], matrix * image_matrix);


// Matrix creation/deletion functions
matrix * new_matrix(int row_cnt, int col_cnt);
matrix_set * new_matrix_set(int size_of_set);
void free_matrix(matrix * oldmatrix);
void free_matrix_set(matrix_set * oldmatrix_set);

// Matrix operation functions
void rand_matrix(matrix * matrix_a, float range);
void sum_matrix(matrix * result, matrix * matrix_a, matrix * matrix_b);
void dif_matrix(matrix * result, matrix * matrix_a, matrix * matrix_b);
void mult_matrix(matrix * result, matrix * matrix_a, matrix * matrix_b);
void hadamard_matrix(matrix * result, matrix * matrix_a, matrix * matrix_b);
void scale_matrix(matrix * result, matrix * matrix_a, float scalar);
void transpose_matrix(matrix * result, matrix * matrix_a);

// These are here because I dont think they quite belong in either specific group
void sigmoid_matrix(matrix * result, matrix * matrix_a);
void sig_deriv_matrix(matrix * result, matrix * matrix_a);
void print_matrix(matrix * matrix_a);

#endif

