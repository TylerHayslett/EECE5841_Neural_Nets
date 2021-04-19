// Tyler Hayslett
// 2021-04-12
#ifndef matrix_functions
#define matrix_functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common_deffs.h"

// Matrix creation/deletion functions
matrix * new_matrix(int dimx, int dimy);
matrix * rand_matrix(int dimx, int dimy, float range);
void free_matrix(matrix * oldmatrix);
void free_matrix_set(matrix_set * oldmatrix_set);

// Matrix operation functions
matrix * sum_matrix(matrix * matrix_a, matrix * matrix_b);
matrix * mult_matrix(matrix * matrix_a, matrix * matrix_b);
matrix * hadamard_matrix(matrix * matrix_a, matrix * matrix_b);
void scale_matrix(matrix * matrix_a, float scalar);
matrix * transpose_matrix(matrix * matrix_a);

// These are here because I dont think they quite belong in either specific group
matrix * sigmoid_matrix(matrix * matrix_a);
matrix * sig_deriv_matrix(matrix * matrix_a);
void print_matrix(matrix * matrix_a);

#endif

