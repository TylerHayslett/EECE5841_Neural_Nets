#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common_deffs.h"
#include "image_functions.h"
#include "matrix_functions.h"
#include "neural_net.h"

matrix * make_expected(int label){
  matrix * expected = new_matrix(10,1);
  //expected->data[(int)label] = 1;
  if (label > 4) {
    expected->data[1] = 1;
  } else {
    expected->data[0] = 1;
  }
  
  return expected;
}



int main(int argc, char *argv[]){  
  int index = 0;
  char current_label = 0;
  matrix image1; //image array
  char * train_data  = "train_test_data/train-images-idx3-ubyte";
  char * train_label = "train_test_data/train-labels-idx1-ubyte";
  //char * test_data   = "train_test_data/t10k-images-idx3-ubyte";
  //char * test_label  = "train_test_data/t10k-labels-idx1-ubyte";
  
  index = atoi(argv[1]);
  
  int total_layers = 4;
  int learning_rate = 5;
  
  setup_network(28*28,total_layers-1,15,10,1);
  
  printf("Network setup\n");
  
  int i,k;
  for(i = 0; i < 60000; i++){
    imageread(train_data, &image1, i);
    current_label = labelread(train_label, i);
    
    matrix * norm_set = scale_matrix(&image1, 1/256);
    matrix * expected = make_expected((int)current_label);
    
    train(norm_set, expected, total_layers-1,learning_rate);
    
    free_matrix(norm_set);
    free_matrix(expected);
  }
  
  
  
  imageread(train_data, &image1, index);
  current_label = labelread(train_label, index);
  printf("%d\n", (int)current_label);
  
  matrix * expected = make_expected((int)current_label);
  
  print_matrix(expected);
  
  free_matrix(expected);
  
  matrix * norm_set = scale_matrix(&image1, 1/256);
  classify_image(norm_set);
  free_matrix(norm_set);
  
  printf("\n");
  print_matrix(ACTIVATIONS->set[total_layers]);
  
  
  
  printf("Done\n");
  return 0;
  
}



