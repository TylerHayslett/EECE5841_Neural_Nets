#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image_functions.h"
#include "matrix_functions.h"

int main(int argc, char *argv[]){  
  int index = 0;
  char current_label = 0;
  unsigned char *image = 0; //image array
  char * train_data  = "train_test_data/train-images-idx3-ubyte";
  char * train_label = "train_test_data/train-labels-idx1-ubyte";
  char * test_data   = "train_test_data/t10k-images-idx3-ubyte";
  char * test_label  = "train_test_data/t10k-labels-idx1-ubyte";
  
  index = atoi(argv[1]);
  
  printf("Reading image index %d, size %dx%d\n", index, SIZEX, SIZEY);
  imageread(train_data, &image, index);
  current_label = labelread(train_label, index);
  printf("Index %d is %d\n", index, current_label);
  
  printf("Writing image outputs\n");
  imagewrite("character.pgm", image);
  
  // Free used memory to prevent leaks in other OSes
  free(image);
  
  printf("Done\n");
  
  return 0;
  
}



