#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common.h"
#include "matrix_functions.h"
#include "neural_net.h"

typedef struct data_sample {
  int label;
  matrix * values;
} data_sample;


void read_in_data(char s[], BYTE * data, int size){
  FILE *iFile = fopen(s,"r");
  if(iFile==0){
    printf("Error malloc-ing data\n");
    return;
  }
  fseek(iFile, (4*4), SEEK_SET);
  fread(data,sizeof(BYTE),size,iFile);
  fclose(iFile);
}

void read_in_labels(char s[], BYTE * labels, int size){
  FILE *iFile = fopen(s,"r");
  if(iFile==0){
    printf("Error malloc-ing labels\n");
    return;
  }
  fseek(iFile, (4*2), SEEK_SET);
  fread(labels,sizeof(BYTE),size,iFile);
  fclose(iFile);
}

void get_sample(data_sample * sample, BYTE * datum, BYTE * labels, int index){
  sample->label = (int) labels[index];
  
  int i;
  for(i = 0; i < (28*28); i++){
    sample->values->data[i] = ((float) datum[(index*28*28)+i]) / 255.0;
  }
}


void make_expected(matrix * expected, int label){
  int i;
  for(i = 0; i < (expected->row_cnt * expected->col_cnt); i++){
    expected->data[i] = 0;
  }
  
  expected->data[(int)label] = 1;
}

int estimate_index(matrix * estimated, ){
  get_sample();
  classify_image(norm_set);
  back_propogate(expected);
  
}


void eval_network(int total_layers){
  
  char * test_data   = "train_test_data/t10k-images-idx3-ubyte";
  char * test_label  = "train_test_data/t10k-labels-idx1-ubyte";
  
  int index = 0;
  int current_label = 0;
  
  matrix * accum_num = new_matrix(10,1);
  matrix * accum_est = new_matrix(10,1);
  matrix * expected  = new_matrix(10,1);
  matrix * estimate  = new_matrix(10,1);
  matrix * norm_set  = new_matrix(28*28,1);
  matrix * image     = new_matrix(28*28,1);
  
  int i;
  for(i = 0; i < 10000; i++){
    
    current_label = estimate_index( i);
    make_expected(expected, current_label);
    
    hadamard_matrix(estimate, ACTIVATIONS->set[total_layers], expected);
    
    int k;
    for(k = 0; k < 10; k++){
      accum_num->data[k] = accum_num->data[k] + expected->data[k];
      accum_est->data[k] = accum_est->data[k] + estimate->data[k];
    }
  }
  free_matrix(norm_set);
  free_matrix(image);
  free_matrix(expected);
  free_matrix(estimate);
  
  for(i = 0; i < 10; i++){
    accum_est->data[i] = accum_est->data[i] / accum_num->data[i];
  }
  print_matrix(accum_est);
  
  for(i = 0; i < 10; i++){
    matrix * image = malloc(sizeof(matrix));
    //imageread(test_data, image, i);
    current_label = labelread(test_label, i);
    
    if(i == 8){
      //imagewrite("example.pgm", image);
    }
    
    
    classify_image(norm_set);
    
    printf("%d\n",(int)current_label);
    print_matrix(ACTIVATIONS->set[total_layers]);
    
    free_matrix(norm_set);
    free_matrix(image);
  }
  
  
}


void train_network(float learning_rate, int total_layers){
  char * train_data  = "train_test_data/train-images-idx3-ubyte";
  char * train_label = "train_test_data/train-labels-idx1-ubyte";
  
  char current_label = 0;
  float adj_rate = learning_rate;
  adj_rate = adj_rate / 20.0;
  
  int i, index;
  for(i = 0; i < 160000; i++){
    
    index = (int)floor((((float)rand())/RAND_MAX) * 60000.0);
    
    //imageread(train_data, image, index);
    current_label = labelread(train_label, index);
    
    make_expected(expected, (int)current_label);
    
    classify_image(norm_set);
    back_propogate(expected);
    if((i % 20) == 19){
      train(total_layers, adj_rate);
    }
    
    free_matrix(expected);
  }
  
}


int main(int argc, char *argv[]){  
  
  int total_layers = atoi(argv[1]);
  int neurons_per_layer = atoi(argv[2]);
  float learning_rate = atof(argv[3]);
  
  
  setup_network(28*28,total_layers-1,neurons_per_layer,10);
  printf("Network setup\n");
  
  train_network(learning_rate, total_layers);
  eval_network(total_layers);
  
  printf("Done\n");
  return 0;
  
}



