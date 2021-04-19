#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common_deffs.h"
#include "matrix_functions.h"

matrix_set * WEIGHTS;
matrix_set * BIASES;
matrix_set * ACTIVATIONS;
matrix_set * ERRORS;
matrix_set * GRADIENT;


// assuming input will be one single full length column
void setup_network(int input_size, int number_of_hidden_layers, int nodes_per_layer, int output_size){
  int i;
  
  WEIGHTS->number_of_matrices = (number_of_hidden_layers + 1);
  BIASES->number_of_matrices = (number_of_hidden_layers + 1);
  ACTIVATIONS->number_of_matrices = (number_of_hidden_layers + 1);
  ERRORS->number_of_matrices = (number_of_hidden_layers + 1);
  GRADIENT->number_of_matrices = (number_of_hidden_layers + 1);
  
  WEIGHTS->set = malloc(sizeof(matrix *)*(number_of_hidden_layers + 1));
  BIASES->set = malloc(sizeof(matrix *)*(number_of_hidden_layers + 1));
  ACTIVATIONS->set = malloc(sizeof(matrix *)*(number_of_hidden_layers + 1));
  ERRORS->set = malloc(sizeof(matrix *)*(number_of_hidden_layers + 1));
  GRADIENT->set = malloc(sizeof(matrix *)*(number_of_hidden_layers + 1));
  
  for(i = 0; i < (number_of_hidden_layers + 1); i++){
    WEIGHTS->set[i] = ;
  }
  
  
}
void back_propogate(matrix * image){}
void classify_image(matrix * image){}  

// Lower level Neural Net functions
// Calculates squared error of output layer in comparison to expected
matrix * calc_output_error(matrix * activations, matrix * required){
  matrix * result = new_matrix(activations->row_cnt, activations->col_cnt);
  
  int i;
  for(i = 0; i < ((activations->col_cnt) * (activations->row_cnt)); i++){
    result->data[i] = ((required->data[i] - activations->data[i]) * (required->data[i] - activations->data[i]))/2;
  }
  return result;
}

matrix * calc_layer_error(matrix * activations, matrix * previous_error, matrix * weights, matrix * biases){
  matrix * result = new_matrix(activations->row_cnt, activations->col_cnt);
  
  int i;
  for(i = 0; i < ((activations->col_cnt) * (activations->row_cnt)); i++){
    result->data[i] = (required->data[i] - activations->data[i]) * (required->data[i] - activations->data[i]);
  }
  return result;
}

// Takes error, activations, weights and biases, and calculates the partial derivatives for the cost function
matrix_set * calc_gradient(matrix_set * activations, matrix_set * errors){
  int i;
  for(i = 0; i < activations->number_of_matrices; i++){
    result->data[i] = (required->data[i] - activations->data[i]) * (required->data[i] - activations->data[i]);
  }
}

// Takes input, weights and biases, and calculates the next layers activations
matrix * calc_layer_activation(matrix * prior_activations, matrix * weights, matrix * biases){
  matrix * WA = mult_matrix(weights, prior_activations);
  matrix * Z  = sum_matrix(WA, biases);
  matrix * A  = sigmoid_matrix(new_mat);
  
  free_matrix(WA);
  free_matrix(Z);
  return A;
}


