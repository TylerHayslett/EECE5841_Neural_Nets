// Tyler Hayslett
// 2021-04-12
#ifndef matrix_functions
#define matrix_functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common_deffs.h"

// Conversion functions
void image_to_matrix(BYTE * image_char, matrix &result);
void matrix_to_image(matrix &matrix, char s[]); // generates an image file from martix

// Matrix functions
void new_matrix(matrix &result, int dimx, int dimy);
void sum_matrix(matrix &result, matrix &matrix_a, matrix &matrix_b);
void mult_matrix(matrix &result, matrix &matrix_a, matrix &matrix_b);
void div_matrix(matrix &result, matrix &matrix_a, float denominator);

// These are here because I dont think they quite belong in the net specific group
void sigmoid_matrix(matrix &result, matrix &matrix_a);
void sig_deriv_matrix(matrix &result, matrix &matrix_a);

#endif

