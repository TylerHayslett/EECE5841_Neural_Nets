#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix_functions.h"

// Matrix functions
matrix * new_matrix(int row_cnt, int col_cnt){
  matrix * new_mat = malloc(sizeof(matrix));
  new_mat->row_cnt = row_cnt;
  new_mat->col_cnt = col_cnt;
  new_mat->data = calloc(row_cnt*col_cnt, sizeof(float));
  return new_mat;
}

matrix_set * new_matrix_set(int size_of_set){
  matrix_set * new_set = malloc(sizeof(matrix_set));
  new_set->number_of_matrices = size_of_set;
  new_mat->set = malloc(size_of_set*sizeof(matrix *));
  return new_set;
}

void free_matrix(matrix * oldmatrix){
  free(oldmatrix->data);
  free(oldmatrix);
}

void free_matrix_set(matrix_set * oldmatrix_set){
  int i = 0;
  for(i = 0; i < oldmatrix_set->number_of_matrices; i++){
    free_matrix(oldmatrix_set->set[i]);
  }
  free(oldmatrix_set);
}




void rand_matrix(matrix * matrix_a, float range){
  int i;
  for(i = 0; i < (matrix_a->row_cnt * matrix_a->col_cnt); i++){
    matrix_a->data[i] = ((2 * ((float)rand()) - RAND_MAX)/RAND_MAX) * range;
  }
}

void sum_matrix(matrix * result, matrix * matrix_a, matrix * matrix_b){
  int i;
  if (matrix_a->col_cnt == matrix_b->col_cnt){
    if (matrix_a->row_cnt == matrix_b->row_cnt){
      matrix * sum = new_matrix(matrix_a->row_cnt, matrix_a->col_cnt);
      
      for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
        sum->data[i] = matrix_a->data[i] + matrix_b->data[i];
      }
      
      free_matrix(result);
      result = sum;
    }
  }
  printf("Matrices different sizes, cant element-wise sum\n");
  printf("%d %d\n", matrix_a->row_cnt, matrix_a->col_cnt);
  printf("%d %d\n", matrix_b->row_cnt, matrix_b->col_cnt);
  return 0;
}

void dif_matrix(matrix * result, matrix * matrix_a, matrix * matrix_b){
  int i;
  if (matrix_a->col_cnt == matrix_b->col_cnt){
    if (matrix_a->row_cnt == matrix_b->row_cnt){
      matrix * diff = new_matrix(matrix_a->row_cnt, matrix_a->col_cnt);
      
      for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
        diff->data[i] = matrix_a->data[i] - matrix_b->data[i];
      }
      
      free_matrix(result);
      result = diff;
    }
  }
  printf("Matrices different sizes, cant element-wise dif\n");
  printf("%d %d\n", matrix_a->row_cnt, matrix_a->col_cnt);
  printf("%d %d\n", matrix_b->row_cnt, matrix_b->col_cnt);
  return 0;
}

void mult_matrix(matrix * result, matrix * matrix_a, matrix * matrix_b){ 
  if (matrix_a->col_cnt == matrix_b->row_cnt){
    matrix * product = new_matrix(matrix_a->row_cnt, matrix_b->col_cnt);
    
    int i, k, j;
    for(i = 0; i < matrix_b->col_cnt; i++){
      for(k = 0; k < matrix_a->row_cnt; k++){
        for(j = 0; j < matrix_a->col_cnt; j++){
          product->data[i + (k * matrix_b->col_cnt)] += 
              matrix_a->data[j + (k * matrix_a->col_cnt)] * 
              matrix_b->data[i + (j * matrix_b->col_cnt)];
        }
      }
    }
    
    free_matrix(result);
    result = product;
  } 
  printf("Matrix Multiplication failed, wrong sizes \n");
  printf("%d %d\n", matrix_a->row_cnt, matrix_a->col_cnt);
  printf("%d %d\n", matrix_b->row_cnt, matrix_b->col_cnt);
  return 0;
}

void hadamard_matrix(matrix * result, matrix * matrix_a, matrix * matrix_b){ 
  int i;
  if (matrix_a->col_cnt == matrix_b->col_cnt){
    if (matrix_a->row_cnt == matrix_b->row_cnt){
      matrix * hadamard = new_matrix(matrix_a->row_cnt, matrix_a->col_cnt);
      
      for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
        hadamard->data[i] = matrix_a->data[i] * matrix_b->data[i];
      }
      
      free_matrix(result);
      result = hadamard;
    }
  }
  printf("Hadamard failed, incorrect sizes\n");
  printf("%d %d\n", matrix_a->row_cnt, matrix_a->col_cnt);
  printf("%d %d\n", matrix_b->row_cnt, matrix_b->col_cnt);
  return 0;
}

void scale_matrix(matrix * result, matrix * matrix_a, float scalar){
  int i;
  for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
    result->data[i] = matrix_a->data[i] * scalar;
  }
}

void transpose_matrix(matrix * result, matrix * matrix_a){
  int i, row, col;
  matrix * transpose = new_matrix(matrix_a->col_cnt, matrix_a->row_cnt);
  
  for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
    col = i % matrix_a->row_cnt;
    row = (int) floor(i / matrix_a->row_cnt);
    
    transpose->data[i] = matrix_a->data[col*matrix_a->col_cnt + row];
  }
  
  free_matrix(result);
  result = transpose;
}

// These are here because I dont think they quite belong in the net specific group
void sigmoid_matrix(matrix * result, matrix * matrix_a){
  matrix * siged = new_matrix(matrix_a->row_cnt, matrix_a->col_cnt);
  
  int i;
  for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
    siged->data[i] = 1 / (1 + exp(-matrix_a->data[i]));
  }
  
  free_matrix(result);
  result = siged;
}

void sig_deriv_matrix(matrix * result, matrix * matrix_a){
  matrix * sigderv = new_matrix(matrix_a->row_cnt, matrix_a->col_cnt);
  
  int i;
  float sig;
  for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
    sig = 1 / (1 + exp(-matrix_a->data[i]));
    sigderv->data[i] = sig * (1 - sig);
  }
  
  free_matrix(result);
  result = sigderv;
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
  printf("\n");
}
