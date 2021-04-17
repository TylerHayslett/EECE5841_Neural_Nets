// Tyler Hayslett
// 2021-04-12
#ifndef neural_net
#define neural_net

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common_deffs.h"
#include "matrix_functions.h"

// Higher level Neural Net functions
void setup_network(int number_of_hidden_layers, int nodes_per_layer); // Initializes randomized weight and bias arrays for network
matrix_set back_propogate(matrix image);                              // Returns the gradient matrices
matrix classify_image(matrix image);                                  // Returns the output activations for the network

// Lower level Neural Net functions
void setup_layer(int preceeding_nodes, int following_nodes); // Initializes a single weight and bias array for the network
matrix calc_error(matrix activations, matrix required);
matrix calc_gradient(matrix activations, matrix prior_activations, matrix error, matrix weights, matrix biases);                      
matrix calc_activation(matrix prior_activations, matrix weights, matrix biases);

#endif
