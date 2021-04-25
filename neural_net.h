// Tyler Hayslett
// 2021-04-12
#ifndef neural_net
#define neural_net

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common.h"
#include "matrix_functions.h"

extern matrix_set * WEIGHTS;
extern matrix_set * BIASES;
extern matrix_set * Z_SUM;
extern matrix_set * ACTIVATIONS;
extern matrix_set * ERRORS;
extern matrix_set * WGRADIENT;
extern matrix_set * BGRADIENT;

// Higher level Neural Net functions
void setup_network(int input_size, int total_layers, int nodes_per_layer, int output_size); // Initializes randomized weight and bias arrays for network
void train(int num_layers, float training_rate);                    // 
void back_propogate(matrix * expected);           // Calculates the gradient matrices
void classify_image(matrix * image);                              // Calculates the activations for the network

// Lower level Neural Net functions
void calc_output_error(matrix * calc_error, matrix * activations, matrix * required, matrix * Z);
void calc_hidden_error(matrix * calc_error, matrix * prev_error, matrix * prev_weights, matrix * Z);

#endif
