#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common.h"
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
  ACTIVATIONS->set[0] = new_matrix(input_size,1);
  
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
    WEIGHTS->set[i] = rand_matrix(out_width,in_width,1/sqrt(in_width));
    BIASES->set[i] = const_matrix(out_width,1, 1.0);
    Z_SUM->set[i] = new_matrix(out_width,1);
    ACTIVATIONS->set[i+1] = new_matrix(out_width,1);
    ERRORS->set[i] = new_matrix(out_width,1);
    WGRADIENT->set[i] = new_matrix(out_width,in_width);
    BGRADIENT->set[i] = new_matrix(out_width,1);
  }
  
}

void free_network(){
  
  free_matrix_set(WEIGHTS);   
  free_matrix_set(BIASES);
  free_matrix_set(Z_SUM);  
  free_matrix_set(ACTIVATIONS);
  free_matrix_set(ERRORS);     
  free_matrix_set(WGRADIENT); 
  free_matrix_set(BGRADIENT);
}

void back_propogate(matrix * expected){
  int i;
  int num_layers = WEIGHTS->number_of_matrices;
  
  for(i = 0; i < num_layers; i++){
    free_matrix(ERRORS->set[num_layers - 1 - i]);
    if (i == 0){
      ERRORS->set[num_layers - 1 - i] = calc_output_error(ACTIVATIONS->set[num_layers - i], expected, Z_SUM->set[num_layers - 1 - i]);
    } else {
      ERRORS->set[num_layers - 1 - i] = calc_hidden_error(ERRORS->set[num_layers - i], WEIGHTS->set[num_layers - i], Z_SUM->set[num_layers - 1 - i]);
    }
    
    matrix * AT = transpose_matrix(ACTIVATIONS->set[num_layers - 1 - i]);
    
    matrix * Wgrad = mult_matrix(ERRORS->set[num_layers - 1 - i], AT);
    matrix * Bgrad = scale_matrix(ERRORS->set[num_layers - 1 - i], 1);
    
    matrix * WGaccum = sum_matrix(Wgrad, WGRADIENT->set[num_layers - 1 - i]);
    matrix * BGaccum = sum_matrix(Bgrad, BGRADIENT->set[num_layers - 1 - i]);
    
    free_matrix(Wgrad);
    free_matrix(Bgrad);
    free_matrix(WGRADIENT->set[num_layers - 1 - i]);
    free_matrix(BGRADIENT->set[num_layers - 1 - i]);
    
    WGRADIENT->set[num_layers - 1 - i] = WGaccum;
    BGRADIENT->set[num_layers - 1 - i] = BGaccum;
    free_matrix(AT);
  }
}

void train(int num_layers, float training_rate){
  int k;
  
  for(k = 0; k < num_layers; k++){
    matrix * WGscaled = scale_matrix(WGRADIENT->set[k],training_rate);
    matrix * BGscaled = scale_matrix(BGRADIENT->set[k],training_rate);
    
    free_matrix(WGRADIENT->set[k]);
    free_matrix(BGRADIENT->set[k]);
    
    WGRADIENT->set[k] = new_matrix(WEIGHTS->set[k]->row_cnt, WEIGHTS->set[k]->col_cnt);
    BGRADIENT->set[k] = new_matrix(BIASES->set[k]->row_cnt, BIASES->set[k]->col_cnt);
    
    matrix * Wdiffed = dif_matrix(WEIGHTS->set[k],WGscaled);
    matrix * Bdiffed = dif_matrix(BIASES->set[k],BGscaled);
    
    free_matrix(WGscaled);
    free_matrix(BGscaled);
    free_matrix(WEIGHTS->set[k]);
    free_matrix(BIASES->set[k]);
    
    WEIGHTS->set[k] = Wdiffed;
    BIASES->set[k] = Bdiffed;
  }
}



matrix * classify_image(matrix * image){
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
    //ACTIVATIONS->set[i+1] = ReLU_matrix(Z_SUM->set[i]);
    free_matrix(WA);
  }
  
  image->row_cnt = temp_row;
  image->col_cnt = temp_col;
  
  return scale_matrix(ACTIVATIONS->set[num_layers], 1);
}  

// Lower level Neural Net functions
// Calculates squared error of output layer in comparison to expected
matrix * calc_output_error(matrix * activations, matrix * required, matrix * Z){
  matrix * Ca = new_matrix(activations->row_cnt, activations->col_cnt);
  matrix * dZ = sig_deriv_matrix(Z);
  //matrix * dZ = ReLU_deriv_matrix(Z);
  
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
  //matrix * dZ = ReLU_deriv_matrix(Z);
  
  matrix * error = hadamard_matrix(product, dZ);
  
  free_matrix(WT);
  free_matrix(product);
  free_matrix(dZ);
  
  return error;
}



