#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common_deffs.h"
#include "image_functions.h"
#include "matrix_functions.h"

int main(int argc, char *argv[]){  
  int index = 0;
  char current_label = 0;
  matrix image1, image2, result; //image array
  char * train_data  = "train_test_data/train-images-idx3-ubyte";
  char * train_label = "train_test_data/train-labels-idx1-ubyte";
  char * test_data   = "train_test_data/t10k-images-idx3-ubyte";
  char * test_label  = "train_test_data/t10k-labels-idx1-ubyte";
  
  index = atoi(argv[1]);
  
  printf("Reading image index %d, size %dx%d\n", index, SIZEX, SIZEY);
  imageread(train_data, &image1, index);
  current_label = labelread(train_label, index);
  printf("Index %d is %d\n", index, current_label);
  
  printf("Reading second image\n");
  imageread(train_data, &image2, 3);
  
  scale_matrix(&image1, &image1, 4);
  sum_matrix(&result, &image1, &image2);
  
  printf("Writing image outputs\n");
  imagewrite("character.pgm", &result);
  
  printf("Done\n");
  
  return 0;
  
}



