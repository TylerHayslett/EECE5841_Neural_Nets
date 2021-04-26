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

float calc_cost(matrix * expected, matrix * estimated){
  float cost = 0;
  for(int i = 0; i < 10; i++){
    cost += 0.5 * (expected->data[i] - estimated->data[i]) * (expected->data[i] - estimated->data[i]);
  }
  
  return cost;
}

matrix * estimate_index(matrix * expected, BYTE * datum, BYTE * labels, int index){
  
  data_sample * cur_sample = malloc(sizeof(data_sample));
  cur_sample->values = new_matrix(28*28,1);
  
  get_sample(cur_sample, datum, labels, index);
  
  matrix * estimated = classify_image(cur_sample->values);
  
  make_expected(expected, cur_sample->label);
  
  free_matrix(cur_sample->values);
  free(cur_sample);
  
  return estimated;
}


matrix * eval_network(int total_layers){
  
  char * test_data   = "train_test_data/t10k-images-idx3-ubyte";
  char * test_label  = "train_test_data/t10k-labels-idx1-ubyte";
  BYTE * sample_sets = malloc(sizeof(BYTE)*28*28*10000);
  BYTE * sample_labels = malloc(sizeof(BYTE)*10000);
  read_in_data(test_data, sample_sets, 28*28*10000);
  read_in_labels(test_label, sample_labels, 10000);
  
  float accum_cost = 0;
  matrix * accum_num = new_matrix(10,1);
  matrix * accum_est = new_matrix(10,1);
  matrix * expected  = new_matrix(10,1);
  
  
  int i;
  for(i = 0; i < 10000; i++){
    
    matrix * estimate = estimate_index(expected, sample_sets, sample_labels, i);
    accum_cost += calc_cost(expected, estimate);
    
    matrix * estimate_zoomed = hadamard_matrix(estimate, expected);
    
    int k;
    for(k = 0; k < 10; k++){
      accum_num->data[k] = accum_num->data[k] + expected->data[k];
      accum_est->data[k] = accum_est->data[k] + estimate_zoomed->data[k];
    }
    free_matrix(estimate);
    free_matrix(estimate_zoomed);
  }
  
  matrix * results = new_matrix(11,1);
  for(i = 0; i < 10; i++){
    results->data[i] = accum_est->data[i] / accum_num->data[i];
  }
  results->data[10] = accum_cost / 10000.0;
  print_matrix(results);
  
  free_matrix(accum_num);
  free_matrix(accum_est);
  free_matrix(expected);
  
  free(sample_sets);
  free(sample_labels);
  
  return results;
}


void epoch_network(float learning_rate, int total_layers, int batch_size){
  char * train_data  = "train_test_data/train-images-idx3-ubyte";
  char * train_label = "train_test_data/train-labels-idx1-ubyte";
  BYTE * sample_sets = malloc(sizeof(BYTE)*28*28*60000);
  BYTE * sample_labels = malloc(sizeof(BYTE)*60000);
  read_in_data(train_data, sample_sets, 28*28*60000);
  read_in_labels(train_label, sample_labels, 60000);
  
  float adj_rate = learning_rate / ((float) batch_size);
  matrix * expected  = new_matrix(10,1);
  
  int i;
  for(i = 0; i < 60000; i++){
    
    int index = (int)floor((((float)rand())/RAND_MAX) * 60000.0);
    //matrix * estimate = estimate_index(expected, sample_sets, sample_labels, index);
    matrix * estimate = estimate_index(expected, sample_sets, sample_labels, i);
    
    back_propogate(expected);
    
    if((i % batch_size) == (batch_size - 1)){
      train(total_layers, adj_rate);
    }
    free_matrix(estimate);
  }
  
  free_matrix(expected);
  free(sample_sets);
  free(sample_labels);
}


int main(int argc, char *argv[]){  
  
  FILE *iFile = fopen("test_data.txt","w");
  if(iFile==0) return 1; 
  
  int total_layers[4] = {1, 2, 3, 4};
  int neurons_per_layer[5] = {20, 40, 60, 80, 100};
  float learning_rate[6] = {2, 1, .2, .1, .05, .01};
  int number_of_epochs = 25;
  int size_of_batches[5] = {20, 40, 60, 80, 100};
  
  for(int k = 0; k < 4; k++){
    for(int h = 0; h < 5; h++){
      for(int j = 0; j < 6; j++){
        for(int l = 0; l < 5; l++){
          setup_network(28*28,total_layers[k],neurons_per_layer[h],10);
          printf("Network setup\n");
          fprintf(iFile, "----------------------------------------------------------------------------------------\n");
          fprintf(iFile, "-- %d Total Layers, %d Hidden Neurons/Layer, %d Batch size, %f Learning Rate\n", total_layers[k], neurons_per_layer[h], size_of_batches[l], learning_rate[j]);
          fprintf(iFile, "----------------------------------------------------------------------------------------\n");
          for(int i = 0; i < number_of_epochs; i++){
            // Write pgm header
            fprintf(iFile, "Epoch %d\n",i);
            
            epoch_network(learning_rate[j], total_layers[k], size_of_batches[l]);
            fprint_matrix(iFile, eval_network(total_layers[k]));
          }
          
          free_network();
        }
      }
    }
  }
  
  fprintf(iFile, "\n\nAll done!\n\n");
  fclose(iFile);
  
  printf("Done\n");
  return 0;  
}



