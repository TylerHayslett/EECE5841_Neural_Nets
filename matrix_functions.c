#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image_functions.h"
#include "matrix_functions.h"

// Matrix functions
void new_matrix(matrix * result, int dimx, int dimy){
  
}

void sum_matrix(matrix * result, matrix * matrix_a, matrix * matrix_b){
  if (matrix_a->dimrow == matrix_b->dimrow){
    if (matrix_a->dimcol == matrix_b->dimcol){
      result->dimrow = matrix_a->dimrow;
      result->dimcol = matrix_a->dimcol;
      float * temp = malloc((matrix_a->dimrow) * (matrix_a->dimcol) * sizeof(float));
      int i;
      for(i = 0; i < ((matrix_a->dimrow) * (matrix_a->dimcol)); i++){
        temp[i] = matrix_a->data[i] + matrix_b->data[i];
      }
      result->data = temp;
    }
  }
}

void mult_matrix(matrix * result, matrix * matrix_a, matrix * matrix_b){
  printf("Setting up sum\n");
  if (matrix_a->dimrow == matrix_b->dimrow){
    if (matrix_a->dimcol == matrix_b->dimcol){
      result->dimrow = matrix_b->dimrow;
      result->dimcol = matrix_b->dimcol;
      result->data = malloc((matrix_b->dimrow) * (matrix_b->dimcol) * sizeof(float));
      int i;
      printf("Summing\n");
      for(i = 0; i < ((matrix_b->dimrow) * (matrix_b->dimcol)); i++){
        result->data[i] = matrix_a->data[i] + matrix_b->data[i];
      }
    }
  }
}

void scale_matrix(matrix * result, matrix * matrix_a, float scalar){
  result->dimrow = matrix_a->dimrow;
  result->dimcol = matrix_a->dimcol;
  float * temp = malloc((matrix_a->dimrow) * (matrix_a->dimcol) * sizeof(float));
  int i;
  for(i = 0; i < ((matrix_a->dimrow) * (matrix_a->dimcol)); i++){
    temp[i] = matrix_a->data[i] * scalar;
  }
  result->data = temp;
}

// These are here because I dont think they quite belong in the net specific group
void sigmoid_matrix(matrix * result, matrix * matrix_a){
  
}
void sig_deriv_matrix(matrix * result, matrix * matrix_a){
  
}
