#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix_functions.h"

// Matrix functions

// Matrix constructor, initialized to all 0's
matrix * new_matrix(int row_cnt, int col_cnt){
  matrix * new_mat = malloc(sizeof(matrix));
  new_mat->row_cnt = row_cnt;
  new_mat->col_cnt = col_cnt;
  new_mat->data = calloc(row_cnt*col_cnt, sizeof(float));
  return new_mat;
}

// Matrix constructor, initialized to a constant
matrix * const_matrix(int row_cnt, int col_cnt, float constant){
  matrix * new_mat = malloc(sizeof(matrix));
  new_mat->row_cnt = row_cnt;
  new_mat->col_cnt = col_cnt;
  new_mat->data = calloc(row_cnt*col_cnt, sizeof(float));
  
  for(int i = 0; i < row_cnt*col_cnt; i++){
    new_mat->data[i] = constant;
  }
  return new_mat;
}

// Matrix constructor, initialized to a random value in [-range, range]
matrix * rand_matrix(int row_cnt, int col_cnt, float range){
  int i;
  matrix * new_mat = malloc(sizeof(matrix));
  new_mat->row_cnt = row_cnt;
  new_mat->col_cnt = col_cnt;
  new_mat->data = malloc(row_cnt*col_cnt*sizeof(float));
  
  for(i = 0; i < row_cnt*col_cnt; i++){
    new_mat->data[i] = ((2 * ((float)rand()) - RAND_MAX)/RAND_MAX) * range;
  }
  
  return new_mat;
}

// Constructor for a matrix set, matrixes themselves not constructed
matrix_set * new_matrix_set(int size_of_set){
  matrix_set * new_set = malloc(sizeof(matrix_set));
  new_set->number_of_matrices = size_of_set;
  new_set->set = malloc(size_of_set*sizeof(matrix *));
  return new_set;
}

// Destructor for a matrix
void free_matrix(matrix * oldmatrix){
  free(oldmatrix->data);
  free(oldmatrix);
}

// Destructor for a matrix set
void free_matrix_set(matrix_set * oldmatrix_set){
  int i = 0;
  for(i = 0; i < oldmatrix_set->number_of_matrices; i++){
    free_matrix(oldmatrix_set->set[i]);
  }
  free(oldmatrix_set);
}



// Almost all of the following functions dynamically allocat memory for their output
// This is not best practice in C, as it requires thought to not have memory leaks
// I tried to fix this but got lost and ran out of time. c'est la vie


// Takes two matrices of equal size and elementwise sums them
// A + B = C
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
  printf("Matrices different sizes, cant sum\n");
  printf("%d %d\n", matrix_a->row_cnt, matrix_a->col_cnt);
  printf("%d %d\n", matrix_b->row_cnt, matrix_b->col_cnt);
  return 0;
}

// Similar to sum, except the elementwise difference
// A - B = C
matrix * dif_matrix(matrix * matrix_a, matrix * matrix_b){
  int i;
  if (matrix_a->col_cnt == matrix_b->col_cnt){
    if (matrix_a->row_cnt == matrix_b->row_cnt){
      matrix * result = new_matrix(matrix_a->row_cnt, matrix_a->col_cnt);
      
      for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
        result->data[i] = matrix_a->data[i] - matrix_b->data[i];
      }
      return result;
    }
  }
  printf("Matrices different sizes, cant dif\n");
  printf("%d %d\n", matrix_a->row_cnt, matrix_a->col_cnt);
  printf("%d %d\n", matrix_b->row_cnt, matrix_b->col_cnt);
  return 0;
}

// This is a matrix multiplication, make sure your dimensions are correct
// A * B = C
matrix * mult_matrix(matrix * matrix_a, matrix * matrix_b){ 
  //printf("%d %d\n", matrix_a->row_cnt, matrix_a->col_cnt);
  //printf("%d %d\n\n", matrix_b->row_cnt, matrix_b->col_cnt);
  if (matrix_a->col_cnt == matrix_b->row_cnt){
    matrix * result = new_matrix(matrix_a->row_cnt, matrix_b->col_cnt);
    
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
  printf("Matrix Multiplication failed, wrong sizes \n");
  printf("%d %d\n", matrix_a->row_cnt, matrix_a->col_cnt);
  printf("%d %d\n", matrix_b->row_cnt, matrix_b->col_cnt);
  return 0;
}

// This is a elementwise multiplication of two same-size matrices
// Hadamard product
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
  printf("Hadamard failed\n");
  printf("%d %d\n", matrix_a->row_cnt, matrix_a->col_cnt);
  printf("%d %d\n", matrix_b->row_cnt, matrix_b->col_cnt);
  return 0;
}


// Single matrix functions


// Scales matrix by scalar
matrix * scale_matrix(matrix * matrix_a, float scalar){
  int i;
  matrix * result = new_matrix(matrix_a->row_cnt, matrix_a->col_cnt);
  for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
    result->data[i] = matrix_a->data[i] * scalar;
  }
  return result;
}

// Returns the transpose of the matrix
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

// Returns the element-wize sigmoid function of the matrix
matrix * sigmoid_matrix(matrix * matrix_a){
  matrix * result = new_matrix(matrix_a->row_cnt, matrix_a->col_cnt);
  
  int i;
  for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
    result->data[i] = 1 / (1 + exp(-matrix_a->data[i]));
  }
  return result;
}

// Returns the element-wize sigmoid-derivative function of the matrix
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

// Returns the element-wize Rectifying Linear Unit function of the matrix
matrix * ReLU_matrix(matrix * matrix_a){
  matrix * result = new_matrix(matrix_a->row_cnt, matrix_a->col_cnt);
  
  int i;
  for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
    if (matrix_a->data[i] > 0){
      result->data[i] = matrix_a->data[i];
    } else {
      result->data[i] = 0;
    }
  }
  return result;
}

// Returns the element-wize Rectifying Linear Unit derivative function of the matrix
matrix * ReLU_deriv_matrix(matrix * matrix_a){
  matrix * result = new_matrix(matrix_a->row_cnt, matrix_a->col_cnt);
  
  int i;
  for(i = 0; i < ((matrix_a->col_cnt) * (matrix_a->row_cnt)); i++){
    if (matrix_a->data[i] > 0){
      result->data[i] = 1.0;
    } else {
      result->data[i] = 0;
    }
  }
  return result;
}


// These functions print a bracketed matrix to a file or to the console
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

void fprint_matrix(FILE * oFile, matrix * matrix_a){
  int row, col;
  
  for(row = 0; row < matrix_a->row_cnt; row++){
    fprintf(oFile, "[");
    for(col = 0; col < (matrix_a->col_cnt - 1); col++){
      fprintf(oFile, "%f,", matrix_a->data[col + row*matrix_a->col_cnt]);
    }
    fprintf(oFile, "%f]\n",matrix_a->data[col + row*matrix_a->col_cnt]);
  }
  fprintf(oFile, "\n");
}
