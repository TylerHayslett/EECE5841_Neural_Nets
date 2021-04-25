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
void setup_network(int input_size, int total_layers, int nodes_per_layer, int output_size){
  int i;
  
  WEIGHTS     = new_matrix_set(total_layers);
  BIASES      = new_matrix_set(total_layers);
  Z_SUM       = new_matrix_set(total_layers);
  ACTIVATIONS = new_matrix_set(total_layers + 1);
  ERRORS      = new_matrix_set(total_layers);
  WGRADIENT   = new_matrix_set(total_layers);
  BGRADIENT   = new_matrix_set(total_layers);
  
  // In new version, activations [0] is just always the image
  //ACTIVATIONS->set[0] = new_matrix(input_size,1);
  
  int in_width, out_width;
  for(i = 0; i < (total_layers); i++){
    if (i == 0){
      in_width = input_size;
    } else {
      in_width = nodes_per_layer;
    }
    if (i == (total_layers - 1)){
      out_width = output_size;
    } else {
      out_width = nodes_per_layer;
    }
    WEIGHTS->set[i] = new_matrix(out_width,in_width);
    rand_matrix(WEIGHTS->set[i],1/sqrt(in_width));
    
    BIASES->set[i] = new_matrix(out_width,1);
    Z_SUM->set[i] = new_matrix(out_width,1);
    ACTIVATIONS->set[i+1] = new_matrix(out_width,1);
    ERRORS->set[i] = new_matrix(out_width,1);
    WGRADIENT->set[i] = new_matrix(out_width,in_width);
    BGRADIENT->set[i] = new_matrix(out_width,1);
  }
  
}


void back_propogate(matrix * expected){
  int i;
  int num_layers = WEIGHTS->number_of_matrices;
  matrix * AT      = malloc(sizeof(matrix));
  matrix * Wgrad   = malloc(sizeof(matrix));
  matrix * Bgrad   = malloc(sizeof(matrix));
  
  for(i = 0; i < num_layers; i++){
    free_matrix(ERRORS->set[num_layers - 1 - i]);
    free_matrix(WGRADIENT->set[num_layers - 1 - i]);
    free_matrix(BGRADIENT->set[num_layers - 1 - i]);
    
    if (i == 0){
      calc_output_error(ERRORS->set[num_layers - 1 - i], ACTIVATIONS->set[num_layers - i], expected, Z_SUM->set[num_layers - 1 - i]);
    } else {
      calc_hidden_error(ERRORS->set[num_layers - 1 - i], ERRORS->set[num_layers - i], WEIGHTS->set[num_layers - i], Z_SUM->set[num_layers - 1 - i]);
    }
    
    transpose_matrix(AT, ACTIVATIONS->set[num_layers - 1 - i]);
    
    mult_matrix(Wgrad, ERRORS->set[num_layers - 1 - i], AT);
    scale_matrix(Bgrad, ERRORS->set[num_layers - 1 - i], 1);
    
    matrix * WGaccum = malloc(sizeof(matrix));
    matrix * BGaccum = malloc(sizeof(matrix));
    sum_matrix(WGaccum, Wgrad, WGRADIENT->set[num_layers - 1 - i]);
    sum_matrix(BGaccum, Bgrad, BGRADIENT->set[num_layers - 1 - i]);
    
    WGRADIENT->set[num_layers - 1 - i] = WGaccum;
    BGRADIENT->set[num_layers - 1 - i] = BGaccum;
    
  }
  
  free_matrix(AT);
  free_matrix(Wgrad);
  free_matrix(Bgrad);
}

void train(int num_layers, float training_rate){
  int k;
  matrix * WGscaled = malloc(sizeof(matrix));
  matrix * BGscaled = malloc(sizeof(matrix));
  
  for(k = 0; k < num_layers; k++){
    scale_matrix(WGscaled, WGRADIENT->set[k],training_rate);
    scale_matrix(BGscaled, BGRADIENT->set[k],training_rate);
    
    matrix * Wdiffed = malloc(sizeof(matrix));
    matrix * Bdiffed = malloc(sizeof(matrix));
    
    dif_matrix(Wdiffed, WEIGHTS->set[k], WGscaled);
    dif_matrix(Bdiffed, BIASES->set[k], BGscaled);
    
    free_matrix(WEIGHTS->set[k]);
    free_matrix(BIASES->set[k]);
    
    WEIGHTS->set[k] = Wdiffed;
    BIASES->set[k] = Bdiffed;
  }
  
  free_matrix(WGscaled);
  free_matrix(BGscaled);
}



void classify_image(matrix * image, matrix * estimate){
  int i;
  int num_layers = WEIGHTS->number_of_matrices;
  int temp_row = image->row_cnt;
  int temp_col = image->col_cnt;
  matrix * WA = malloc(sizeof(matrix));
  
  image->row_cnt = image->col_cnt * image->row_cnt;
  image->col_cnt = 1;
  
  ACTIVATIONS->set[0] = image;
  
  for(i = 0; i < num_layers; i++){
    free_matrix(Z_SUM->set[i]);
    free_matrix(ACTIVATIONS->set[i+1]);
    
    mult_matrix(WA, WEIGHTS->set[i], ACTIVATIONS->set[i]);
    sum_matrix(Z_SUM->set[i], WA, BIASES->set[i]);
    sigmoid_matrix(ACTIVATIONS->set[i+1], Z_SUM->set[i]);
  }
  image->row_cnt = temp_row;
  image->col_cnt = temp_col;
  
  free_matrix(WA);
}  

// Lower level Neural Net functions
// Calculates squared error of output layer in comparison to expected
void calc_output_error(matrix * calc_error, matrix * activations, matrix * required, matrix * Z){
  matrix * Ca    = new_matrix(activations->row_cnt, activations->col_cnt);
  matrix * dZ    = malloc(sizeof(matrix));
  matrix * error = malloc(sizeof(matrix));
  
  int i;
  for(i = 0; i < ((activations->col_cnt) * (activations->row_cnt)); i++){
    Ca->data[i] = activations->data[i] - required->data[i];
  }
  
  sig_deriv_matrix(dZ, Z);
  hadamard_matrix(error, Ca, dZ);
  
  free_matrix(Ca);
  free_matrix(dZ);
  free_matrix(calc_error);
  
  calc_error = error;
}

void calc_hidden_error(matrix * calc_error, matrix * prev_error, matrix * prev_weights, matrix * Z){
  matrix * WT      = malloc(sizeof(matrix));
  matrix * product = malloc(sizeof(matrix));
  matrix * dZ      = malloc(sizeof(matrix));
  matrix * error   = malloc(sizeof(matrix));
  
  transpose_matrix(WT, prev_weights);
  mult_matrix(product, WT, prev_error);
  sig_deriv_matrix(dZ, Z);
  
  hadamard_matrix(error, product, dZ);
  
  free_matrix(WT);
  free_matrix(product);
  free_matrix(dZ);
  free_matrix(calc_error);
  
  calc_error = error;
}



