// Tyler Hayslett
// 2021-04-12
#ifndef matrix_functions
#define matrix_functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common_deffs.h"

// Matrix functions
matrix * new_matrix(int dimx, int dimy);
void free_matrix(matrix * oldmatrix);
matrix * sum_matrix(matrix * matrix_a, matrix * matrix_b);
matrix * mult_matrix(matrix * matrix_a, matrix * matrix_b);
void scale_matrix(matrix * matrix_a, float scalar);

// These are here because I dont think they quite belong in the net specific group
matrix * sigmoid_matrix(matrix * matrix_a);
matrix * sig_deriv_matrix(matrix * matrix_a);

#endif

