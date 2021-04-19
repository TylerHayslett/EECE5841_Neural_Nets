#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common_deffs.h"
#include "image_functions.h"
#include "matrix_functions.h"
#include "neural_net.h"

int main(int argc, char *argv[]){  
  int index = 0;
  char current_label = 0;
  matrix image1; //image array
  char * train_data  = "train_test_data/train-images-idx3-ubyte";
  char * train_label = "train_test_data/train-labels-idx1-ubyte";
  //char * test_data   = "train_test_data/t10k-images-idx3-ubyte";
  //char * test_label  = "train_test_data/t10k-labels-idx1-ubyte";
  
  index = atoi(argv[1]);
  
  imageread(train_data, &image1, index);
  current_label = labelread(train_label, index);
  
  setup_network(28*28,1,10,10);
  
  printf("Network setup\n");
  
  int i,k;
  for(i = 0; i < 60000; i++){
    imageread(train_data, &image1, i);
    current_label = labelread(train_label, i);
    matrix * expected = new_matrix(10,1);
    
    expected->data[(int)current_label] = 1;
    
    back_propogate(&image1, expected);
    
    free_matrix(expected);
    
    for(k = 0; k < 2; k++){
      matrix * WGscaled = scale_matrix(WGRADIENT->set[k],0.01);
      matrix * BGscaled = scale_matrix(BGRADIENT->set[k],0.01);
      
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
  classify_image(&image1);
  printf("%d\n", (int)current_label);
  
  matrix * expected = new_matrix(10,1);
  expected->data[(int)current_label] = 1;
  print_matrix(expected);
  printf("\n");
  free_matrix(expected);
  
  
  print_matrix(ACTIVATIONS->set[2]);
  
  
  
  printf("Done\n");
  return 0;
  
}



