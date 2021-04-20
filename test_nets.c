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
  
  expected->data[(int)label] = 1;
  
  return expected;
}
matrix * make_test_data(int label){
  matrix * test_data = new_matrix(10,1);
  test_data->data[(int)label] = 1;
  
  return test_data;
}

void eval_network(int total_layers){
  
  char * test_data   = "train_test_data/t10k-images-idx3-ubyte";
  char * test_label  = "train_test_data/t10k-labels-idx1-ubyte";
  
  int index = 0;
  char current_label = 0;
  float scale = (float)1/256;
  
  matrix * accum_num = new_matrix(10,1);
  matrix * accum_est = new_matrix(10,1);
  
  int i;
  for(i = 0; i < 10000; i++){
    matrix * image = malloc(sizeof(matrix*));
    
    imageread(test_data, image, i);
    current_label = labelread(test_label, i);
    
    matrix * expected = make_expected((int)current_label);
    
    matrix * norm_set = scale_matrix(image, scale); 
    
    classify_image(norm_set);
    free_matrix(norm_set);
    
    matrix * estimate = hadamard_matrix(ACTIVATIONS->set[total_layers], expected);
    
    int k;
    for(k = 0; k < 10; k++){
      accum_num->data[k] = accum_num->data[k] + expected->data[k];
      accum_est->data[k] = accum_est->data[k] + estimate->data[k];
    }
    free_matrix(estimate);
    free_matrix(expected);
    free_matrix(image);
  }
  
  //print_matrix(accum_est);
  //print_matrix(accum_num);
  
  for(i = 0; i < 10; i++){
    accum_est->data[i] = accum_est->data[i] / accum_num->data[i];
  }
  
  for(i = 0; i < 10; i++){
    matrix * image = malloc(sizeof(matrix*));
    imageread(test_data, image, i);
    current_label = labelread(test_label, i);
    matrix * norm_set = scale_matrix(image, scale); 
    
    if(i == 8){
      imagewrite("example.pgm", image);
    }
    
    
    classify_image(norm_set);
    
    printf("%d\n",(int)current_label);
    print_matrix(ACTIVATIONS->set[total_layers]);
    
    free_matrix(norm_set);
    free_matrix(image);
  }
  
  print_matrix(accum_est);
}


void train_network(float learning_rate, int total_layers){
  char * train_data  = "train_test_data/train-images-idx3-ubyte";
  char * train_label = "train_test_data/train-labels-idx1-ubyte";
  
  char current_label = 0;
  float scale = (float)1/256;
  float adj_rate = learning_rate;
  adj_rate = adj_rate / 20.0;
  
  int i, index;
  for(i = 0; i < 160000; i++){
    
    matrix * image = malloc(sizeof(matrix*));
    
    index = (int)floor((((float)rand())/RAND_MAX) * 60000.0);
    //printf("%d\n", index);
    
    imageread(train_data, image, index);
    current_label = labelread(train_label, index);
    
    matrix * norm_set = scale_matrix(image, scale); 
    matrix * expected = make_expected((int)current_label);
    
    classify_image(norm_set);
    back_propogate(expected);
    if((i % 20) == 19){
      train(total_layers, adj_rate);
    }
    
    free_matrix(image);
    free_matrix(norm_set);
    free_matrix(expected);
  }
  eval_network(total_layers);
}


int main(int argc, char *argv[]){  
  
  int total_layers = atoi(argv[1]);
  int neurons_per_layer = atoi(argv[2]);
  float learning_rate = atof(argv[3]);
  
  
  setup_network(28*28,total_layers-1,neurons_per_layer,10);
  printf("Network setup\n");
  
  train_network(learning_rate, total_layers);
  
  printf("Done\n");
  return 0;
  
}



