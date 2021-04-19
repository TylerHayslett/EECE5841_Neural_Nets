#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common_deffs.h"
#include "matrix_functions.h"
#include "neural_net.h"

matrix_set * WEIGHTS;
matrix_set * BIASES;
matrix_set * Z_SUM;
matrix_set * ACTIVATIONS;
matrix_set * ERRORS;
matrix_set * WGRADIENT;
matrix_set * BGRADIENT;

// assuming input will be one single full length column
void setup_network(int input_size, int number_of_hidden_layers, int nodes_per_layer, int output_size){
  int i;
  
  WEIGHTS = malloc(sizeof(matrix_set *));
  BIASES = malloc(sizeof(matrix_set *));
  Z_SUM  = malloc(sizeof(matrix_set *));
  ACTIVATIONS = malloc(sizeof(matrix_set *));
  ERRORS = malloc(sizeof(matrix_set *));
  WGRADIENT   = malloc(sizeof(matrix_set *));
  BGRADIENT = malloc(sizeof(matrix_set *));
  
  WEIGHTS->number_of_matrices = (number_of_hidden_layers + 1);
  BIASES->number_of_matrices = (number_of_hidden_layers + 1);
  Z_SUM->number_of_matrices = (number_of_hidden_layers + 1);
  ACTIVATIONS->number_of_matrices = (number_of_hidden_layers + 2);
  ERRORS->number_of_matrices = (number_of_hidden_layers + 1);
  WGRADIENT->number_of_matrices = (number_of_hidden_layers + 1);
  BGRADIENT->number_of_matrices = (number_of_hidden_layers + 1);
  
  WEIGHTS->set = malloc(sizeof(matrix *)*(number_of_hidden_layers + 1));
  BIASES->set = malloc(sizeof(matrix *)*(number_of_hidden_layers + 1));
  Z_SUM->set = malloc(sizeof(matrix *)*(number_of_hidden_layers + 1));
  ACTIVATIONS->set = malloc(sizeof(matrix *)*(number_of_hidden_layers + 2));
  ERRORS->set = malloc(sizeof(matrix *)*(number_of_hidden_layers + 1));
  WGRADIENT->set = malloc(sizeof(matrix *)*(number_of_hidden_layers + 1));
  BGRADIENT->set = malloc(sizeof(matrix *)*(number_of_hidden_layers + 1));
  
  int in_width, out_width;
  for(i = 0; i < (number_of_hidden_layers + 1); i++){
    if (i == 0){
      in_width = input_size;
    } else {
      in_width = nodes_per_layer;
    }
    if (i == number_of_hidden_layers){
      out_width = output_size;
    } else {
      out_width = nodes_per_layer;
    }
    WEIGHTS->set[i] = rand_matrix(out_width,in_width,1);
    BIASES->set[i] = new_matrix(out_width,1);
    Z_SUM->set[i] = new_matrix(out_width,1);
    ACTIVATIONS->set[i] = new_matrix(out_width,1);
    ERRORS->set[i] = new_matrix(out_width,1);
    WGRADIENT->set[i] = new_matrix(out_width,in_width);
    BGRADIENT->set[i] = new_matrix(out_width,1);
  }
  ACTIVATIONS->set[i] = new_matrix(out_width,1);
}


void back_propogate(matrix * image, matrix * expected){
  int i;
  int num_layers = WEIGHTS->number_of_matrices;
  classify_image(image);
  
  //printf("classified\n");
  
  for(i = 0; i < num_layers; i++){
    free_matrix(ERRORS->set[num_layers - 1 - i]);
    free_matrix(WGRADIENT->set[num_layers - 1 - i]);
    free_matrix(BGRADIENT->set[num_layers - 1 - i]);
    if (i == 0){
      ERRORS->set[num_layers - 1 - i] = calc_output_error(ACTIVATIONS->set[num_layers - i], expected, Z_SUM->set[num_layers - 1 - i]);
    } else {
      ERRORS->set[num_layers - 1 - i] = calc_hidden_error(ERRORS->set[num_layers - i], WEIGHTS->set[num_layers - i], Z_SUM->set[num_layers - 1 - i]);
    }
    
    matrix * AT = transpose_matrix(ACTIVATIONS->set[num_layers - 1 - i]);
    WGRADIENT->set[num_layers - 1 - i] = mult_matrix(ERRORS->set[num_layers - 1 - i], AT);
    BGRADIENT->set[i] = scale_matrix(ERRORS->set[num_layers - 1 - i], 1);
    free_matrix(AT);
  }
  //printf("propogated\n");
}

void classify_image(matrix * image){
  int i;
  int num_layers = WEIGHTS->number_of_matrices;
  int temp_row = image->row_cnt;
  int temp_col = image->col_cnt;
  
  image->row_cnt = image->col_cnt * image->row_cnt;
  image->col_cnt = 1;
  
  free_matrix(ACTIVATIONS->set[0]);
  ACTIVATIONS->set[0] = scale_matrix(image, 1);
  
  for(i = 0; i < num_layers; i++){
    free_matrix(Z_SUM->set[i]);
    free_matrix(ACTIVATIONS->set[i+1]);
    
    matrix * WA = mult_matrix(WEIGHTS->set[i], ACTIVATIONS->set[i]);
    Z_SUM->set[i] = sum_matrix(WA, BIASES->set[i]);
    ACTIVATIONS->set[i+1] = sigmoid_matrix(Z_SUM->set[i]);
      
    free_matrix(WA);
  }
  image->row_cnt = temp_row;
  image->col_cnt = temp_col;
}  

// Lower level Neural Net functions
// Calculates squared error of output layer in comparison to expected
matrix * calc_output_error(matrix * activations, matrix * required, matrix * Z){
  matrix * Ca = new_matrix(activations->row_cnt, activations->col_cnt);
  matrix * dZ = sig_deriv_matrix(Z);
  
  int i;
  for(i = 0; i < ((activations->col_cnt) * (activations->row_cnt)); i++){
    Ca->data[i] = activations->data[i] - required->data[i];
  }
  
  matrix * error = hadamard_matrix(Ca, dZ);
  
  free_matrix(Ca);
  free_matrix(dZ);
  
  return error;
}

matrix * calc_hidden_error(matrix * prev_error, matrix * prev_weights, matrix * Z){
  matrix * WT = transpose_matrix(prev_weights);
  matrix * product = mult_matrix(WT, prev_error);
  matrix * dZ = sig_deriv_matrix(Z);
  
  matrix * error = hadamard_matrix(product, dZ);
  
  free_matrix(WT);
  free_matrix(product);
  free_matrix(dZ);
  
  return error;
}



