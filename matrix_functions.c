#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image_functions.h"
#include "matrix_functions.h"

// Matrix functions
matrix * new_matrix(int row_cnt, int col_cnt){
  matrix * new_mat = malloc(sizeof(matrix));
  new_mat->row_cnt = row_cnt;
  new_mat->col_cnt = col_cnt;
  new_mat->data = calloc(row_cnt*col_cnt, sizeof(float));
  return new_mat;
}

matrix * rand_matrix(int row_cnt, int col_cnt, float range){
  int i;
  matrix * new_mat = malloc(sizeof(matrix));
  new_mat->row_cnt = row_cnt;
  new_mat->col_cnt = col_cnt;
  new_mat->data = malloc(row_cnt*col_cnt*sizeof(float));
  
  for(i = 0; i < row_cnt*col_cnt; i++){
    new_mat->data[i] = ((2 * ((float)rand()) - RAND_MAX)/RAND_MAX) * range;;
  }
  
  return new_mat;
}

void free_matrix(matrix * oldmatrix){
  free(oldmatrix->data);
  free(oldmatrix);
}

void free_matrix_set(matrix * oldmatrix_set){
  int i = 0;
  for(i = 0; i < oldmatrix_set->number_of_matrices; i++){
    free_matrix(oldmatrix_set->set[i]);
  }
  free(oldmatrix_set);
}

matrix * sum_matrix(matrix * matrix_a, matrix * matrix_b){
  int i;
  if (matrix_a->col_cnt == matrix_b->col_cnt){
    if (matrix_a->row_cnt == matrix_b->row_cnt){
      matrix * result = new_matrix(matrix_a->row_cnt, matrix_a->col_cnt);
      
      for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
        result->data[i] = matrix_a->data[i] + matrix_b->data[i];
      }
      return result;
    }
  }
  return 0;
}

matrix * mult_matrix(matrix * matrix_a, matrix * matrix_b){ 
  if (matrix_a->col_cnt == matrix_b->row_cnt){
    matrix * result = new_matrix(matrix_b->row_cnt, matrix_a->col_cnt);
    
    int i, k, j;
    for(i = 0; i < matrix_b->col_cnt; i++){
      for(k = 0; k < matrix_a->row_cnt; k++){
        for(j = 0; j < matrix_a->col_cnt; j++){
          result->data[i + (k * matrix_b->col_cnt)] += 
              matrix_a->data[j + (k * matrix_a->col_cnt)] * 
              matrix_b->data[i + (j * matrix_b->col_cnt)];
        }
      }
    }
    return result;
  }
  return 0;
}

matrix * hadamard_matrix(matrix * matrix_a, matrix * matrix_b){ 
  int i;
  if (matrix_a->col_cnt == matrix_b->col_cnt){
    if (matrix_a->row_cnt == matrix_b->row_cnt){
      matrix * result = new_matrix(matrix_a->row_cnt, matrix_a->col_cnt);
      
      for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
        result->data[i] = matrix_a->data[i] * matrix_b->data[i];
      }
      return result;
    }
  }
  return 0;
}

void scale_matrix(matrix * matrix_a, float scalar){
  int i;
  for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
    matrix_a->data[i] = matrix_a->data[i] * scalar;
  }
}

matrix * transpose_matrix(matrix * matrix_a){
  int i, row, col;
  matrix * result = new_matrix(matrix_a->col_cnt, matrix_a->row_cnt);
  
  for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
    col = i % matrix_a->row_cnt;
    row = (int) floor(i / matrix_a->row_cnt);
    
    result->data[i] = matrix_a->data[col*matrix_a->col_cnt + row];
  }
  return result;
}

// These are here because I dont think they quite belong in the net specific group
matrix * sigmoid_matrix(matrix * matrix_a){
  matrix * result = new_matrix(matrix_a->row_cnt, matrix_a->col_cnt);
  
  int i;
  for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
    result->data[i] = 1 / (1 + exp(-matrix_a->data[i]));
  }
  return result;
}

matrix * sig_deriv_matrix(matrix * matrix_a){
  matrix * result = new_matrix(matrix_a->row_cnt, matrix_a->col_cnt);
  
  int i;
  float sig;
  for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
    sig = 1 / (1 + exp(-matrix_a->data[i]));
    result->data[i] = sig * (1 - sig);
  }
  return result;
}

void print_matrix(matrix * matrix_a){
  int row, col;
  
  for(row = 0; row < matrix_a->row_cnt; row++){
    printf("[");
    for(col = 0; col < (matrix_a->col_cnt - 1); col++){
      printf("%f,", matrix_a->data[col + row*matrix_a->col_cnt]);
    }
    printf("%f]\n",matrix_a->data[col + row*matrix_a->col_cnt]);
  }
}
