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
  matrix image1, image2, test1, test2; //image array
  matrix * result;
  matrix * result2;
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
  
  scale_matrix(&image1, 4);
  result = sum_matrix(&image1, &image2);
  
  printf("Writing image outputs\n");
  imagewrite("character.pgm", result);
  
  printf("Done\n");
  
  test1.col_cnt = 3;
  test1.row_cnt = 1;
  float data1[] = {3,4,2};
  test1.data = data1;
  
  test2.col_cnt = 4;
  test2.row_cnt = 3;
  float data2[] = {13,9,7,15,8,7,4,6,6,4,0,3};
  test2.data = data2;
  
  result2 = mult_matrix(&test1, &test2);
  
  printf("Result is %d by %d\n", result2->row_cnt, result2->col_cnt);
  printf("[%f,%f]\n", result2->data[0], result2->data[1]);
  printf("[%f,%f]\n", result2->data[2], result2->data[3]);
  return 0;
  
}



